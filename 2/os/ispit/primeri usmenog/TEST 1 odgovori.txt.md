**TEST 1**

**1) Sta su postojeci tipovi semafora/ koje vrste semafora postoje**

postoje **binarni**, **generalni** i **raspodeljeni binarni**



**2) Po cemu se razlikuju ziva i mrtva petlja?**

U slucaju neblokirajuce sistemske operacije akljucavanja,procesi upadaju u beskonacnu betlju (starvation), pokusavajuci da zakljucaju datoteku,koju je zakljucao drugi proces. Ovakav oblik medjuzavisnosti procesa se naziva ziva petlja te se ona po svoom ishodu sustinski i ne razlikuje od mrtve petlje.



**3) Uporedite segmentni adresni prostor i stranicni adresni prostor u pogledu interne fragmentacije i objasniti koliko je interna fragmentacija memorije znacajna za odabir adresnog prostora na modernim racunarskim arhitekturama.**



U segmentnom adresnom prostoru memorija je podeljena na segmente različite dužine, pa nema interne fragmentacije, ali se javlja eksterna fragmentacija, jer slobodni delovi između segmenata često nisu dovoljni za nove segmente.

U straničnom adresnom prostoru memorija je podeljena na jednake blokove (stranice), pa nema eksterne fragmentacije, ali postoji interna fragmentacija – poslednja stranica procesa retko je potpuno popunjena.

U savremenim arhitekturama interna fragmentacija je malo značajna, jer je gubitak memorije zanemarljiv u poređenju sa prednostima straničenja: jednostavnijim upravljanjem memorijom, boljom iskorišćenošću i zaštitom procesa.



**4) u distribuiranom sistemu koji upravlja nekakvom zgradom imate poruku koja ima parametre ID, SMER RAZDALJINA. Ta poruka omogucava direktnu kontrolu lifta tako sto liftu oznacenom sa ID kaze da se u SMER-u (gore ili dole) pomeri za odgovarajuci broj spratova RAZDALJINA. Da li je ova poruka idempotentna? ako jeste koje njene osobine je cine takvom ako nije kako bi je modifikovali da bude idempotentna**



Poruka sa parametrima (ID, SMER, RAZDALJINA) nije idempotentna, jer ponovnim slanjem iste poruke lift bi se ponovo pomerio za zadatu razdaljinu.

Dakle, ako se poruka slučajno duplira u mreži, lift bi izvršio komandu više puta, što bi dovelo do pogrešne pozicije — to znači da rezultat zavisi od broja ponavljanja poruke.



Da bi poruka bila idempotentna, potrebno je da se njen efekat ne menja ponavljanjem.

To se može postići tako da poruka ne sadrži relativno kretanje (gore/dole za razdaljinu), već apsolutnu poziciju lifta, npr:



(ID, SPRAT) – "postavi lift ID na određeni sprat".



U tom slučaju, ako se poruka ponovi više puta, rezultat je uvek isti — lift će ostati na tom spratu, pa je operacija idempotentna.







