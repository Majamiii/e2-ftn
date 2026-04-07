#include <iostream>
#include <fstream>  // potrebno zbog ifstream (InputFileSTREAM)
#include <sstream>  // potrebno zbog istringstream (InputSTRINGSTREAM)

int main() {
  std::string ime_ulazne_dat = "studenti.csv";
  std::ifstream ulazna_dat(ime_ulazne_dat);

  if(ulazna_dat.is_open()) {
    std::string red_datoteke;
    while(getline(ulazna_dat, red_datoteke)) {  // citanje datoteke red po red
			std::istringstream red_datoteke_tok(red_datoteke);
      std::string ime, prezime, indeks, ocena;
 
			if(!getline(red_datoteke_tok, ime, ','))
          continue;  // ako ne procitamo ime kako treba, prelazimo na naredni red datoteke, ovaj zanemarujemo
 
			if(!getline(red_datoteke_tok, prezime, ','))
          continue;  // ako ne procitamo prezime kako treba, prelazimo na naredni red datoteke, ovaj zanemarujemo
 
			if(!getline(red_datoteke_tok, indeks, ','))
          continue;  // ako ne procitamo indeks kako treba, prelazimo na naredni red datoteke, ovaj zanemarujemo
 
      std::cout << "Indeks:\t" << indeks << std::endl << "   Prezime: " << prezime << std::endl << "   Ime:     " << ime << std::endl << "   Ocene:   ";
			while (getline(red_datoteke_tok, ocena, ','))  // citanje ocena dok postoje; odvojene su zarezom
				std::cout << std::stoi(ocena) << " ";  // parsiranje ocene iz stringa i ispis na ekran
      std::cout << std::endl;
    }

    ulazna_dat.close();
  } else
      std::cerr << "CITAC: Nisam mogao da otvorim datoteku \"" << ime_ulazne_dat << "\" za citanje!\n";  // ispis na tok standardnog izlaza greske

  return 0;
}