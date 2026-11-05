# Redovi čekanja (M|M|k|r sistemi) — podsetnik pre rešavanja zadataka

## 1. Osnovna ideja

Sistem masovnog opsluživanja posmatramo kao **proces rađanja i umiranja** (birth-death process). Stanje sistema u trenutku t je broj mušterija/kupaca/klijenata koji se trenutno nalaze u sistemu (i oni koji se uslužuju i oni koji čekaju).

- Kad stigne nova mušterija, stanje raste za 1 ("rađanje").
- Kad se neko usluži i ode, stanje opada za 1 ("umiranje").

Ovo je **Markovljev lanac neprekidnog vremena**, i zato se ceo sistem opisuje jednom matricom Λ (matrica intenziteta prelaza), a mi tražimo **finalne (stacionarne) verovatnoće** p*n = verovatnoća da se, nakon dovoljno dugog vremena, u sistemu nalazi tačno n mušterija.

## 2. Kendall-ova notacija: M|M|k|r

- **M** (prvo) — dolasci mušterija su Poasonov proces (Markovljev), tj. broj dolazaka u jedinici vremena ima Poasonovu P(λ) raspodelu, a vreme između dva dolaska ima eksponencijalnu E(λ) raspodelu.
- **M** (drugo) — vreme usluživanja jedne mušterije na jednom mestu ima eksponencijalnu E(μ) raspodelu.
- **k** — broj mesta za usluživanje (broj "šaltera", radnika, ekipa...).
- **r** — broj mesta **za čekanje** (ne računajući mesta za usluživanje!). Ako je r = ∞, red nije ograničen. Ako je r = 0, nema reda uopšte (ko ne nađe slobodno mesto za usluživanje, biva odbijen).

**Ukupan kapacitet sistema** = k + r (maksimalan broj mušterija koje sistem uopšte može da sadrži).

## 3. Osnovni parametri

- **λ** (lambda) — intenzitet dolazaka: prosečan broj dolazaka u jedinici vremena. Bira se **vremenska jedinica** (najčešće 1 sat ili 1 dan) i λ se izračunava u toj jedinici.
- **μ** (mi) — intenzitet usluživanja **na jednom mestu**: koliko mušterija u proseku jedno mesto za usluživanje opsluži u jedinici vremena. Ako je prosečno vreme usluživanja E(V) = 1/μ, onda μ = 1/E(V).

⚠️ **Najčešća greška** (vidi Zadatak 5!): ako je dato koliko sistem *ukupno* uposli u jedinici vremena (npr. tri krojačice zajedno sašiju 6 komada dnevno), to **nije μ** — to treba podeliti sa k da dobiješ μ po jednom mestu (μ = 6/3 = 2).

- **ρ = λ/(kμ)** — **faktor opterećenja sistema** (utilization). Intuitivno: koliki deo ukupnog "kapaciteta usluživanja" sistem prosečno koristi.
  - Ako je r = ∞ (neograničen red), finalne verovatnoće postoje **samo ako je ρ < 1** (inače se red beskonačno gomila).
  - Ako je r konačno (uključujući r = 0), finalne verovatnoće **uvek postoje**, jer sistem ima konačno mnogo stanja.

## 4. Matrica Λ i jednačine ravnoteže

Za proces rađanja i umiranja, brzina rađanja u stanju n (λn) i brzina umiranja u stanju n (μn) su:

- **λn = λ** za sva n < k+r (ako ima mesta), λn = 0 za n ≥ k+r (sistem pun, dolasci se odbijaju)
- **μn = n·μ** za n ≤ k (koliko god je zauzetih mesta za usluživanje, toliko "servera" radi)
- **μn = k·μ** za n > k (svi serveri rade punom parom, dodatni ljudi samo čekaju)

Matrica Λ (na dijagonali -( λn+μn ), iznad dijagonale λn, ispod dijagonale μn) potpuno opisuje sistem.

