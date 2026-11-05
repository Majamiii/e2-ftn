# Rok 2 — rešenja

## Eliminacioni deo — `1.jpg`

*Sve ispravno odgovoreno donosi 10 poena; jedna ili više grešaka donosi 0 poena na celom ispitu.*

---

### 1. Napisati (u Ce++) telo funkcije `foo` tako da njeno vreme izvršavanja na jednom jezgru ima asimptotski usku granicu Θ(n³)

```cpp
void foo(int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                cout << "nesto" << endl;
}
```

Tri ugnježdene petlje po `n` iteracija, telo Θ(1) → Θ(n³).

---

### 2. Koliki je rad funkcije `foo` iz prethodnog pitanja?

> $T_1 = \Theta(n^3)$

Rad je vreme izvršavanja na jednom procesoru, a ono za `foo` ima asimptotski usku granicu Θ(n³).

---

### 3. Za dati kod nacrtati graf toka upravljanja i obeležiti osnovne blokove (`use` i `def` skupovi)

```c
int foo (int x, int y)
{
    int b, z, a = 5;
    if (x > 5)
        z = y - a;
    else
        z = x;
    b = 7;
    return z - b;
}
```

```
              +----------------+
              |  B1            |   def = {a}
              |    a = 5       |   use = {x}
              |    x > 5       |
              +----------------+
                 |          |
            da   |          |   ne
                 v          v
   +---------------+    +---------------+
   |  B2           |    |  B3           |
   |    z = y - a  |    |    z = x      |
   +---------------+    +---------------+
   def = {z}            def = {z}
   use = {y, a}         use = {x}
                 |          |
                 v          v
              +----------------+
              |  B4            |   def = {b}
              |    b = 7       |   use = {z, b}
              |    return z-b  |
              +----------------+
```

`def` su promenljive kojima blok zadaje vrednost, `use` one koje očitava. Skupovi nisu disjunktni: u B4 se `b` i definiše (`b = 7`) i koristi (`return z - b`).

---

### 4. Koliko u gramatici ima terminalnih simbola? Zaokružiti ih.

```
S -> x = P            P -> 2 - F            F -> x
S -> F = 2 - P / t    P -> F / t            F -> 2 - P
```

> **6 terminalnih simbola:** `x`, `=`, `2`, `-`, `/`, `t`

Neterminali su `S`, `P`, `F` (javljaju se sa leve strane produkcija). Sve ostalo su terminali. Broje se **različiti simboli**, ne njihova pojavljivanja.

---

### 5. Ako graf ima 4 čvora i svaki čvor ima rang 3

**a) Koliko taj graf ima ivica?**

Zbir rangova svih čvorova jednak je dvostrukom broju ivica:

$$4 \cdot 3 = 12 = 2E \quad\Rightarrow\quad E = 6$$

> **6 ivica**

**b) Koji je najmanji broj boja sa kojim može biti obojen?**

Svaki čvor je susedan sa preostala 3 — to je **potpun graf K₄**. U potpunom grafu su svaka dva čvora susedna, pa nikoja dva ne mogu deliti boju.

> **4 boje**

---

### 6. Šta je tačno, a šta nije?

- ❌ a) Tabela simbola pridružuje kod operacije broju koji predstavlja njegovu vrednost.
- ❌ b) Tabela simbola definiše razliku između mašinskih i pseudo instrukcija.
- ❌ c) Popunjena tabela simbola je ulaz u prvi prolaz asemblera (tj. ugrađena je u asembler).
- ✅ **d) Popunjena tabela simbola je izlaz iz prvog prolaza asemblera.**

Tabela simbola pridružuje **simbol** broju koji predstavlja njegovu vrednost. Razliku između mašinskih i pseudo operacija definiše **tabela koda operacije**. Prvi prolaz **popunjava** tabelu simbola, drugi je **koristi**.

---

## Glavni deo — `2.jpg` – `4.jpg`

*Ispravan odgovor donosi 4 poena, negativnih bodova nema.*

---

### 1. Primenom Master teoreme odrediti asimptotsko ograničenje za T(n) = 24,7·T(n/3) + n²

$a = 24{,}7$, $b = 3$, $f(n) = n^2$

