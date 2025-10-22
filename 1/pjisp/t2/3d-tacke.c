/*
Tačke u trodimenzionalnom Dekartovom koordinatnom sistemu opisane su preko njihovih koordinata:

Vrednost na x-osi (realan broj dvostruke preciznosti)
Vrednost na y-osi (realan broj dvostruke preciznosti)
Vrednost na z-osi (realan broj dvostruke preciznosti)
Rastojanje od koordinatnog početka (realan broj dvostruke preciznosti)

Učitati tačke iz ulazne datoteke, potom uraditi sledeće:

Prilikom učitavanja izračunati rastojanje od koordinatnog početka (formula data pre sekcije "Napomene"). 
Nakon toga, zapisati koordinate u izlaznu datoteku čije ime se zadaje kao argument komandne linije u 
sledećem formatu: "(x, y, z), d", gde su x, y i z redom koordinate tačke, a d rastojanje od koordinatnog početka.

Pronaći najbližu i najdalju tačku tačku od koordinatnog početka. Izračunati njihovu međusobnu udaljenost, 
potom izračunati zapreminu kocke čija je stranica dužine udaljenosti između tih tačaka.

Izračunati zapreminu kocke čija stranica se unosi u program kao argument komandne linije (može biti realna 
vrednost). Upisati zapreminu iz prethodnog koraka (pod b) i dobijenu zapreminu u izlaznu datoteku, kao 
zapreminu tela koje bi nastalo kada bi se od veće kocke odsekao deo veličine manje kocke. Izlazna datoteka 
treba da nosi ime koje počinje sa "sracunata"/"argument", "_kocka_minus_", "sracunata"/"argument", "_kocka.txt", 
gde će prva biti kocka sa većom, a druga kocka sa manjom zapreminom.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
    float d;
}TACKE;

FILE *safe_fopen(char filename[], char mode[], int kod);
void ucitaj(FILE *in, FILE *out, TACKE tacke[], int *n);

int main(int argc, char **argv) {

    int n=0;

    if(argc != 4) {
        printf("Pogresan poziv programa! Primer: %s tacke.txt tacke_,..\n", argv[0]);
        exit(20);
    }

    char *filename1 = argv[1];
    char *filename2 = argv[2];
    FILE *in = safe_fopen(filename1, "r", 1);
    FILE *out = safe_fopen(filename2, "w", 1);

    TACKE tacke[30];
    ucitaj(in, out, tacke, &n);

    fclose(in);
    fclose(out);

    return 0;
}



FILE *safe_fopen(char filename[], char mode[], int kod){

    FILE *fp = fopen(filename, mode);

    if(fp == NULL) {
        printf("Nemoguce pristupiti datoteci %s!\n", filename);
        exit(kod);
    }

    return fp;

}

void ucitaj(FILE *in, FILE *out, TACKE tacke[], int *n){

    
    while(
        (fscanf(in, "%f %f %f",
        &tacke[*n].x, &tacke[*n].y, &tacke[*n].z))!= EOF
    ){
        (*n)++;
    }
    // printf("%f\n", (float)tacke[1].x);

    for(int i=0; i<(*n); i++){
        fprintf(out, "(%.2f %.2f %.2f", tacke[i].x, tacke[i].y, tacke[i].z);

        tacke[i].d = sqrt( (tacke[i].x)*tacke[i].x + tacke[i].y*tacke[i].y + tacke[i].z*tacke[i].z );
        // printf("%.2f    ", tacke[i].d);
        fprintf(out, "), %.2f\n", tacke[i].d);

    }


}


/*
Primer poziva programa:

./a.out tacke.txt tacke_formatirano.txt 5
Primer ulazne datoteke tacke.txt:

1 1 1
2 1 3
4 1 7
3 5 3
7 7 7
1 8 7



Primer izlazne datoteke tacke_formatirano.txt:

(1.00, 1.00, 1.00), 1.73
(2.00, 1.00, 3.00), 3.74
(4.00, 1.00, 7.00), 8.12
(3.00, 5.00, 3.00), 6.56
(7.00, 7.00, 7.00), 12.12
(1.00, 8.00, 7.00), 10.68



Primer izlazne datoteke sracunata_kocka_minus_argument_kocka.txt:

Zapremina sracunate kocke: 1122.37
Zapremina argument kocke: 125.00
Razlika u zapreminama: 997.37
*/