#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <regex>
#include <numeric>

using namespace std;

// ─────────────────────────────────────────────
//  Student
// ─────────────────────────────────────────────
class Student {
private:
    string ime;
    string prezime;
    string broj_indeksa;
    double prosek;

public:
    Student() : prosek(0.0) {}

    Student(const string& ime, const string& prezime,
            const string& indeks, const vector<double>& ocene)
        : ime(ime), prezime(prezime), broj_indeksa(indeks), prosek(0.0)
    {
        if (!ocene.empty())
            prosek = accumulate(ocene.begin(), ocene.end(), 0.0) / ocene.size();
    }

    string getIme()          const { return ime; }
    string getPrezime()      const { return prezime; }
    string getBrojIndeksa()  const { return broj_indeksa; }
    double getProsek()       const { return prosek; }

    // Formatiran red za izlaznu datoteku
    string toCSVLine() const {
        ostringstream oss;
        oss << ime << "," << prezime << "," << broj_indeksa << ","
            << fixed << setprecision(2) << prosek;
        return oss.str();
    }
};

// ─────────────────────────────────────────────
//  InputData  –  reader → workers
//  Blokirajući red s jednim proizvođačem (reader nit).
//  set_end() signalizira radnicima da je čitanje završeno.
// ─────────────────────────────────────────────
template<typename T>
class InputData {
private:
    mutex              data_mtx;
    condition_variable cv;
    queue<T>           data;
    bool               end;

public:
    InputData() : end(false) {}

    void add_data(T data_element) {
        {
            unique_lock<mutex> lock(data_mtx);
            data.push(move(data_element));
        }
        cv.notify_one();
    }

    // Vraća false samo kad je red prazan I kraj je signaliziran.
    bool remove_data(T& data_element) {
        unique_lock<mutex> lock(data_mtx);
        cv.wait(lock, [this] { return !data.empty() || end; });
        if (data.empty()) return false;
        data_element = move(data.front());
        data.pop();
        return true;
    }

    void set_end() {
        {
            unique_lock<mutex> lock(data_mtx);
            end = true;
        }
        cv.notify_all();   // probudi sve radnike koji čekaju
    }
};

// ─────────────────────────────────────────────
//  OutputData  –  workers → writer
//  Više proizvođača (10 radnih niti); svaka poziva
//  remove_producer() pri izlasku. Kad brojač padne na 0,
//  end = true i pisač se budi.
// ─────────────────────────────────────────────
template<typename T>
class OutputData {
private:
    mutex              data_mtx;
    condition_variable cv;
    queue<T>           data;
    bool               end;
    int                data_producers_num;

public:
    OutputData() : end(false), data_producers_num(0) {}

    void add_producer() {
        unique_lock<mutex> lock(data_mtx);
        ++data_producers_num;
    }

    void remove_producer() {
        {
            unique_lock<mutex> lock(data_mtx);
            if (--data_producers_num == 0)
                end = true;
        }
        cv.notify_all();
    }

    void add_data(T data_element) {
        {
            unique_lock<mutex> lock(data_mtx);
            data.push(move(data_element));
        }
        cv.notify_one();
    }

    // Vraća false samo kad je red prazan I svi proizvođači završili.
    bool remove_data(T& data_element) {
        unique_lock<mutex> lock(data_mtx);
        cv.wait(lock, [this] { return !data.empty() || end; });
        if (data.empty()) return false;
        data_element = move(data.front());
        data.pop();
        return true;
    }

    bool the_end() {
        unique_lock<mutex> lock(data_mtx);
        return data.empty() && end;
    }
};

// ─────────────────────────────────────────────
//  Reader nit  –  čita redove iz CSV-a
// ─────────────────────────────────────────────
void reader(const string& input_file_name, InputData<string>& raw_data) {
    ifstream file(input_file_name);
    if (!file.is_open()) {
        cerr << "[reader] Ne mogu da otvorim: " << input_file_name << "\n";
        raw_data.set_end();
        return;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            raw_data.add_data(line);
    }

    raw_data.set_end();   // signalizira radnicima da više nema podataka
}

// ─────────────────────────────────────────────
//  Worker niti  –  parsiraju, validiraju, računaju prosek
// ─────────────────────────────────────────────
void proccessing_data(InputData<string>& raw_data,
                      OutputData<Student>& proccessed_data)
{
    proccessed_data.add_producer();

    // Format indeksa: [[:alpha:]][[:alnum:]]{1,2}\s[[:digit:]]{1,3}\/[[:digit:]]{4}
    const regex index_regex(
        "[[:alpha:]][[:alnum:]]{1,2}\\s[[:digit:]]{1,3}/[[:digit:]]{4}");

    string line;
    while (raw_data.remove_data(line)) {

        // ── parsiranje zarezima odvojenih polja ──────────────────────────
        vector<string> tokens;
        {
            istringstream ss(line);
            string tok;
            while (getline(ss, tok, ','))
                tokens.push_back(tok);
        }

        // Minimalno: Ime, Prezime, Indeks, bar jedna ocena
        if (tokens.size() < 4) continue;

        const string& ime     = tokens[0];
        const string& prezime = tokens[1];
        const string& indeks  = tokens[2];

        // ── validacija formata indeksa ───────────────────────────────────
        if (!regex_match(indeks, index_regex)) {
            cerr << "[worker] Nevalidan indeks: \"" << indeks << "\" – preskačem.\n";
            continue;
        }

        // ── parsiranje ocena ─────────────────────────────────────────────
        vector<double> ocene;
        bool valid = true;
        for (size_t i = 3; i < tokens.size(); ++i) {
            try {
                ocene.push_back(stod(tokens[i]));
            } catch (...) {
                valid = false;
                break;
            }
        }
        if (!valid || ocene.empty()) continue;

        proccessed_data.add_data(Student(ime, prezime, indeks, ocene));
    }

    proccessed_data.remove_producer();
}

// ─────────────────────────────────────────────
//  Writer nit  –  raspoređuje studente u tri datoteke
// ─────────────────────────────────────────────
void writer(OutputData<Student>& proccessed_data) {
    ofstream f_stipendija("kandidati_stipendija.csv");
    ofstream f_kredit("kandidati_kredit.csv");
    ofstream f_ostali("ostali.csv");

    if (!f_stipendija || !f_kredit || !f_ostali) {
        cerr << "[writer] Greška pri otvaranju izlaznih datoteka.\n";
        return;
    }

    Student s;
    while (proccessed_data.remove_data(s)) {
        const double p = s.getProsek();
        const string row = s.toCSVLine();

        if      (p > 9.0) f_stipendija << row << "\n";
        else if (p > 8.0) f_kredit     << row << "\n";
        else               f_ostali     << row << "\n";
    }
}

// ─────────────────────────────────────────────
//  main
// ─────────────────────────────────────────────
int main() {
    InputData<string>   raw_data;
    OutputData<Student> proccessed_data;

    thread th_reader(reader, "studenti.csv", ref(raw_data));
    thread th_writer(writer, ref(proccessed_data));

    thread th_workers[10];
    for (auto& th : th_workers)
        th = thread(proccessing_data, ref(raw_data), ref(proccessed_data));

    th_reader.join();
    for (auto& th : th_workers) th.join();
    th_writer.join();

    return 0;
}