/**
 * Napisati program koji 20 puta pokrece simulaciju 05_a_i_b_pre_c koja je radjena na terminu 4. vezbi.
 * 
 * Prvi korak je uraditi taj zadatak ako vec niste.
 * 
 * Ako jeste, izvrsnu datoteku programa kopirati pored izvrsne datoteke ovog programa. Uz oslonac na 
 * `fork`, `wait` i `execv` sistemske pozive, pokrenuti 20 puta zadatak 05_a_i_b_pre_c kao spoljasnji
 * program pritom svaki put sacekavsi da se pokrenuto izvrsenje zavrsi. 
 * 
 * NAPOMENA: program se navodi punom putanjom!
 * 
 * BONUS: pokrenuti ovaj program od 2 do 5 puta i videti da li se desava da nekada ispisi iz niti a i b
 * zamene mesta. Ako se desava da oni zamene mesta ali ne budu nikada pre ispisa iz niti c, zadatak 
 * 05_a_i_b_pre_c je odlicno resen. 
*/
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"

#define BR_POKRETANJA 20

int main() {
    pid_t dete_pid;

    for (int i = 0; i < BR_POKRETANJA; i++) {
        dete_pid = fork();

        if (dete_pid < 0) {  // ukoliko je povratna vrednost fork() sistemskog poziva negativna, znaci da je doslo do greske i proces nije podvojen
            std::cerr << "Proces se nije uspesno podvojio." << std::endl;
            exit(2);  // signaliziramo da nas primer nije uspesno podvojio proces.

        } else if (dete_pid == 0) { 
            char *argumenti[] = {"TODO ovde staviti punu putanju do izvrsne datoteke projekta!", NULL};  // TODO postaviti punu putanju na nesto smisleno!
            
            if (execv(argumenti[0], argumenti) == -1) {
                std::cerr << "Doslo je do greske prilikom pokretanja programa!" << std::endl;
                exit(1);
            }
        } else {
            wait(nullptr); // cekamo na dete da zavrsi!
        }
    }

    return 0;
}