**Jednačine ravnoteže** dobijaju se iz p*·Λ = 0 uz uslov Σp*n = 1. Zbog specijalne (trodijagonalne) strukture, ovo se svodi na jednostavan **princip protoka**: proticanje "unapred" preko granice između stanja n i n+1 mora biti jednako proticanju "unazad":

**λn · p*n = μ(n+1) · p*(n+1)**

Ovo je ključna formula — iz nje se rekurzivno izražava svako p*n preko p*0, a zatim se p*0 nađe iz uslova da je zbir svih verovatnoća 1.

## 5. Opšti recept (koji se ponavlja u svakom zadatku)

1. Odredi λ, μ, k, r (pazi na vremensku jedinicu!).
2. Napiši Λ.
3. Rekurzivno izrazi p*1, p*2, p*3, ... preko p*0 koristeći λn·p*n = μ(n+1)·p*(n+1).
4. Iz p*0 + p*1 + p*2 + ... = 1 nađi p*0 (ovde se, kod r = ∞, javlja geometrijski red — zato je bitan uslov ρ<1 da red konvergira).
5. Iz p*0 izračunaj sve ostale p*n.

## 6. Gotove formule po tipu sistema

### a) M|M|1|∞ (jedan server, neograničen red)

Uslov postojanja: ρ = λ/μ < 1.

- p*n = (1 − ρ)·ρⁿ = (1 − λ/μ)·(λ/μ)ⁿ, n = 0,1,2,...
- p*0 = 1 − λ/μ
- **E(X) = ρ/(1−ρ) = λ/(μ−λ)** (očekivan broj mušterija u sistemu)

### b) M|M|k|∞ (k servera, neograničen red)

Uslov postojanja: ρ = λ/(kμ) < 1.

- Za n ≤ k: **p*n = p*0 · (λ/μ)ⁿ / n!**
- Za n ≥ k: **p*n = p*0 · (λ/μ)ⁿ / (k! · k^(n−k))**
- p*0 = 1/A, gde je

  A = Σ (n=0 do k−1) (λ/μ)ⁿ/n!  +  (λ/μ)^k / k! · 1/(1 − λ/(kμ))

(Ovo je poznato i kao osnova Erlang-ovih formula u teoriji saobraćaja.)

### c) M|M|k|r (k servera, r mesta za čekanje — konačan sistem)

Finalne verovatnoće **uvek postoje** (bez uslova na ρ), jer je broj stanja konačan: n = 0, 1, ..., k+r.

- Za 0 ≤ n ≤ k: p*n = p*0 · (λ/μ)ⁿ / n!
- Za k ≤ n ≤ k+r: p*n = p*0 · (λ/μ)ⁿ / (k! · k^(n−k))
- p*0 se dobija iz uslova Σ(n=0 do k+r) p*n = 1 (konačna suma, uvek se može direktno sabrati/rešiti sistem).

Specijalni slučaj **M|M|k|0**: nema mesta za čekanje uopšte, sistem ima samo k+1 stanja (0 do k). Ko ne nađe slobodan server, biva odbijen.

## 7. Verovatnoća odbijanja / čekanja — i PASTA princip

- **Verovatnoća da je nova mušterija odbijena** (sistem pun) = p*(k+r) — poslednja finalna verovatnoća.
- **Verovatnoća da nova mušterija mora da čeka** (svi serveri zauzeti, ali ima mesta u redu) = p*k + p*(k+1) + ... + p*(k+r−1) = 1 − (p*0+...+p*(k−1)) − p*(k+r) (ili slično, zavisno šta tačno pitaju).

Ovo važi zbog **PASTA principa** (Poisson Arrivals See Time Averages): pošto su dolasci Poasonov proces, verovatnoća da baš pristigla mušterija затекне sistem u stanju n je ista kao finalna verovatnoća p*n. Zato možeš direktno da koristiš p*n za "sledećeg kupca", bez dodatnog računanja.

