# Priprema: Lanci Markova (sve što ti treba pre zadataka)

## Legenda oznaka (pročitaj prvo ovo)

- **sⱼ** — "stanje broj j" (npr. s₁ = prvo stanje, s₂ = drugo stanje...). U konkretnim
  zadacima stanja često imaju imena umesto brojeva (npr. "voz", "autobus", "kolima").
- **Xₙ** — u kom stanju je sistem u trenutku (koraku) n. Xₙ = sⱼ znači "u trenutku n sistem
  je u stanju j".
- **pᵢⱼ** — verovatnoća prelaska iz stanja i u stanje j **za jedan korak**. Ovo su baš
  elementi matrice P (i-ti red, j-ta kolona).
- **pᵢⱼ(n)** — verovatnoća prelaska iz stanja i u stanje j **za n koraka**. Ovo su elementi
  matrice Pⁿ (P na n-ti stepen).
- **p(n)** — ceo vektor (red) verovatnoća da sistem bude u svakom od stanja u trenutku n.
  Npr. p(0) = [1/3, 2/3] znači "verovatnoća 1/3 da na početku budeš u stanju 1, verovatnoća
  2/3 da budeš u stanju 2".
- **pⱼ(n)** — samo j-ta komponenta tog vektora — verovatnoća da si baš u stanju j, u trenutku n.
- **p\*** — finalna (stacionarna) verovatnoća — vektor kojem se p(n) približava kad n → ∞.
- **pⱼ\*** — j-ta komponenta tog finalnog vektora.

Znači: mala slova sa jednim indeksom (pⱼ) — verovatnoća da si u stanju j.
Mala slova sa dva indeksa (pᵢⱼ) — verovatnoća prelaska i→j.
Dodatak "(n)" — kaže "za n koraka" ili "u trenutku n".
Zvezdica (*) — kaže "finalno, kad se sistem smiri".

To je sve — ostatak dokumenta koristi samo ove oznake.

---

## 0. Šta je uopšte lanac Markova — intuicija

Zamisli sistem koji svakog dana (koraka) "skače" iz jednog stanja u drugo, na slučajan način.
Ključna osobina (**Markov osobina**): da bi predvideo gde će sistem biti *sutra*, dovoljno je
znati gde je *danas* — ne zanima te cela istorija kako je stigao tu.

Formalno (uslovna verovatnoća da sutra budeš u j, dato SVE što se do sad dešavalo, jednaka je
uslovnoj verovatnoći da sutra budeš u j dato SAMO gde si danas):

**P(Xₙ₊₁ = j | Xₙ = i, Xₙ₋₁ = ..., X₀ = ...) = P(Xₙ₊₁ = j | Xₙ = i)**

Ovo je **jedina** stvar koju moraš intuitivno da "osetiš" — sve ostalo su posledice te ideje.

---

## 1. Matrica prelaza P (transition matrix)

Ako sistem ima stanja s₁, s₂, ..., sₖ, matrica prelaza je k×k matrica gde element **pᵢⱼ** (i-ti
red, j-ta kolona) znači "verovatnoća da iz stanja i odeš u stanje j za jedan korak":

**pᵢⱼ = P(Xₙ₊₁ = sⱼ | Xₙ = sᵢ)**

**Bitna osobina**: zbir svakog reda mora biti 1 (iz svakog stanja moraš negde otići za sledeći
korak, uključujući i mogućnost da ostaneš u istom stanju).

**Kako je praviš iz teksta zadatka**: pročitaš pravilo prelaska za svako stanje ponaosob i upišeš
te verovatnoće u odgovarajući red. Npr. "ako ide kolima, sutra jednakoverovatno ide vozom,
autobusom ili kolima" → ceo red za "kolima" je [1/3, 1/3, 1/3].

---

## 2. Matrica prelaza za n koraka: Pⁿ

Ovo je centralna formula cele oblasti (Chapman-Kolmogorov):

**pᵢⱼ(n) = P(Xₙ = sⱼ | X₀ = sᵢ) = (i,j)-ti element matrice Pⁿ**

**Intuicija**: da odeš iz i u j za n koraka, moraš proći kroz neko međustanje na svakom koraku —
matrično množenje automatski sabira sve moguće puteve kroz sva međustanja. Zato je verovatnoća
prelaska za n koraka baš n-ti stepen matrice P, ništa komplikovanije od toga.

Praktično: **P⁴ = (P²)²** — uvek je lakše kvadrirati nego množiti P sa sobom četiri puta. Ovaj
trik se koristi svuda u zadacima (npr. zadatak 3, 4, 8).

---

## 3. Raspodela verovatnoća u trenutku n: p(n)

Ako je p(0) = [p₁(0), p₂(0), ..., pₖ(0)] vektor verovatnoća da sistem *na početku* bude u svakom
od stanja, onda je raspodela posle n koraka:

**p(n) = p(0) · Pⁿ**

**Intuicija**: to je samo "ponderisano mešanje" — polaziš od neizvesnosti gde si na početku, i tu
neizvesnost "guraš" kroz n koraka tranzicija, a matrica Pⁿ ti kaže kuda sve i sa kojom težinom
ide svaki mogući put.

