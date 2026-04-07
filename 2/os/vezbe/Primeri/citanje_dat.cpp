#include <iostream>
#include <fstream>  // potrebno zbog ifstream (InputFileSTREAM)

int main() {
  std::string ime_ulazne_dat = "studenti.csv";
  std::ifstream ulazna_dat(ime_ulazne_dat);

  if(ulazna_dat.is_open()) {
    std::string red_datoteke;
    while(getline(ulazna_dat, red_datoteke)) {  // citanje datoteke red po red
      std::cout << red_datoteke << std::endl;
    }

    ulazna_dat.close();
  } else
      std::cerr << "CITAC: Nisam mogao da otvorim datoteku \"" << ime_ulazne_dat << "\" za citanje!\n";  // ispis na tok standardnog izlaza greske

  return 0;
}