## 8. Očekivani broj u sistemu — opšta formula

Bez obzira na tip sistema:

**E(X∞) = Σ (n=0 do ∞ ili k+r) n · p*n**

Za M|M|1 ovo ima zatvorenu formu (λ/(μ−λ)); za M|M|k i M|M|k|r obično se računa direktno kao suma (konačna ili beskonačna) — nema uvek lepu zatvorenu formulu, pa se često koristi trik sa izvodom geometrijskog reda (tačka 9).

## 9. Korisne sume redova (pamti ove dve!)

Za |x| < 1:

- **Σ (n=0 do ∞) xⁿ = 1/(1−x)**  (obična geometrijska suma)
- **Σ (n=0 do ∞) n·xⁿ⁻¹ = 1/(1−x)²**
- pa je **Σ (n=0 do ∞) n·xⁿ = x/(1−x)²**

Ove formule se koriste kad računaš E(X) direktno kao red (npr. u Zadatku 1b, 2b).

Veza sa geometrijskom raspodelom: ako X∞ = Y − 1, gde Y ima geometrijsku G(p) raspodelu (p = p*0), onda:
**E(X∞) = E(Y) − 1 = 1/p − 1**

## 10. Računanje "u realnom vremenu" (troškovi, broj odbijenih, itd.)

Kad treba da nađeš **očekivani broj događaja tokom perioda T** (npr. koliko će ljudi biti odbijeno za 8 sati, koliko će se sladoleda pokloniti za 12 sati):

**Očekivan broj (odbijenih / onih koji čekaju / itd.) za vreme T = (λ · T) · p**

gde je:
- λ·T = očekivan ukupan broj dolazaka tokom perioda T (pazi da su λ i T u istoj vremenskoj jedinici!)
- p = odgovarajuća finalna verovatnoća (npr. p*(k+r) za odbijene, ili suma verovatnoća "lošeg" ishoda)

Za **očekivano vreme provedeno u nekom stanju** tokom perioda T (npr. koliko su frizeri besposleni), formula je jednostavnija:

**Očekivano vreme u stanju A tokom perioda T = T · P(sistem je u stanju A)**

(ovde ne množiš sa λ, jer ne brojimo događaje nego direktno "udeo vremena").

## 11. Little-ov zakon (za kasnije, korisno je znati)

**L = λeff · W**

gde je L = očekivan broj u sistemu, W = očekivano vreme provedeno u sistemu po mušteriji, a λeff = efektivna stopa dolazaka (kod sistema sa odbijanjem: λeff = λ·(1 − p_odbijanja), jer odbijene mušterije "ne ulaze" u sistem).

## 12. Praktični saveti pre rešavanja zadataka

1. **Prvo izaberi vremensku jedinicu** (najčešće 1h ili 1 dan) i sve prevedi u nju pre računanja λ i μ.
2. **μ je uvek "po jednom serveru"**, ne za ceo sistem — ako ti daju ukupan učinak, podeli sa k.
3. Proveri tip sistema: da li red ima ograničenje (r konačno ili r=0) ili ne (r=∞) — to određuje da li ti treba geometrijski red ili konačna suma, i da li uopšte moraš da proveravaš uslov ρ<1.
4. Kad računaš "broj odbijenih/nagrađenih/itd. tokom perioda T", uvek množi: (broj dolazaka u T) × (odgovarajuća verovatnoća).
5. Kod finalnih verovatnoća, uvek na kraju proveri da Σp*n = 1 (bar približno, sabiranjem par prvih članova + rep geometrijskog reda).

---

Sa ovim bi trebalo da imaš sve što ti treba za Zadatke 1–5 (M|M|1|∞, M|M|2|∞, M|M|2|2, M|M|3|∞, M|M|3|0) — svaki od njih je samo primena tačaka 6 i 8-10 iznad, sa različitim k i r.