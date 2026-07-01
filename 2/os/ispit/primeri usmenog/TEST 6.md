**TEST 6**

**1. Koja prava pristupa datoteka postoje?** 

&nbsp;pravo čitanja, pravo pisanja, pravo izvršavanja



**2) Po cemu se razlikuju ziva i mrtva petlja?**

U slucaju neblokirajuce sistemske operacije akljucavanja,procesi upadaju u beskonacnu betlju (starvation), pokusavajuci da zakljucaju datoteku,koju je zakljucao drugi proces. Ovakav oblik medjuzavisnosti procesa se naziva ziva petlja te se ona po svoom ishodu sustinski i ne razlikuje od mrtve petlje.



3\) Koje su prednosti a koje mane ucitavanja citavog veceg fajla u memorijski bafer u odnosu na ucitavanje kroz mapiranje na memoriju?



Učitavanje celog fajla daje jednostavnost i deterministične performanse ali troši više RAM-a i radi dodatna kopiranja; mmap štedi memoriju i često ubrzava nasumičan pristup (zero-copy, lazy paging), ali uvodi page-fault režiju, komplikovanije rukovanje greškama i pitanja sinhronizacije sa diskom.



Bafer = jednostavnije, ali troši više memorije

Mapiranje = efikasnije i brže za velike fajlove, ali kompleksnije za implementaciju