Specijalan slučaj: ako *sigurno* znaš početno stanje (npr. "kolima"), p(0) je vektor sa 1 na tom
mestu i 0 svuda drugde — tada je p(n) prosto odgovarajući **red** matrice Pⁿ (onaj koji odgovara
stanju "kolima").

---

## 4. Finalne (stacionarne) verovatnoće p\*

### Kada postoje?

**Dovoljan uslov (koji se koristi u svim ovim zadacima)**: ako postoji neki stepen n₀ takav da
matrica Pⁿ⁰ ima **sve elemente strogo pozitivne** (nema nula), onda finalne verovatnoće postoje.

Intuicija: ovo znači da iz bilo kog stanja možeš (za dovoljno koraka) da stigneš u bilo koje
drugo stanje sa pozitivnom verovatnoćom — sistem se "izmeša" i zaboravi odakle je krenuo. Kada
prođe dovoljno vremena, raspodela verovatnoća se ustali i više ne zavisi od početnog stanja.

**Kada NE postoje** (dva tipična razloga, oba se pojavljuju u zadatku 2):

- **Periodičnost** — Pⁿ osciluje između više različitih matrica i nikad se ne "smiruje"
  (zadatak 2a: P² = I, P³ = P, pa P^n stalno "skače" između te dve matrice i granica ne postoji).
- **Matrica Pⁿ konvergira, ali redovi granične matrice nisu međusobno jednaki** — tada granica
  postoji, ali to nije "prava" finalna raspodela nezavisna od početnog stanja (zadatak 2b:
  Pⁿ = P za svako n, ali redovi P nisu isti — polazeći iz različitih stanja dobijaš različit
  dugoročni ishod, tipično kod apsorbujućih stanja).

**Formalni kriterijum**: finalne verovatnoće postoje akko lim (n→∞) Pⁿ = P\*, gde P\* ima **sve
redove međusobno jednake**, i taj zajednički red je baš vektor p\*.

### Kako ih računaš

Rešavaš sistem:

**p\* · P = p\*** (stacionarnost — raspodela se ne menja kad je pomnožiš sa P)

**p₁\* + p₂\* + ... + pₖ\* = 1** (normalizacija — verovatnoće moraju da se saberu u 1)

**Intuicija za p\*·P = p\***: ako si već u "ravnotežnom" stanju, jedan korak tranzicije te ostavlja
u istoj (agregatnoj) raspodeli — kao mešanje boje koja se više ne menja bez obzira koliko dugo
mešaš.

**Praktični trik za rešavanje**: uzmeš k−1 jednačina iz p\*P = p\* (jedna je uvek suvišna, tj.
linearno zavisna od ostalih — to je normalno) i dodaš jednačinu zbira = 1.

### Interpretacija p\*

pᵢ\* = dugoročni **udeo vremena** koji sistem provede u stanju i, ako posmatraš jako dug period.
(Zadatak 6b, 8b: "koliko vremena provede u Somboru" = baš pSombor\*.)

---

## 5. Lančano pravilo (chain rule) + Markov osobina za spojene/uslovne verovatnoće

Ovo je formula koja izgleda zastrašujuće u zadacima 3(d)–(g) i 6(d), ali je mehanička kad je
jednom razumeš.

### Osnovna ideja

Za bilo koji niz vremenskih trenutaka t₁ < t₂ < ... < tₘ, verovatnoća da sistem prođe baš kroz
ta stanja u tim trenucima je proizvod:

**P(Xₜ₁=a₁, Xₜ₂=a₂, ..., Xₜₘ=aₘ) = P(Xₜ₁=a₁) · P(Xₜ₂=a₂|Xₜ₁=a₁) · P(Xₜ₃=a₃|Xₜ₂=a₂) · ... · P(Xₜₘ=aₘ|Xₜ₍ₘ₋₁₎=a₍ₘ₋₁₎)**

**Ključne dve stvari koje ti Markov osobina daje**:

1. Uslovljavanje na više prošlih trenutaka svodi se na uslovljavanje samo na **poslednji**
   poznati trenutak (jer budućnost zavisi samo od "sada", ne od cele istorije).
2. Ako su dva trenutka udaljena za "gap" koraka (npr. t₃ − t₂ = 2), koristiš verovatnoću za
   **taj broj koraka**, ne za jedan korak! Dakle P(Xₜ₃=a₃|Xₜ₂=a₂) = element matrice P podignute
   na stepen (t₃−t₂), na poziciji (a₂, a₃).

### Recept korak po korak (npr. zadatak 3d)

1. Poređaj trenutke po vremenu.
2. Prva verovatnoća: P(Xₜ₁ = a₁) — ili je 1 (ako je to dato/uslovljeno), ili je iz vektora p(t₁).
3. Svaki sledeći faktor: element matrice P na stepen "gap" (gap = razlika u vremenu između ta
   dva trenutka), na poziciji (prethodno stanje → sledeće stanje).
4. Pomnožiš sve dobijene brojeve.

### Uslovna verovatnoća P(A|B) kad B nije samo "poslednji trenutak pre A"

