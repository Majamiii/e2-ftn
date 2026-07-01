**TEST 2**

**1) Koje rasporedjivanje je vezano za zamenu slika/stranica procesa?**

DUGOROCNO



**2) Kakvu ulogu ima klasa unique\_lock?**

Konstruktor klase unique\_lock poziva omeraciju lock(), a destruktor operaciju unlock(). Da bi se to postiglo kao argument templejt klase unique\_lock mora se navesti klasa mutex, a kao argument konstruktora klase unique\_lock mora se navesti objekat klase mutex :  unique\_lock<mutex> m.



**3) koje bi posledice bile kada bi se u OS zabranila upotreba SETUID/SUID bitova na izvrsnim datototekama?**



Podsetnik: šta je SUID (Set User ID)



Ako izvršna datoteka ima SUID bit, svaki korisnik koji je pokrene privremeno dobija prava njenog vlasnika (najčešće „root“-a).

To omogućava običnim korisnicima da koriste programe koji traže administratorska prava, bez da su stalno root.

Primer: komanda passwd ima SUID, jer menja /etc/shadow, fajl koji običan korisnik inače ne sme da menja.



Ako bi OS zabranio SUID bitove Bezbednost bi se povećala, jer:



Napadač ne bi mogao da zloupotrebi SUID programe za eskalaciju privilegija.



Ali bi se pojavili veliki praktični problemi, jer:



Mnogi sistemski programi (npr. passwd, ping, mount, su) više ne bi mogli da funkcionišu za obične korisnike.



Korisnici bi morali da imaju administratorske privilegije za svaku operaciju koja pristupa zaštićenim resursima.



Sistem bi postao manje funkcionalan i nepraktičan za više korisnika.



**Kratak i tačan odgovor za ispit:**



**Zabrana SUID bitova bi povećala bezbednost, jer bi se sprečile zloupotrebe privilegija, ali bi onemogućila normalan rad mnogih sistemskih programa koji zahtevaju privremeno povišena prava (npr. passwd, ping). Time bi sistem postao bezbedniji, ali znatno manje upotrebljiv.**



**4) Zamislite da pravite fajl sistem pod sledecim okolnostima,disk mora da cuva veliki broj malih fajlova koji mogu da rastu ali znate da ce uvek imati najvise 1 MB. Najvaznija osobina za koju treba da optimizujete je maksimalna efikasnost koriscenja prostora. Kako bi dizajnirali taj fajl sistem i zasto?**



Za veliki broj malih fajlova najefikasniji bi bio indeksirani fajl sistem sa malom veličinom bloka (npr. 1 KB).

Koristio bih inode strukturu sa direktnim pokazivačima, jer fajlovi ne prelaze 1 MB i time se izbegava nepotrebna indirekcija.

Ovakav sistem minimizuje internu fragmentaciju i postiže maksimalnu iskorišćenost prostora, uz zadržavanje mogućnosti rasta fajlova.







