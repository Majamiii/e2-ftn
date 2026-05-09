/**
 * Napisati C++ program koji cita podatke o studentima iz ulazne datoteke i potom 
 * za svakog studenta racuna prosek
 * 
 * U ulaznoj datoteci "studenti.csv" se u svakom redu nalaze informacije o studentu: 
 *     Ime,Prezime,Broj indeksa,Ocene 
 * Pritom su ocene odvojene medjusobno zarezima.
 * 
 * Prilikom obrade podataka o studentima, mora se proveriti format indeksa da li je validan. Ako nije, zanemariti taj unos.
 * Format indeksa je:
 *     [[:alpha:]][[:alnum:]]{1,2}\s[[:digit:]]{1,3}\/[[:digit:]]{4}
 * 
 * U tri izlazne datoteke rasporediti studente u zavisnosti od proseka.
 * Ukoliko je prosek > 9.00 potrebno je upisati studenta u datoteku "kandidati_stipendija.csv".
 * Ukoliko je prosek > 8.00 i prosek <= 9.00 potrebno je upisati studenta u datoteku "kandidati_kredit.csv".
 * U ostalim slucajevima upisati studenta u datoteku "ostali.csv".
 * Format u izlaznoj datoteci treba da odgovara sledecem: Ime,Prezime,Broj_indeksa,prosek
 * 
 * Treba napraviti jednu nit koja ce samo citati redove ulazne podatke, jednu nit 
 * koja ce samo pisati gotove podatke u izlazne datoteke i 10 niti radnika koji ce na osnovu redova
 * iz ulazne datoteke generisati sve neophodno za ispis u izlaznu datoteku.
*/

#include <iostream>
#include <sstream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <regex>
#include <numeric>
#include <condition_variable>
#include <fstream>
#include <queue>

#define BROJ_RADNIKA 10

using namespace std;

class Student {
private:
    string ime;
    string prezime;
    string broj_indeksa;
    double prosek;
    int tip;    // 1 je stipendija, 2 je kredit, 3 su ostali
public:
    Student(string i, string p, string b, double pr) : ime(i),prezime(p),broj_indeksa(b),prosek(pr) {
        if (prosek>9){
            tip = 1;
        }else if (prosek>8){
            tip = 2;
        }else{
            tip = 3;
        }
    }

    string getIme(){
        return ime;
    }
    void setIme(string nime){
        ime = nime;
    }
    string getPrezime(){
        return prezime;
    }
    void setPrezime(string nime){
        prezime = nime;
    }
    string getIdx(){
        return broj_indeksa;
    }
    void setIdx(string i){
        broj_indeksa = i;
    }
    double getProsek(){
        return prosek;
    }
    void setProsek(double d){
        prosek = d;
    }
    int getTip(){
        return tip;
    }
};

template<typename T>
class InputData {
private:
    mutex data_mtx;
    // TODO dodati polja po potrebi
    queue<T> data;
    bool end;
    condition_variable cv;
public:
    InputData(): end(false) {
        // TODO
    }
    void add_data(T data_element) {
        unique_lock<mutex> ul(data_mtx);
        data.push(data_element);
        cv.notify_one();
    }

    bool remove_data(T &data_element) {
        unique_lock<mutex> ul(data_mtx);

        while(waiting()){
            cv.wait(ul);
        }
        if (the_end()){
            return false;
        }

        data_element = move(data.front());
        data.pop();

        return true;
    }

    // TODO dodati metode po potrebi

    
    bool the_end() {
        return data.empty() && end;
    }

    bool waiting(){
        return data.empty() && !end;
    }

    void declare_end(){
        unique_lock<mutex> ul(data_mtx);
        end = true;
        cv.notify_all();
    }

};

template<typename T>
class OutputData {
private:
    mutex data_mtx;
    // TODO dodati polja po potrebi
    queue<T> data;
    condition_variable cv;
    int data_producers_num;
    bool end;
public:
    OutputData(): end(false), data_producers_num(0) {}

    void add_data(T data_element) {
        unique_lock<mutex> ul(data_mtx);
        data.push(data_element);
        cv.notify_one();
    }
    bool remove_data(T &data_element) {
        unique_lock<mutex> ul(data_mtx);

        while(waiting()){
            cv.wait(ul);
        }

        if (the_end()){
            return false;
        }

        data_element = move(data.front());
        data.pop();

        return true;
    }

