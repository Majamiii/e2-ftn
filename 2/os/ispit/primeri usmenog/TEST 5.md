**TEST 5**

**1)Sta je tacno za skracivanje kvantuma?**

brži odziv, smanjenje iskorišćenosti procesora



**2) sta ima svaka nit konkurentnog procesa?**

Svaka nit ima svoj prioritet, stek i descriptor, ali nema svoju sliku jer nju deli sa maticnim procesom,tj sa ostalim  nitima istog procesa.



**3) Da li su drajveri potencijalan vektor za napad na bezbednost računarskog sistema?** 

Drajveri definitivno jesu potencijalni vektor za napad — zbog izvršavanja u kernelu i direktnog pristupa resursima. Međutim, uz dobru praksu razvoja (validacija, fuzzing, statička analiza), pravilne administrativne politike (potpisivanje, ažuriranja, ograničavanje instalacija) i hardverske/mehaničke zaštite (IOMMU, Secure Boot), rizik se značajno smanjuje.



4)Koja je razlika izmedju jezika za konkurentno programiranje i jezika kome je biblioteka za konkurentno programiranje deo standardne biblioteke? Da li uospte postoji?



Jezik sa ugrađenom konkurentnošću pojednostavljuje i osigurava pisanje paralelnih programa zahvaljujući jezičnim konstrukcijama i runtime optimizacijama, dok pristup kroz biblioteku daje veću kontrolu i manju zavisnost od runtime-a, ali zahteva više pažnje i koda od programera.“