$$\log_b a = \log_3 24{,}7 = 2{,}919 \quad\Rightarrow\quad n^{\log_b a} = n^{2,919}$$

Provera: $3^3 = 27 > 24{,}7$, pa je $\log_3 24{,}7$ nešto malo manje od 3.

Poređenje: $f(n) = n^2$ je **polinomijalno manja** od $n^{2,919}$ — važi $n^2 = O(n^{2,919-\varepsilon})$ za npr. $\varepsilon = 0{,}5$. To je **slučaj 1**.

> $$T(n) = \Theta\!\left(n^{\log_b a}\right) = \Theta\!\left(n^{\log_3 24,7}\right) \approx \Theta(n^{2,919})$$

**Pazi:** ovde je veća funkcija $n^{\log_b a}$, pa ona određuje rešenje. (Uporedi sa `T(n) = 7T(n/8) + n lg n`, gde je veća `f(n)`, pa je odgovor `Θ(n lg n)`.)

---

### 2. Koje osobine mora da ima invarijanta petlje da bi algoritam bio korektan?

Invarijanta petlje se koristi za dokaz da je algoritam korektan. Potrebno je pokazati **tri osobine**:

1. **Inicijalizacija** — istinita je pre prve iteracije petlje.
2. **Održavanje** — ako je istinita pre iteracije petlje, ostaje istinita posle iteracije.
3. **Završetak** — kada se petlja završi, invarijanta daje korisnu osobinu za dokazivanje korektnosti.

Velika je sličnost sa matematičkom indukcijom, s tim što se ovde postupak zaustavlja kada se petlja završi.

---

### 3. Rad 2048s i raspon 1s izmenjeni na rad 1024s i raspon 8s. Kako su se promenile gornje i donje granice na 32 i 512 jezgara?

Donja granica: $T_P \ge \max(T_1/P,\ T_\infty)$. Gornja granica: $T_P \le T_1/P + T_\infty$.

| | $P$ | donja | gornja |
|---|---|---|---|
| original | 32 | $\max(64, 1) = 64$ | $64 + 1 = 65$ |
| izmenjen | 32 | $\max(32, 8) = 32$ | $32 + 8 = 40$ |
| original | 512 | $\max(4, 1) = 4$ | $4 + 1 = 5$ |
| izmenjen | 512 | $\max(2, 8) = 8$ | $2 + 8 = 10$ |

> **Na 32 jezgra** obe granice su se smanjile (64 → 32 i 65 → 40) — **poboljšanje**.
>
> **Na 512 jezgara** obe granice su se povećale (4 → 8 i 5 → 10) — **pogoršanje**.

Na malom broju jezgara dominira rad, pa se isplati njegovo smanjenje. Na velikom broju jezgara dominira raspon, pa ga povećanje sa 1s na 8s odmah pokvari.

---

### 4. Poželjne osobine međukoda su

- **a)** Pogodan je za davanje značenja čvorovima stabla sintaksne analize
- **b)** Pogodan je za prevođenje u mašinski jezik odredišnog procesora
- **c)** Čvorovi stabla međukoda treba da imaju jasna i jednostavna značenja
  *(radi lake specifikacije i realizacije optimizacionih transformacija)*

---

### 5. Zadatu gramatiku transformisati u gramatiku bez konflikta

```
E -> E + T          T -> id
E -> E - T          T -> num
E -> T              T -> ( E )
```

Gramatika je **levo rekurzivna**, a leva rekurzija je specijalan slučaj preklapanja `FIRST` skupova dve produkcije. Uklanja se prevođenjem u desnu rekurziju:

```
E  -> T E'          T -> id
E' -> + T E'        T -> num
E' -> - T E'        T -> ( E )
E' -> ε
```

**Pazi:** produkcije za `E'` moraju imati **repno `E'`**. Bez njega bi izraz mogao imati najviše jedan operator.

---

### 6. Pored svake petlje napisati da li je dobro formirana

```c
for (i = 0; i < foo(y); ++i) { y = (y + x) % 7; }
```
> **Nije** — `foo(y)` se računa svake iteracije, a `y` se menja u telu.

```c
i = 0; while (i < 10) { y *= x; i += 1; }
```
> **Jeste**, *veoma dobro formirana* — broj iteracija (10) poznat je pri prevođenju.