    bool the_end() {
        return data.empty() && end;
    }

    // TODO dodati metode po potrebi
    bool waiting(){
        return data.empty() && !end;
    }

    void add_data_producer(){
        unique_lock<mutex> ul(data_mtx);
        data_producers_num++;
    }
    void remove_data_producer(){
        unique_lock<mutex> ul(data_mtx);
        data_producers_num--;
        if (data_producers_num == 0){
            end = true;
            cv.notify_all();
        }
    }
    
};

void reader(string input_file_name, InputData<string>& raw_data) {
    ifstream dat(input_file_name);
    string linija;

    if (dat.is_open()){

        string s;

        while(getline(dat,linija)){

            raw_data.add_data(linija);

        }

        dat.close();
    }else{
        cerr << "CITAC: ne mogu da otvorim fajl.\n";
    }

    raw_data.declare_end();
}

void proccessing_data(InputData<string>& raw_data, OutputData<Student>& proccessed_data){

    proccessed_data.add_data_producer();
    string linija;
    
    while (raw_data.remove_data(linija)){

        stringstream ss(linija);
        string token;
        vector<string> tokeni;

        while (getline(ss, token, ',')) {
            tokeni.push_back(token);
        }
        if (tokeni.size() < 4) {
            cerr << "RADNIK: neispravna linija: " << linija << "\n";
            continue;
        }
 
        string ime     = tokeni[0];
        string prezime = tokeni[1];
        string indeks  = tokeni[2];

        double suma = 0.0;
        int    n    = 0;
        bool   valid = true;

        for (size_t i = 3; i < tokeni.size(); i++) {
            try {
                double ocena = stod(tokeni[i]);
                suma += ocena;
                n++;
            } catch (const exception&) {
                cerr << "RADNIK: neispravna ocena '" << tokeni[i] << "' za studenta " << ime << " " << prezime << "\n";
                valid = false;
                break;
            }
        }

        static const regex index_regex{"[[:alpha:]][[:alnum:]]{1,2}\\s[[:digit:]]{1,3}\\/[[:digit:]]{4}"};
        if(!regex_match(indeks, index_regex)){
            cerr << "RADNIK: neispravan format indeksa '" << indeks << "' za studenta " << ime << " " << prezime << "\n";
            continue;
        }

        if (!valid || n == 0) continue;

        double prosek = suma / n;
        Student s(ime, prezime, indeks, prosek);
        proccessed_data.add_data(s);
    }
    proccessed_data.remove_data_producer();
}

string outputFileName(int tip){
    if (tip == 1){
        return "kandidati_stipendija.csv";
    }else if (tip == 2){
        return "kandidati_kredit.csv";
    }
    else if (tip == 3){
        return "ostali.csv";
    }else{
        cerr << "PISAC: Student ne upada ni u jednu kategoriju!\n";
        return "";
    }
}

void writer(OutputData<Student>& proccessed_data) {

    Student s("","","",0.0);
    
    while(proccessed_data.remove_data(s)){
        
        string output_file_name = outputFileName(s.getTip());
        if (output_file_name.empty()) continue;

        ofstream dat(output_file_name, ios::app);

        if (dat.is_open()){

            dat<<s.getIme()<<","<<s.getPrezime()<<","<<s.getIdx()<<","<<s.getProsek()<<"\n";
            dat.close();
        }else{
            cerr << "PISAC: ne mogu da otvorim fajl.\n";
        }
    }
}


int main() {
    InputData<string> ulazni_podaci;
    OutputData<Student> izlazni_podaci;
    thread radnici[BROJ_RADNIKA];

    ofstream("kandidati_kredit.csv").close();
    ofstream("kandidati_stipendija.csv").close();
    ofstream("ostali.csv").close();

    thread p1 = thread(reader, "studenti.csv", ref(ulazni_podaci));
    for(int i=0;i<BROJ_RADNIKA;i++){
        radnici[i] = thread(proccessing_data, ref(ulazni_podaci), ref(izlazni_podaci));
    }
    thread p2 = thread(writer, ref(izlazni_podaci));

    p1.join();
    for(int i=0;i<BROJ_RADNIKA;i++){
        radnici[i].join();
    }
    p2.join();
    
    return 0;
}