/*
Učinak fudbalskog tima tokom sezone opisan je sledećim poljima:

naziv tima (do 30 karaktera)
gol razlika (ceo broj)
broj bodova (neoznačen, ceo broj)

Svaki tim, pored imena i gol razlike, u ulaznoj datoteci postoje, redom, broj pobeda, nerešenih 
utakmica i poraza. Sa podacima iz ulazne datoteke uraditi sledeće:

Učitati ih u niz struktura koje odgovaraju gornjem opisu. Iskoristiti broj pobeda, nerešenih utakmica i 
poraza za računanje trenutnog broja bodova po sledećem principu:

Pobeda nosi 3 boda
Nerešena utakmica nosi 1 bod
Poraz nosi 0 bodova

U izlaznu datoteku ispisati sve timove koji se sa brojem bodova nalaze u intervalu između prosečnog broja 
bodova u ligi i vrednosti zadate kao argument komandne linije. Datoteku nazvati sa prefiksom 
"izmedju_proseka_i_", pa onda staviti broj bodova unet kao argument komandne linije i postfiks "_bodova.txt".

Sortirati tabelu po broju bodova. U slučaju da dve ekipe imaju isti broj bodova, prednost ima ona ekipa koja 
ima veću gol razliku. Prve tri ekipe idu u "Ligu šampiona", sledeće dve u "Ligu Evrope", a poslednje tri su u 
"zoni ispadanja". Prilikom ispisa u izlaznu datoteku posebno podvući crtu ispod timova koji su plasirani za 
"Lige", odnosno iznad "zone ispadanja".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 31

typedef struct timovi_st{
    char naziv[MAX_NAZIV];
    int gol_razlika;
    int pobede;
    int neresene;
    int porazi;
    int trenutni_bodovi;
}TIMOVI;

FILE* safe_fopen(char fajl[], char mod[], int kod);
void unos(FILE *in, int *n, TIMOVI *timovi);
void izmedju_proseka(FILE *prosek, TIMOVI *timovi, int n, int granica);
void ispis_tabela(TIMOVI *timovi, int n, FILE *granica);

int main(int argc, char **argv) {

    if(argc != 4) {
        printf("Greska pri pozivu programa! Primer:     %s statistika.txt tabela.txt 20\n", argv[0]);
        exit(1);
    }

    char *ulazni_fajl = argv[1];
    char *tabela = argv[2];
    char *granica_string = argv[3];
    int granica = atoi(argv[3]);

    FILE *in = safe_fopen(ulazni_fajl, "r", 2);
    FILE *out = safe_fopen(tabela, "w", 3);

    char ime_prosek[100] = {};
    strcat(ime_prosek, "izmedju_proseka_i_");
    strcat(ime_prosek, granica_string);
    strcat(ime_prosek, "_bodova.txt");

    FILE *prosek = safe_fopen(ime_prosek, "w", 3);

    int n=0;
    TIMOVI timovi[50];

    unos(in, &n, timovi);
    izmedju_proseka(prosek, timovi, n, granica);
    ispis_tabela(timovi, n, out);

    fclose(in);
    fclose(out);
    fclose(prosek);

    return 0;
}



FILE* safe_fopen(char fajl[], char mod[], int kod) {
    
    FILE *fp = fopen(fajl, mod);

    if(fp ==NULL) {
        printf("Cannot open file %s!\n", fajl);
        exit(kod);
    }

    return fp;
}


void unos(FILE *in, int *n, TIMOVI *timovi){

    int i=0;

    while(
        (fscanf(in, "%s %d %d %d %d",
        timovi[*n].naziv, &timovi[*n].gol_razlika, &timovi[*n].pobede, &timovi[*n].neresene, &timovi[*n].porazi
        )
        )!=EOF
    ){(*n)++;
    }
    for(i=0; i<(*n); i++) {
        timovi[i].trenutni_bodovi = timovi[i].pobede*3 + timovi[i].neresene;
    }
}


void izmedju_proseka(FILE *prosek, TIMOVI *timovi, int n, int granica){

    int i=0;
    int suma=0;

    for(i = 0; i<n; i++) {
        suma += timovi[i].trenutni_bodovi;
    }
    int avg = suma/n;

    for(i=0; i<n; i++){

        if(avg<granica) {
            if(timovi[i].trenutni_bodovi > avg && timovi[i].trenutni_bodovi<=granica) {
                fprintf(prosek, "%s %d %d\n",
                timovi[i].naziv, timovi[i].gol_razlika, timovi[i].trenutni_bodovi);
                // printf("\ntu sam.\n");
            }
        }
        else if(avg>granica) {
            if(timovi[i].trenutni_bodovi < avg && timovi[i].trenutni_bodovi>=granica) {
                fprintf(prosek, "%s %d %d\n",
                timovi[i].naziv, timovi[i].gol_razlika, timovi[i].trenutni_bodovi);
            }
        }

    }


}



void ispis_tabela(TIMOVI *timovi, int n, FILE *granica){
    int brojac = 0;
    int i, j, temp, max_index;

    TIMOVI temp_tim;

    for(i=0; i<n; i++){
        // max_index = i;
        for(j=i+1; j<n; j++){
            if(timovi[i].trenutni_bodovi < timovi[j].trenutni_bodovi){
                // max_index = j;
                temp_tim = timovi[i];
                timovi[i] = timovi[j];
                timovi[j] = temp_tim;

                // temp = timovi[i].naziv;
                // (timovi[i]).naziv = timovi[j].naziv;
                // timovi[j].naziv = temp;
            }   
        }
        fprintf(granica, "%s %d %d\n", timovi[i].naziv, timovi[i].gol_razlika, timovi[i].trenutni_bodovi);
        brojac++;

        if(brojac == 3 || brojac == 5 || brojac==(n-3)) {
            fprintf(granica, "---------------------\n");
        }

    }

}

/*
Primer ulazne datoteke statistika.txt:

Atalanta 7 8 1 4
Bologna -5 4 4 5
Cagliari -10 5 1 7
Chievoverona -1 5 3 5
Crotone -16 1 2 10
Empoli -11 2 4 7
Fiorentina 7 5 5 2
Genoa 0 4 4 4
Inter 2 5 3 5
Juventus 19 11 0 2
Lazio 12 7 4 2
Milan 4 8 2 3
Napoli 9 7 3 3
Palermo -16 1 3 9
Pescara -14 1 4 8
Roma 16 8 2 3
Sampdoria -3 5 3 5
Sassuolo -9 4 1 8
Torino 13 6 4 3
Udinese -4 4 3 6



Primer izlazne datoteke tabela.txt:

Juventus 19 33
Roma 16 26
Milan 4 26
-------------------
Lazio 12 25
Atalanta 7 25
-------------------
Napoli 9 24
Torino 13 22
Fiorentina 7 20
Inter 2 18
Chievoverona -1 18
Sampdoria -3 18
Genoa 0 16
Bologna -5 16
Cagliari -10 16
Udinese -4 15
Sassuolo -9 13
Empoli -11 10
-------------------
Pescara -14 7
Palermo -16 6
Crotone -16 5



Primer izlazne datoteke izmedju_proseka_i_25_bodova.txt:

Atalanta 7 25
Chievoverona -1 18
Fiorentina 7 20
Inter 2 18
Lazio 12 25
Napoli 9 24
Sampdoria -3 18
Torino 13 22



Primer poziva programa:

./fudbal statistika.txt tabela.txt 20



*/