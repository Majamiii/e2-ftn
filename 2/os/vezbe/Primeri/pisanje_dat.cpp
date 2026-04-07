#include <iostream>
#include <fstream>  // potrebno zbog ofstream (OutputFileSTREAM)

int main() {
  std::string ime_izlazne_dat = "probna.txt";
  std::ofstream izlazna_dat(ime_izlazne_dat);

  if(izlazna_dat.is_open()) {
    izlazna_dat << "Saljemo prvo jedan string." << std::endl;
    izlazna_dat << "Potom i par brojeva: " << 1 << " " << 15.48 << " " << -2.0/3 << std::endl;
    izlazna_dat << "Moze i zapetljano: ";
    for (int i = 0; i < 42; i++)
      izlazna_dat << i+1 << " ";
    izlazna_dat << "\nIspis je isti kao na standardni izlaz, samo je ovaj put usmeren u datoteku!" << '\n';

    izlazna_dat.close();
  } else
      std::cerr << "CITAC: Nisam mogao da otvorim datoteku \"" << ime_izlazne_dat << "\" za pisanje!\n";  // ispis na tok standardnog izlaza greske

  return 0;
}