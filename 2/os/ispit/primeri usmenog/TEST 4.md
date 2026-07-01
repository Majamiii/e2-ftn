**TEST 4** 

**1) Koji nivoi koriscenja OS postoje?**

PROGRAMSKI, INTERAKTIVNI



**2) Kakvu ulogu ima klasa condition\_variable?**

Klasa condition\_variable je zaduzena da omoguci ostvarenje uslovne sinhronizacije. U while petlji condition variablom uspavamo nit sa wait I oslobadjamo trenutni lock pod kojim smo dok se uslov ne ispuni i neka druga nit ne pozove notify tj ne obavesti prvu nit da treba ponovo da pocne da radi. Operacije ove klase su namenjene za ostvarenje uslovne sinhronizacije u okviru kriticnih sekcija u kojim je medjusobna iskljucivost ostvarena pomocu operacija klase muteks. Ovom klasom sprecavamo pojaaavu busy waitinga.



**3)Prednosti i mane programiranja bez zakljucavanja.**

**Prednosti**

&nbsp;**a) bolje performanse** - smanjuje se vreme cekanja niti na pristup deljenim resursima i tako se moze poboljsati ukupno vreme izvrsavanja programa.

&nbsp;**b) nema zakljucavanja** - nema upotrebe semafora,propusnica I kriticnih sekcija pa nema potrebe za skupim i potencijalno sporum operacijama zakljucavanja

&nbsp;**c) Nema trke do podataka** sto omogucava koriscenje DWCAS.



**Mane**

&nbsp;a) **slozenost implementacije** - implementacija zahteva uboko razumevanje problema sinhronizacije i svojstava arhitekture na kojoj se program  izvodi a Llosa implementacija moze dovesti do gresaka koje je tesko otkriti i debagovati.

&nbsp;b) **Problem konzistentnosti podataka** = ako dve ili vise niti pokusaju da izmene iste podatke istovremeno posledicu su neispravni rezultati ili gubljenje podataka.

&nbsp;c) **Tesko za debagovanje** I otkrivanje gresaka(ovakve bagove je u linuks kernel bilo potreebo 10 godina da se otkriju.

&nbsp;d)**neportabilnost koda**



**4) Zamislite da pravite fajl sistem pod sledecim okolnostima,disk mora da cuva veliki broj malih fajlova koji mogu da rastu ali znate da ce uvek imati najvise 1 MB. Najvaznija osobina za koju treba da optimizujete je maksimalna efikasnost koriscenja prostora. Kako bi dizajnirali taj fajl sistem i zasto?**



Za veliki broj malih fajlova najefikasniji bi bio indeksirani fajl sistem sa malom veličinom bloka (npr. 1 KB).

Koristio bih inode strukturu sa direktnim pokazivačima, jer fajlovi ne prelaze 1 MB i time se izbegava nepotrebna indirekcija.

Ovakav sistem minimizuje internu fragmentaciju i postiže maksimalnu iskorišćenost prostora, uz zadržavanje mogućnosti rasta fajlova.