```c
for (i = 7; i < N; i += 5) { y /= z; }
```
> **Jeste** — `N` se ne menja u telu, pa je broj iteracija poznat pre prve iteracije.

```c
for (i = 6; i <= 100; i *= 5) { y += i; }
```
> **Nije** — `i *= 5` nije kanonički oblik.

---

### 7. Tokom asembliranja datog MIPS koda, koje su vrednosti simbola `val1` i `end`?

```mips
.globl main
.data                               # brojač lokacija = 0
arr1:   .word 5 87 54 63            # 0   (4 x 4 = 16 B)
arr2:   .word 16                    # 16  (4 B)
val1:   .space 9                    # 20  (9 B)
.text                               # brojač lokacija = 0
main:
        la $t1, arr1                # 0
        la $t2, arr2                # 4
        lw $t3, val1                # 8
end:
        jr $ra                      # 12
```

> **val1 = 20**, **end = 12**

---

### 8. Za dati graf toka upravljanja nacrtati graf smetnji, pa zaokružiti tačne i precrtati netačne tvrdnje

```
1: a := 0
2: b := a + 1     <- povratna grana iz čvora 5
3: c := c + b
4: a := b * 2
5: a < N          -> nazad na 2, ili dalje na 6
6: return c
```

Rešenje jednačina životnog veka:

| Čvor | `def` | `use` | `in` | `out` |
|---|---|---|---|---|
| 1 | a | — | c | a, c |
| 2 | b | a | a, c | b, c |
| 3 | c | c, b | b, c | b, c |
| 4 | a | b | b, c | a, c |
| 5 | — | a | a, c | a, c |
| 6 | — | c | c | — |

**Graf smetnji.** Promenljiva koja se definiše u čvoru je u smetnji sa svim promenljivima živim na izlazu iz tog čvora:

- čvor 1 definiše `a`, `out[1] = {a, c}` → **a — c**
- čvor 2 definiše `b`, `out[2] = {b, c}` → **b — c**
- čvor 3 definiše `c`, `out[3] = {b, c}` → **b — c**
- čvor 4 definiše `a`, `out[4] = {a, c}` → **a — c**

Brojevi u zagradi su boje (registri):

```
   a(1) --------- c(2) --------- b(1)
```

Grane: `a—c` i `b—c`. Grane `a—b` **nema**, pa `a` i `b` mogu deliti isti registar. Graf je 2-obojiv — dovoljna su dva registra.

- ❌ a) Životni vek promenljive `a` i `b` se preklapa — nijedan `in`/`out` skup ne sadrži i `a` i `b`.
- ❌ b) Promenljive `a` i `b` su u smetnji preko `c` — smetnja **nije tranzitivna**. To što su obe u smetnji sa `c` ne znači da su u smetnji međusobno; `a` i `b` mogu deliti isti registar.
- ✅ **c) Promenljive `a` i `c` su u smetnji** — `c` je živa tamo gde se `a` definiše (čvorovi 1 i 4).
- ✅ **d) Promenljiva `c` je živa na izlazu iz čvora 2** — `out[2] = {b, c}`.

---

### 9. Koje su vrste zavisnosti u grafu toka podataka?

1. **RAW — čitanje posle pisanja** (*prava*, true). Izlaz iz `I₁` je ulaz u `I₂`.
2. **WAR — pisanje posle čitanja** (*antizavisnost*, anti). Izlaz iz `I₂` je ulaz u `I₁`.
3. **WAW — pisanje posle pisanja** (*izlazna*, output). Izlaz iz `I₁` je izlaz i iz `I₂`.

---

### 10. Ukratko opiši BSS punjač

**BSS punjač** omogućava punjenje **više segmenata programa** nad samo **jednim zajedničkim segmentom podataka**.

Izlaz iz asemblera je prevedeni program i informacija o svim drugim programima na koje se on poziva. Navodi se i informacija o tome koje reference treba menjati — **relokaciona informacija**.

Za povezivanje koristi **vektor prelaza** (`foo1: call addr1`, `foo2: call addr2`, …).

**Nedostaci:**

- Vektor prelaza zauzima prostor u memoriji, a koristi se samo za povezivanje.
- Obrađuje segmente procedura, ali ne olakšava pristup segmentima deljivih podataka.
