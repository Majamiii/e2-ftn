**TEST 3**

**1) Koji logicki adresni prostori postoje?**

KONTINUALNI, SEGMENTIRANI, STRANICNI



**2) sta karakterise nultu nit?**

Nulta nit je osnovna i prva nit procesa, automatski stvorena pri njegovom pokretanju.

Ona izvršava glavnu funkciju programa, stvara ostale niti i njen završetak obično znači kraj celog procesa.



**3) Ako bi postojao fajl gde bi imali i write pristup i bio postavljen setuid bit, da li bi to mogli da iskoristite da probijete zastitu na sistemu? Ako ne sta bi vam jos trebalo?**



Ako izvršna datoteka ima SUID bit, ona se prilikom pokretanja izvršava sa privilegijama njenog vlasnika (često root). Ako je ta ista izvršna datoteka pisiva (može joj se promeniti sadržaj), to predstavlja kritičan sigurnosni rizik: napadač koji uspe da izmeni sadržaj datoteke može (konceptualno) uzrokovati izvršavanje proizvoljnog koda sa povišenim privilegijama i tako eskalirati privilegije.



**4) Kako sistemski poziv omogucava obicnom korisniku da poziva zasticene, sistemske operacije?**

Sistemski poziv omogućava običnom korisniku da traži izvršenje zaštićene operacije tako što pravi prelaz iz korisničkog režima u kernel režim (trap/interrupt ili instrukcija syscall/int 0x80), pri čemu CPU menja privilegije i kontrolu prebacuje kernelu. Korisnički proces poziva wrapper (npr. u libc) koji postavlja broj poziva i argumente, zatim skreće u kernel; kernel pročita broj/argumente, validira ih i proveri dozvole (UID/GID, prava, capability), izvrši zahtevanu zaštićenu radnju i vrati rezultat (ili grešku/errno). Nakon toga kernel vraća kontrolu procesu i CPU se vraća u korisnički režim — korisnik nikad direktno ne upravlja hardverom već samo preko ove kontrolisane tačke (interfejsa) koju kernel osigurava.





&nbsp;Sistemski poziv je posrednik između korisničkih programa i jezga, koji omogućava siguran prelaz iz korisničkog u prilivegovani režim, čime korisnik može da koristi zaštićene operacije bez diskretnog pristupa jezgru.



