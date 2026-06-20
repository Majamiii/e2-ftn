/**
 * Napisati program koji na standardnom izlazu prikazuje predloge lozinki od 80
 * znakova koje sadrze u sebi string "caj".
 * 
 * Uz oslonac na `fork`, `wait` i `execv` sistemske pozive, pokrenuti program 
 * "/usr/bin/gpg" kao spoljasnji program sa parametrima {"--gen-random", 
 * "--armor", "1", "4000000"}. Spoljasnji program i roditelja povezati 
 * pajpovanjem tako da izlaz spoljasnjeg programa obradjuje roditeljski proces.
 * 
 * Spoljasnji program ce izgenerisati sekvencu od 4000000 nasumicnih znakova a
 * bez belih znakova
 * 
 * Obrada treba da se desava tako da roditelj uzima po 80 znakova i tretira ih
 * kao jednu lozinku. Potom ako u ucitanih 80 znakova pronadje string "caj", 
 * ispisuje lozinku na standardni izlaz.
 * 
 * NAPOMENA: moze se dosta jednostavno uraditi ako se odvoji bafer od 81-og 
 * znaka i na kraju postavi '\0' nakon ucitavanja 80 znakova
*/
#include <iostream>
#include <unistd.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"

int main() {
    pid_t dete_pid;
    int tok[2];
    int status;

    status = pipe(tok);

    if (status == -1) {
        std::cerr << "Nisam uspeo da napravim tok za preusmerenje ulaza/izlaza." << std::endl;
        exit(1);
    }

    dete_pid = fork();

    if (dete_pid < 0) {  // ukoliko je povratna vrednost fork() sistemskog poziva negativna, znaci da je doslo do greske i proces nije podvojen
        std::cerr << "Proces se nije uspesno podvojio." << std::endl;
        exit(2);  // signaliziramo da nas primer nije uspesno podvojio proces.
    } else if (dete_pid == 0) {  // u slucaju uspesnog podvajanja procesa, fork vraca razlicite povrate vrednosti u originalu i kopiji da bi oba znala ko je ko; kopirani proces, tj. dete, dobija nulu (0) kao povratnu vrednost
        close(tok[0]);  // zatvaramo tok za citanje jer necemo citati iz deteta

        std::cout << "Pocinje preusmerenje standardnog izlaza na tok ka roditelju." << std::endl;

        dup2(tok[1], 1);  // preuzimamo kontrolu nad standardnim izlazom deteta kopirajuci desktriptor toka za pisanje preko deskriptora za standardni izlaz

        std::cout << "Preusmerio sam tok izlaza novog procesa i pozivam novi program." << std::endl;

        char *argumenti[] = {"/usr/bin/gpg", "--gen-random", "--armor", "1", "4000000", NULL};
        if (execv(argumenti[0], argumenti) == -1) {
            std::cerr << "Doslo je do greske prilikom pokretanja programa!" << std::endl;
            exit(1);
        }
    } else {  // roditelj proces dobija kao povratnu vrednost fork() poziva PID deteta (kopiranog procesa) da bi mogao da ga kontrolise.
        char bafer[81], br_znakova;
        bafer[80] = 0;
        close(tok[1]);  // zatvaram deo toka za pisanje jer ce roditelj samo citati rezultat spoljasnjeg programa!
        
        dup2(tok[0], 0);  // preusmeravamo izlaz toka na standardni ulaz (std::cin, ili STDIN_FILENO) tako sto preko STDIN_FILENO deskriptora kopiramo podatke o deksriptoru izlaznog pajp toka

        std::cout << "Roditelj pocinje citanje sadrzaja koji salje spoljni program.\n";
        while ((br_znakova = read(0, bafer, 80)) > 0) {  // citanje je blokirajuce i cekace dok sadrzaj ne stigne ili dok se tok ne zatvori (zatvara ga terminacija poslednjeg pisaca)
            std::string lozinka(bafer);  // stvaranje stringa od bafera radi lakseg rada
            if (lozinka.find("caj") != std::string::npos) {  // ispis lozinke samo ako u njoj ima "caj"
                std::cout << lozinka << std::endl;
            }
        }
    }

    return 0;
}