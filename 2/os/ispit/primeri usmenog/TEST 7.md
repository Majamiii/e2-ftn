**TEST 7**

**1)Koje kolone ima matrica zaštite?** 

&nbsp;vlasnik, saradnik, ostali



2\)Šta sadrže elementi tabele stranica?

• Baznu adresu odgovarajuće stranice



Sažetak za ispit: svaki element tabele stranica sadrži adresu fizičke stranice i skup kontrolnih bitova (present/valid, referenced, dirty i zaštitni bitovi) koji omogućavaju MMU-i i kernelu da bezbedno i efikasno prevode i upravljaju virtuelnim stranicama.



3\) Koje su prednosti a koje mane ucitavanja citavog veceg fajla u memorijski bafer u odnosu na ucitavanje kroz mapiranje na memoriju?



Učitavanje celog fajla daje jednostavnost i deterministične performanse ali troši više RAM-a i radi dodatna kopiranja; mmap štedi memoriju i često ubrzava nasumičan pristup (zero-copy, lazy paging), ali uvodi page-fault režiju, komplikovanije rukovanje greškama i pitanja sinhronizacije sa diskom.



Bafer = jednostavnije, ali troši više memorije

Mapiranje = efikasnije i brže za velike fajlove, ali kompleksnije za implementaciju