Koristiš definiciju P(A|B) = P(A∩B) / P(B), pa oboje izračunaš gornjim receptom pa podeliš
(zadatak 3e, 3f, 6d). Kod ovoga pazi: kad je uslov na **budući** trenutak u odnosu na neke od
događaja u A (npr. zadatak 3f: uslov je X₁=v, X₂=k, a traži se i X₀=k koji je *pre* toga!),
matematika je ista — samo pažljivo primeniš chain rule prateći hronologiju (X₀ pa X₁ pa X₂...),
a ne redosled kojim su događaji napisani u tekstu zadatka.

### Beskonačan proizvod (zadatak 3g)

**P(X₂=k, X₄=k, X₆=k, ...) = pₖ(2) · pₖₖ(2) · pₖₖ(2) · ... = lim (n→∞) [pₖₖ(2)]ⁿ**

Ako je pₖₖ(2) < 1, ova granica je **0** — intuitivno: verovatnoća da nešto pozitivno-verovatno-
ali-manje-od-1 uspe *beskonačno mnogo puta zaredom* teži nuli.

---

## 6. Random walk po grafu (zadatak 5)

Kada se "čestica" kreće po čvorovima grafa birajući *jednako verovatno* jednog od povezanih
suseda, verovatnoća prelaska je:

**pᵢⱼ = 1 / deg(i)** ako su čvorovi i, j povezani granom, inače 0

gde je deg(i) broj grana koje izlaze iz čvora i (broj suseda). Ovo je samo specijalan način da
napraviš matricu P — sve ostalo (Pⁿ, p(n), p\*) radi se identično kao u prethodnim delovima.

---

## 7. "Ne ide dva dana zaredom u X" / zabranjena stanja (zadatak 3, 6, 8)

Kad tekst kaže "ne ide vozom dva dana uzastopno", to znači: u redu matrice P koji odgovara
stanju "voz", element u koloni "voz" je 0 — sve ostalo se raspoređuje po datim odnosima (npr.
"kolima 2x verovatnije nego autobusom" → kolima = 2/3, autobus = 1/3 od preostale verovatnoće).

---

## 8. Brzi podsetnik: množenje matrica (da ne praviš računsku grešku)

Za p(0)·P: j-ti element rezultata = zbir po i od [ pᵢ(0) · pᵢⱼ ] (množiš vektor-red sa
odgovarajućom kolonom matrice, sabereš).

Za P·P: element na poziciji (i,j) rezultata = zbir po k od [ pᵢₖ · pₖⱼ ] (i-ti red prve matrice
puta j-ta kolona druge, sabereš).

Ovo je mesto gde se najviše greši računski — uvek proveri da li ti se redovi rezultujuće
matrice (ili ceo vektor p(n)) sabiraju u 1. Ako ne — negde je greška.

---

## Mapa: koja formula ti treba za koji tip pitanja

| Pitanje u zadatku | Šta radiš |
|---|---|
| "Da li postoje finalne verovatnoće?" | Nađi Pⁿ dok ne dobiješ sve elemente > 0 (ili pokaži da Pⁿ ne konvergira ka matrici sa jednakim redovima) |
| "Naći finalne verovatnoće" | Reši p\*·P = p\*, uz p₁\*+p₂\*+...+pₖ\*=1 |
| "Verovatnoća da je u stanju j posle n koraka, počev od stanja i" | Element (i,j) matrice Pⁿ |
| "Raspodela posle n koraka, dat početni vektor p(0)" | p(0)·Pⁿ |
| "Verovatnoća niza događaja u različitim trenucima" | Chain rule: proizvod P-na-stepen-gap između svaka dva uzastopna trenutka |
| "Uslovna verovatnoća P(A\|B)" | P(A∩B)/P(B), oba preko chain rule |
| "Udeo vremena u stanju i na duge staze" | pᵢ\* (finalna verovatnoća tog stanja) |
| "Verovatnoća beskonačnog ponavljanja istog prelaza" | granica [pᵢᵢ(gap)]ⁿ kad n→∞ → 0 ako je baza < 1 |

---

## Redosled kojim bih ja rešavao ovih 8 zadataka

1. **Zadatak 1, 2** — najčistiji uvod u Pⁿ i finalne verovatnoće (uključujući slučajeve kad NE
   postoje — obavezno razumi zašto u 2a i 2b, to je klasika na ispitu).
2. **Zadatak 4, 6** — standardna primena: napraviš P iz teksta, nađeš Pⁿ, nađeš p\*.
3. **Zadatak 3, 8** — dodaje se chain rule za spojene/uslovne verovatnoće kroz vreme (najviše
   poena obično nosi ovaj tip).
4. **Zadatak 5** — kratak, samo primena random walk-a na grafu.
5. **Zadatak 7** — sličan zadacima 1/2, dobra vežba za kraj.

Kad savladaš ideje iz tačaka 1–5 ovog dokumenta, svih 8 zadataka su varijacije na isti
mehanizam. Javi kad hoćeš da pređemo zadatak po zadatak — mogu da te vodim kroz svaki, ili da
prvo probaš sam pa ti proverim rešenje.