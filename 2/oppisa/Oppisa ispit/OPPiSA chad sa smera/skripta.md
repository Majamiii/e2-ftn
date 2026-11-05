---
title: "Paralelno programiranje i softverski alati — pitanja sa rokova"
lang: sr
---

# Sadržaj

1. [Međukod](#1-međukod)
2. [Analiza životnog veka](#2-analiza-životnog-veka)
3. [Cilk](#3-cilk)
4. [Asembler](#4-asembler)
5. [Analiza efikasnosti algoritama](#5-analiza-efikasnosti-algoritama)
6. [Rad i raspon](#6-rad-i-raspon)
7. [Osnovni blokovi](#7-osnovni-blokovi)
8. [Formalne gramatike](#8-formalne-gramatike)
9. [Dodela resursa — bojenje grafa](#9-dodela-resursa--bojenje-grafa)
10. [Povezivač i punjač](#10-povezivač-i-punjač)
11. [Raspoređivanje instrukcija](#11-raspoređivanje-instrukcija)
12. [Lingvistički nivoi](#12-lingvistički-nivoi)
13. [Kompaktor](#13-kompaktor)
14. [Izbor instrukcija](#14-izbor-instrukcija)
15. [Paralelno programiranje](#15-paralelno-programiranje)
16. [Leksička analiza](#16-leksička-analiza)

> 🔴 = **eliminaciono pitanje** — bez njega se ispit ne može položiti.
>
> Na rokovima je **prva strana uvek eliminacioni deo** (sve ispravno = 10 poena, jedna greška = 0 poena na celom ispitu), a od druge strane počinje **glavni deo** (ispravan odgovor 4 poena, bez negativnih bodova).

---

# 1. Međukod

### 1.1 _(dopunjavanje)_ — _ponavlja se na više rokova_

**Poželjne osobine međukoda su:**

- **a)** Pogodan je za davanje značenja čvorovima stabla sintaksne analize
- **b)** Pogodan je za prevođenje u mašinski jezik odredišnog procesora
- **c)** Čvorovi stabla međukoda treba da imaju jasna i jednostavna značenja
  _(radi lake specifikacije i realizacije optimizacionih transformacija)_

### 1.2 _(dopunjavanje)_

**Dve osobine kanoničkog stabla međukoda su:**

- **a)** Ne sadrži `SEQ` čvorove (niz od dva iskaza) ni `ESEQ` čvorove (niz od jednog iskaza i jednog izraza)
- **b)** Predak `CALL` čvora (poziv funkcije) je čvor `EXP` (izraz) ili `MOVE` (prebaci rezultat izraza u zadatu lokaciju)

---

# 2. Analiza životnog veka

### 2.1 _(dopunjavanje)_

**Napisati jednačine životnog veka promenljivih za čvor n. Objasniti značenje svih elemenata u jednačinama.**

$$in[n] = use[n] \cup (out[n] - def[n])$$

$$out[n] = \bigcup_{succ[n]} in[s]$$

Značenje elemenata:

- $in[n]$ — promenljive koje žive na ulazu u čvor
- $out[n]$ — promenljive koje žive na izlazu čvora
- $use[n]$ — promenljive koje čvor koristi
- $def[n]$ — promenljive koje čvor definiše
- $\bigcup_{succ[n]}$ — unija po svim čvorovima naslednicima čvora n

### 2.2 🔴 _(zaokruživanje)_

**Za dati graf toka upravljanja zaokružiti tačne i precrtati netačne tvrdnje.**

```
1: a := 0
2: b := a + 1     <- povratna grana iz čvora 5
3: c := c + b
4: a := b * 2
5: a < N          -> nazad na 2, ili dalje na 6
6: return c
```

| Čvor | `def` | `use` |
| ---- | ----- | ----- |
| 1    | a     | —     |
| 2    | b     | a     |
| 3    | c     | c, b  |
| 4    | a     | b     |
| 5    | —     | a     |
| 6    | —     | c     |

- ✅ **a) Promenljiva `a` je živa na ulazu u čvor 2** — čvor 2 koristi `a`.
- ❌ b) Promenljiva `b` se koristi u čvoru 2 — tu se `b` **definiše**.
- ✅ **c) Promenljiva `a` je živa na izlazu iz čvora 4** — naslednik (čvor 5) koristi `a`.
- ✅ **d) Promenljiva `c` se koristi u čvoru 3** — `c := c + b`.

### 2.3 _(zaokruživanje)_

**Za dati graf toka upravljanja zaokružiti tačne i precrtati netačne tvrdnje.** _(isti graf kao u 2.2)_

Rešenje jednačina životnog veka:

| Čvor | `in` | `out` |
| ---- | ---- | ----- |
| 1    | c    | a, c  |
| 2    | a, c | b, c  |
| 3    | b, c | b, c  |
| 4    | b, c | a, c  |
| 5    | a, c | a, c  |
| 6    | c    | —     |

- ❌ a) Životni vek promenljive `a` i `b` se preklapa — nijedan skup ne sadrži i `a` i `b`.
- ✅ **b) Promenljiva `c` je živa na izlazu iz čvora 2** — `out[2] = {b, c}`.
- ✅ **c) Promenljive `a` i `c` su u smetnji** — `c` je živa na mestu gde se `a` definiše (čvorovi 1 i 4).
- ✅ **d) Promenljiva `c` je živa na ulazu u čvor 2** — `in[2] = {a, c}`.

### 2.4 🔴 _(zaokruživanje)_

**Za dati graf toka upravljanja zaokružiti tačne i precrtati netačne tvrdnje.** _(isti graf kao u 2.2)_

- ✅ **a) Promenljiva `c` se definiše u čvoru 3** — `c := c + b`.
- ✅ **b) Promenljiva `a` je živa na ulazu u čvor 5** — `in[5] = {a, c}`, čvor 5 koristi `a`.
- ✅ **c) Promenljiva `a` je živa na izlazu iz čvora 4** — `out[4] = {a, c}`.
- ❌ d) Promenljiva `b` se definiše u čvoru 4 — u čvoru 4 (`a := b * 2`) se `b` **koristi**, a definiše se `a`.

### 2.5 🔴 _(zaokruživanje)_

**Za dati graf toka upravljanja zaokružiti tačne i precrtati netačne tvrdnje.** _(isti graf kao u 2.2)_

- ✅ **a) Promenljiva `c` se koristi (use) u čvoru 3** — `c := c + b`.
- ❌ b) Promenljiva `b` se koristi (use) u čvoru 2 — tu se `b` **definiše**.
- ✅ **c) Promenljiva `a` je živa na izlazu iz čvora 4** — `out[4] = {a, c}`.
- ✅ **d) Promenljiva `a` je živa na ulazu u čvor 2** — `in[2] = {a, c}`.

### 2.6 🔴 _(zaokruživanje)_

**Za dati graf toka upravljanja nacrtati graf smetnji, pa zaokružiti tačne i precrtati netačne tvrdnje.** _(isti graf kao u 2.2)_

Promenljiva koja se definiše u čvoru je u smetnji sa svim promenljivima živim na izlazu iz tog čvora:

- čvor 1 definiše `a`, `out[1] = {a, c}` → grana **a — c**
- čvor 2 definiše `b`, `out[2] = {b, c}` → grana **b — c**
- čvor 3 definiše `c`, `out[3] = {b, c}` → grana **b — c**
- čvor 4 definiše `a`, `out[4] = {a, c}` → grana **a — c**

Graf smetnji (brojevi u zagradi su boje/registri):

```
   a(1) --------- c(2) --------- b(1)
```

Grane `a — b` **nema**, pa `a` i `b` mogu deliti isti registar. Graf je 2-obojiv.

- ❌ a) Životni vek promenljive `a` i `b` se preklapa — nijedan `in`/`out` skup ne sadrži i `a` i `b`.
- ❌ b) Promenljive `a` i `b` su u smetnji preko `c` — **smetnja nije tranzitivna.** To što su obe u smetnji sa `c` ne znači da su u smetnji međusobno; `a` i `b` mogu deliti isti registar.
- ✅ **c) Promenljive `a` i `c` su u smetnji** — `c` je živa tamo gde se `a` definiše.
- ✅ **d) Promenljiva `c` je živa na izlazu iz čvora 2** — `out[2] = {b, c}`.

### 2.7 🔴 _(dopunjavanje)_

**Od koje do koje linije traje životni vek promenljive `a`?**

```c
1.  int foo (int x, int y) {
2.      int b, z, a = x - 2;
3.      b = 4 + a;
4.      b += a * y;
5.      z = 1 + b;
6.      return z - a;
7.  }
```

> **Životni vek počinje u liniji 2 i završava se u liniji 6.**

Promenljiva je živa od svoje **definicije** do **poslednje upotrebe**:

- linija 2 — `a = x - 2`, definicija
- linije 3 i 4 — upotrebe
- linija 5 — `a` se ne pominje, ali je i dalje živa
- linija 6 — `return z - a`, poslednja upotreba

> **Pazi na liniju 5.** Promenljiva je živa na strelici grafa ako postoji putanja od te strelice do `use` čvora koja ne prelazi preko nijednog `def` čvora. Iz linije 5 postoji takva putanja do upotrebe u liniji 6, pa je `a` živa i tu — iako se ne pominje.

### 2.8 _(dopunjavanje)_

**Dva pravila za dodavanje nove smetnje u graf smetnji glase:**

1. Za svaku **definiciju promenljive `a` u čvoru koji nije `MOVE`**, dodaj smetnje između `a` i **svake promenljive žive na izlazu čvora**.
2. Za **`MOVE` instrukciju `a = c`**, dodaj smetnje između `a` i svake promenljive žive na izlazu čvora **koja nije `c`**.

> Drugo pravilo postoji zato što `a` i `c` posle `MOVE`-a imaju **istu vrednost**, pa mogu deliti registar. Time se omogućava kasnije uklanjanje suvišnih `MOVE` instrukcija spajanjem čvorova.

---

# 3. Cilk

**Podsetnik:** petlja je _dobro formirana_ ako se broj iteracija zna unapred — tokom prevođenja (_veoma dobro formirana_) ili bar pre prve iteracije.

`cilk_for` je kraći zapis za **rekurziju podeli-pa-vladaj**, pa mu je raspon $\Theta(\lg n)$. Obična `for` petlja ima raspon $\Theta(n)$.

### 3.1 _(dopunjavanje)_

**Pored svake petlje napisati da li je dobro formirana. Ako nije, kratko opisati zbog čega.**

**a)**

```c
for (i = 0; i < foo(y); ++i) {
  y = (y + x) % 7;
}
```

> **Nije dobro formirana** — `foo(y)` se računa svake iteracije, a `y` se menja u telu, pa se broj iteracija ne zna unapred.

**b)**

```c
i = 0;
while (i < 10) {
  y *= x;
  i += 1;
}
```

> **Dobro formirana** — broj iteracija (10) poznat je već tokom prevođenja, dakle _veoma dobro formirana_.

**c)**

```c
for (i = 7; i < N; i += 5) {
  y /= z;
}
```

> **Dobro formirana** — `N` se ne menja u telu, pa je broj iteracija poznat pre prve iteracije. Nije _veoma dobro formirana_ jer `N` nije poznato tokom prevođenja.

**d)**

```c
for (i = 6; i <= 100; i *= 5) {
  y += i;
}
```

> **Nije dobro formirana** — `i *= 5` nije kanonički oblik; iteraciona promenljiva se množi umesto da se uvećava za konstantan korak.

### 3.2 🔴 _(zaokruživanje)_

**Za date petlje sa nezavisnim iteracijama, zaokružiti tačne a precrtati netačne tvrdnje.**

```c
_Cilk_for (int i = 0; i < N; i++) {      for (int i = 0; i < N; i++) {
    foo(i);                                  _Cilk_spawn foo(i);
}                                        }
                                         _Cilk_sync;
```

- ✅ **a) Obe petlje daju isti rezultat.**
- ✅ **b) Obe petlje imaju jednako vreme izvršavanja na procesoru sa jednim jezgrom.**
- ❌ c) Obe petlje imaju isti raspon.

> Serijalizacija obe petlje daje isti kod — običnu `for` petlju sa `n` poziva `foo`. Zato je i rezultat isti (a) i rad isti, pa i vreme na jednom jezgru (b).
>
> Razlikuju se samo po **rasponu**: `_Cilk_for` se rekurzivno polovi → $\Theta(\lg n)$; kod druge petlje je sama `for` petlja serijska → $\Theta(n)$.

### 3.3 🔴 _(dopunjavanje)_

**Koliki je rad za svaku od petlji iz prethodnog pitanja? Kratko obrazložiti.**

> $T_1 = \Theta(n)$ za **obe** petlje.
>
> Rad je vreme izvršavanja na jednom procesoru. Serijalizacija obe petlje je obična `for` petlja sa `n` poziva funkcije `foo`.

### 3.4 _(zadatak)_

**Dat je sledeći kod. Kako bi izgledao kod podjednakih svojstava u smislu rada i raspona, ali koji bi koristio samo `_Cilk_spawn` i `_Cilk_sync`?**

```c
_Cilk_for (int i = 0; i < N; i++)
    do_something(i);
```

`_Cilk_for` je skraćeni zapis za rekurziju podeli-pa-vladaj:

```c
void recursion(int start, int end) {
    if (end - start <= 1) {
        for (int i = start; i < end; ++i)
            do_something(i);
    }
    else {
        int middle = start + (end - start) / 2;
        _Cilk_spawn recursion(start, middle);
        recursion(middle, end);
        _Cilk_sync;
    }
}

recursion(0, N);
```

> Rad $\Theta(N)$, raspon $\Theta(\lg N)$ — isto kao `_Cilk_for`.
>
> **Nije rešenje** staviti `_Cilk_spawn` unutar obične `for` petlje: tada je sama petlja serijska, pa raspon postaje $\Theta(N)$.

---

# 4. Asembler

### 4.1 _(dopunjavanje)_

**Tokom asembliranja datog MIPS asemblerskog koda, koja će biti vrednost simbola `val1`, a koja vrednost simbola `end`?** Sekcije `.data` i `.text` počinju na adresi 0, literali (parametri `.word`) i instrukcije su 4 bajta, a parametar `.space` direktive predstavlja broj bajtova.

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

> **val1 = 20**
> **end = 12**

### 4.1b *(dopunjavanje)* — *varijanta prethodnog*

**Isti zadatak, drugi brojevi i pomerena labela `end`.**

```mips
.globl main
.data                       # brojač lokacija = 0
arr1:   .word 5 87 63       # 0   (3 x 4 = 12 B)
arr2:   .word 10            # 12  (4 B)
val1:   .space 4            # 16  (4 B)
.text                       # brojač lokacija = 0
main:
        la $t1, arr1        # 0
        la $t2, arr2        # 4
end:
        lw $t3, val1        # 8
        jr $ra              # 12
```

> **val1 = 16**, **end = 8**

**Dve zamke.** `arr1` ovde ima **tri** vrednosti, ne četiri → zauzima 12 B. A labela `end` stoji **iznad `lw`**, ne iznad `jr $ra` → pokazuje na treću instrukciju.

### 4.2 🔴 _(zaokruživanje)_

**Šta je tačno, a šta nije?**

- ❌ a) Tabela simbola definiše razliku između mašinskih i pseudo instrukcija.
- ✅ **b) Popunjena tabela simbola je izlaz iz prvog prolaza asemblera.**
- ❌ c) Popunjena tabela simbola je ulaz u prvi prolaz asemblera.
- ❌ d) Tabela simbola pridružuje kod operacije broju koji predstavlja njegovu vrednost.

> **a)** Razliku između mašinskih i pseudo operacija definiše **tabela koda operacije**, ne tabela simbola.
> **c)** Popunjena tabela simbola je ulaz u **drugi** prolaz. Prvi prolaz je popunjava.
> **d)** Tabela simbola pridružuje **simbol** broju koji predstavlja njegovu vrednost — ne kod operacije.

### 4.3 🔴 _(zaokruživanje)_ — _varijanta prethodnog_

**Šta je tačno, a šta nije?**

- ❌ a) Tabela simbola definiše razliku između mašinskih i pseudo instrukcija.
- ✅ **b) Popunjena tabela simbola je ulaz u drugi prolaz asemblera.**
- ❌ c) Popunjena tabela simbola je ulaz u prvi prolaz asemblera (tj. ugrađena je u asembler).
- ❌ d) Tabela simbola pridružuje kod operacije broju koji predstavlja njegovu vrednost.

> Prvi prolaz **popunjava** tabelu simbola; drugi prolaz je **koristi**. Zato je popunjena tabela izlaz iz prvog i ulaz u drugi prolaz.

### 4.4 _(dopunjavanje)_

**Navesti osnovne module asemblera i skicirati odnos među njima.**

**Četiri osnovna modula:**

1. **Modul za prvi prolaz**
2. **Modul za drugi prolaz**
3. **Modul za izračunavanje izraza** — u I prolazu za obradu `EQU`, u II prolazu za određivanje vrednosti operanada
4. **Modul za konverziju konstanti** — u I prolazu za obradu literala, u II prolazu za obradu `:DATA` i literala

**Odnos među modulima:**

```
                    ASEMBLER
                   /        \
                  /          \
            PRVI              DRUGI
           PROLAZ             PROLAZ
              \                 /
               \               /
                IZRAČUNAVANJE IZRAZA
                       |
                KONVERZIJA KONSTANTI
```

> Oba prolaza koriste modul za izračunavanje izraza i modul za konverziju konstanti.

---

# 5. Analiza efikasnosti algoritama

### 5.1 🔴 _(zaokruživanje)_

**Ako je u vezi sa vremenom izvršavanja nekog algoritma napisano $T(n) = \Theta(n^2)$, to znači:**

- ❌ a) da je funkcija $T(n)$ jednaka funkciji $\Theta(n^2)$
- ❌ b) da je funkcija $T(n)$ asimptotski jednaka funkciji $\Theta(n^2)$
- ✅ **c) da funkcija $T(n)$ pripada skupu funkcija $\Theta(n^2)$**
- ❌ d) da funkcija $\Theta(n^2)$ pripada skupu funkcija $T(n)$

### 5.2 🔴 _(zaokruživanje)_ — _varijanta prethodnog_

**Ako je u vezi sa vremenom izvršavanja nekog algoritma napisano $T(n) = \Theta(n^2)$, to znači:**

- ❌ a) da je funkcija $T(n)$ jednaka funkciji $\Theta(n^2)$
- ✅ **b) da funkcija $T(n)$ pripada skupu funkcija $\Theta(n^2)$**
- ❌ c) da funkcija $\Theta(n^2)$ pripada skupu funkcija $T(n)$
- ❌ d) da je vreme izvršavanja jednako $n^2$ sekundi

> $\Theta(n^2)$ je **skup funkcija**, a znak `=` u zapisu $T(n) = \Theta(n^2)$ zapravo znači **pripadnost** tom skupu. Nije ni jednakost funkcija, ni tvrdnja o konkretnom broju sekundi.

### 5.3 🔴 _(zadatak)_

**Napisati telo funkcije `foo` tako da njeno vreme izvršavanja ima asimptotski usku granicu $\Theta(n)$. Sami odlučite šta će tačno funkcija da radi.**

```cpp
void foo(int n) {
    for (int i = 0; i < n; i++)
        cout << "foo" << endl;
}
```

> Petlja se izvršava tačno `n` puta, a telo petlje je $\Theta(1)$, pa je vreme izvršavanja $\Theta(n)$.

### 5.4 🔴 _(dopunjavanje)_

**Kolika je asimptotski uska granica rada za funkciju `foo` iz prethodnog zadatka?**

> $T_1 = \Theta(n)$

### 5.5 _(dopunjavanje)_

**Primenom Master teoreme odrediti asimptotsko ograničenje za $T(n) = 7T(n/8) + n\lg n$.**

$a = 7$, $b = 8$, $f(n) = n\lg n$

$$\log_b a = \log_8 7 = 0{,}9358 \quad\Rightarrow\quad n^{\log_b a} = n^{0,9358}$$

Kraće: iz $7 = 8^x$ sledi $x \in (0, 1)$, pa je $n^x < n \le n\lg n$, dakle $f(n) = \Omega(n^x)$ — $f(n)$ je **polinomijalno veća** → **slučaj 3**.

Poređenje brojevima: $\dfrac{n\lg n}{n^{0,9358}} = n^{0,0642}\lg n \to \infty$.

Uslov regularnosti: $a\,f(n/b) = 7\cdot\tfrac{n}{8}\lg\tfrac{n}{8} = \tfrac{7}{8}n(\lg n - 3) \le \tfrac{7}{8}\,n\lg n$, sa $c = 7/8 < 1$. Ispunjen.

> $$T(n) = \Theta(f(n)) = \Theta(n \lg n)$$

**Zamka:** nije dovoljno izračunati $c = \log_b a$ i napisati $\Theta(n^c)$. U sva tri slučaja $f(n)$ se **poredi** sa $n^{\log_b a}$, i **veća od te dve funkcije određuje rešenje**. Ovde je veća $f(n)$.

### 5.6 _(zadatak)_

**Napisati telo funkcije `foo` i `bar` tako da funkcija `foo` ima asimptotski usku granicu $\Theta(n^{2,5})$, a funkcija `bar` asimptotski usku granicu $\Theta(\lg n)$.**

```c
void foo(int n) {
    int x = 0;
    int y = 2;
    for (int i = 0; i < n; i++)                 // n
        for (int j = 0; j < n; j++)             // n
            for (int k = 0; k < sqrt(n); k++)   // sqrt(n)
                x += y;
}
```

> $n \cdot n \cdot \sqrt{n} = n^{2,5}$

```c
void bar(int n) {
    int x = 1;
    int y = 2;
    for (int i = 1; i < n; i *= 2)
        x += y;
}
```

> `i` uzima vrednosti $1, 2, 4, 8, \dots$, pa se petlja izvrši $\lfloor\lg n\rfloor + 1$ puta $= \Theta(\lg n)$.
>
> **Pazi:** korak mora biti `i *= 2`. Na roku piše `i*2`, što ne menja `i` — petlja bi bila beskonačna.

### 5.7 🔴 _(zadatak)_

**Napisati telo funkcije `foo` tako da njeno vreme izvršavanja na procesoru sa jednim jezgrom ima asimptotski usku granicu $\Theta(n^3)$. Sami odlučite šta će tačno funkcija da radi.**

```cpp
void foo(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                cout << "nesto" << endl;
            }
        }
    }
}
```

> Tri ugnježdene petlje po `n` iteracija, telo $\Theta(1)$ → $n \cdot n \cdot n = \Theta(n^3)$.
>
> Traži se **telo funkcije**, pa petlje moraju biti napisane u celosti kao C++ kod — skraćeni zapis tipa `for n` se ne priznaje.

### 5.8 🔴 _(dopunjavanje)_

**Koliki je rad funkcije `foo` iz prethodnog pitanja? Kratko obrazložiti.**

> $T_1 = \Theta(n^3)$
>
> Rad je vreme izvršavanja na jednom procesoru, a ono za `foo` ima asimptotski usku granicu $\Theta(n^3)$.

### 5.9 🔴 _(dopunjavanje)_

**Ako vreme izvršavanja neke funkcije na procesoru sa jednim jezgrom ima asimptotski usku granicu $\Theta(n^2)$, koliki je rad te funkcije?**

> $T_1 = \Theta(n^2)$
>
> Rad je po definiciji vreme izvršavanja na jednom procesoru, pa je jednak datoj granici.

### 5.10 🔴 _(zadatak)_

**Napisati telo funkcije `foo` tako da njeno vreme izvršavanja na procesoru sa jednim jezgrom ima asimptotski usku granicu $\Theta(n^2)$.**

```cpp
void foo(int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cout << "nesto" << endl;
}
```

> Dve ugnježdene petlje po `n` iteracija, telo $\Theta(1)$ → $\Theta(n^2)$.

### 5.11 _(dopunjavanje)_

**Primenom Master teoreme odrediti asimptotsko ograničenje za $T(n) = 4T(n/5) + n\lg n$.**

$a = 4$, $b = 5$, $f(n) = n\lg n$

$$\log_b a = \log_5 4 = 0{,}861 \quad\Rightarrow\quad n^{\log_b a} = n^{0,861}$$

Iz $4 = 5^x$ sledi $x \in (0,1)$, pa je $n^x < n \le n\lg n$ — $f(n)$ je **polinomijalno veća** → **slučaj 3**.

Uslov regularnosti: $4\cdot\tfrac{n}{5}\lg\tfrac{n}{5} = \tfrac{4}{5}n(\lg n - \lg 5) \le \tfrac{4}{5}n\lg n$, sa $c = 4/5 < 1$. Ispunjen.

> $$T(n) = \Theta(f(n)) = \Theta(n \lg n)$$

### 5.12 _(dopunjavanje)_

**Primenom Master teoreme odrediti asimptotsko ograničenje za $T(n) = 24{,}7\,T(n/3) + n^2$.**

$a = 24{,}7$, $b = 3$, $f(n) = n^2$

$$\log_b a = \log_3 24{,}7 = 2{,}919 \quad\Rightarrow\quad n^{\log_b a} = n^{2,919}$$

Provera: $3^3 = 27 > 24{,}7$, pa je $\log_3 24{,}7$ nešto malo manje od 3.

Ovde je $f(n) = n^2$ **polinomijalno manja** od $n^{2,919}$, tj. $n^2 = O(n^{2,919-\varepsilon})$ za npr. $\varepsilon = 0{,}5$ → **slučaj 1**.

> $$T(n) = \Theta\!\left(n^{\log_3 24,7}\right) \approx \Theta(n^{2,919})$$

**Uporedi sa 5.5 i 5.11:** tamo je veća bila $f(n)$ (slučaj 3), ovde je veća $n^{\log_b a}$ (slučaj 1). Uvek se te dve funkcije porede, a veća određuje rešenje.

### 5.13 _(dopunjavanje)_

**Koje osobine mora da ima invarijanta petlje da bi algoritam bio korektan?**

Invarijanta petlje se koristi za dokaz da je algoritam korektan. Potrebno je pokazati **tri osobine**:

1. **Inicijalizacija** — istinita je pre prve iteracije petlje.
2. **Održavanje** — ako je istinita pre iteracije petlje, ostaje istinita posle iteracije.
3. **Završetak** — kada se petlja završi, invarijanta daje korisnu osobinu za dokazivanje korektnosti.

> Velika sličnost sa matematičkom indukcijom — s tim što se ovde postupak zaustavlja kada se petlja završi.

### 5.14 _(dopunjavanje)_

**Primenom Master teoreme odrediti asimptotsko ograničenje za $T(n) = 3T(n/4) + n\lg n$.**

$a = 3$, $b = 4$, $f(n) = n\lg n$

$$\log_b a = \log_4 3 = 0{,}792 \quad\Rightarrow\quad n^{\log_b a} = n^{0,792}$$

Iz $3 = 4^x$ sledi $x \in (0,1)$, pa je $n^x < n \le n\lg n$ — $f(n)$ je **polinomijalno veća** → **slučaj 3**.

Uslov regularnosti: $3\cdot\tfrac{n}{4}\lg\tfrac{n}{4} = \tfrac{3}{4}n(\lg n - 2) \le \tfrac{3}{4}n\lg n$, sa $c = 3/4 < 1$. Ispunjen.

> $$T(n) = \Theta(n \lg n)$$

**Obrazac:** kad je $a < b$, tada je $\log_b a < 1$, pa je $n^{\log_b a} < n \le f(n)$ za svako $f(n) = n\lg n$ — uvek slučaj 3, uvek $\Theta(n\lg n)$. Tako je i u 5.5 ($7 < 8$) i u 5.11 ($4 < 5$).

### 5.15 _(dopunjavanje)_ — _slučaj 2_

**Primenom Master teoreme odrediti asimptotsko ograničenje za $T(n) = T(2n/3) + 1$.**

$a = 1$, $b = 3/2$, $f(n) = 1 = n^0$

$$\log_b a = \log_{3/2} 1 = 0 \quad\Rightarrow\quad n^{\log_b a} = n^0 = 1$$

Kako je $f(n) = \Theta(n^0) = \Theta(1)$, to jest $f(n)$ i $n^{\log_b a}$ su **iste veličine** → **slučaj 2**.

> $$T(n) = \Theta\!\left(n^{\log_b a}\lg n\right) = \Theta(\lg n)$$

**Sva tri slučaja na jednom mestu:**

| Zadatak                | $n^{\log_b a}$ vs $f(n)$ | Slučaj | Rešenje             |
| ---------------------- | ------------------------ | ------ | ------------------- |
| $7T(n/8) + n\lg n$     | $f(n)$ veća              | 3      | $\Theta(n\lg n)$    |
| $T(2n/3) + 1$          | jednake                  | 2      | $\Theta(\lg n)$     |
| $24{,}7\,T(n/3) + n^2$ | $n^{\log_b a}$ veća      | 1      | $\Theta(n^{2,919})$ |

---

# 6. Rad i raspon

**Podsetnik:** $T_1$ = rad, $T_\infty$ = raspon, $T_P$ = vreme na P procesora.

- **Zakon rada:** $T_P \geq T_1 / P$
- **Zakon raspona:** $T_P \geq T_\infty$
- **Donja granica** (oba zakona zajedno): $T_P \geq \max(T_1/P,\ T_\infty)$
- **Gornja granica** (teorema o pohlepnom raspoređivaču): $T_P \leq T_1/P + T_\infty$

### 6.1 🔴 _(zaokruživanje)_

**Na osnovu zakona rada i raspona možemo biti sigurni da je:**

- ❌ a) vreme izvršavanja na P procesora uvek manje ili jednako srednjoj vrednosti rada i raspona
- ❌ b) vreme izvršavanja na P procesora uvek strogo manje od srednje vrednosti rada i raspona
- ✅ **c) vreme izvršavanja na P procesora uvek veće ili jednako rasponu**
- ❌ d) vreme izvršavanja na P procesora uvek veće ili jednako radu

### 6.2 _(dopunjavanje)_

**Originalna verzija paralelnog algoritma sa radom od 2048s i rasponom od 1s je izmenjena tako da je rad sveden na 1024s, a raspon povećan na 8s. Kako su se nakon te izmene promenile gornje i donje granice vremena izvršavanja na 32 i 512 jezgara?**

Originalno: $T_1 = 2048$, $T_\infty = 1$. Izmenjeno: $T_1' = 1024$, $T_\infty' = 8$.

|          | $P$ | donja $\max(T_1/P,\ T_\infty)$ | gornja $T_1/P + T_\infty$ |
| -------- | --- | ------------------------------ | ------------------------- |
| original | 32  | $\max(64, 1) = 64$             | $64 + 1 = 65$             |
| izmenjen | 32  | $\max(32, 8) = 32$             | $32 + 8 = 40$             |
| original | 512 | $\max(4, 1) = 4$               | $4 + 1 = 5$               |
| izmenjen | 512 | $\max(2, 8) = 8$               | $2 + 8 = 10$              |

> **Na 32 jezgra** obe granice su se smanjile ($64 \to 32$ i $65 \to 40$) — izmena je **poboljšanje**.
>
> **Na 512 jezgara** obe granice su se povećale ($4 \to 8$ i $5 \to 10$) — izmena je **pogoršanje**.
>
> Razlog: na malom broju jezgara dominira rad, pa se isplati njegovo smanjenje. Na velikom broju jezgara dominira raspon, pa ga povećanje sa 1s na 8s odmah pokvari.

**Pazi na donju granicu.** Zakon rada daje $T_P \ge T_1/P$, a zakon raspona $T_P \ge T_\infty$ — važe **oba**, pa je prava donja granica njihov maksimum. Za izmenjenu verziju na 512 jezgara, $T_1/P = 2$ ali je $T_\infty = 8$, pa je donja granica **8**, a ne 2.

### 6.3 _(dopunjavanje)_

**Da li postoji mogućnost za savršeno linearno ubrzanje paralelnog algoritma koji se izvršava na idealnom paralelnom računaru sa 4 procesora, ako je ukupan rad 33, a raspon 9? Obrazložiti odgovor.**

> **Ne postoji.**

Savršeno linearno ubrzanje znači $T_1/T_P = P$, odnosno

$$T_P = \frac{T_1}{P} = \frac{33}{4} = 8{,}25$$

Ali **zakon raspona** kaže $T_P \ge T_\infty = 9$. Kako je $8{,}25 < 9$, takvo vreme je nemoguće.

Ekvivalentno, preko paralelizma: $T_1/T_\infty = 33/9 = 3{,}67 < 4 = P$. Paralelizam je gornja granica ubrzanja, pa se sa 4 procesora ne može dostići ubrzanje 4.

### 6.4 _(dopunjavanje)_

**Kako se računa raspon datog grafa $T_\infty(A \cup B)$ ako su dva podgrafa povezana na sledeća dva načina?**

**a) Redno** (`A → B`):

$$T_\infty(A \cup B) = T_\infty(A) + T_\infty(B)$$

**b) Paralelno** (grananje na `A` i `B`, pa spajanje):

$$T_\infty(A \cup B) = \max\bigl(T_\infty(A),\ T_\infty(B)\bigr)$$

> Analiza raspona je analiza **kritičnog puta**. Kod redne veze putevi se nadovezuju, pa se rasponi sabiraju; kod paralelne veze kritični put ide kroz duži od dva podgrafa, pa se uzima maksimum.
>
> Analiza rada je, za razliku od toga, analiza **serijalizacije**.

### 6.5 _(dopunjavanje)_

**Koliki su rad, raspon i paralelizam procedure `Arithmetic-Sum(n)`?**

```
Arithmetic-Sum(n)
    x = 0
    parallel_for i = 1 to n
        x = x + 1
    print x
```

**Rad** — serijalizacija (`parallel_for` postaje obična `for`) daje petlju sa `n` iteracija:

$$T_1(n) = \Theta(n)$$

**Raspon** — paralelna petlja se realizuje kao rekurzija podeli-pa-vladaj, pa joj je dubina logaritamska. Za petlju sa `n` iteracija u kojoj `i`-ta iteracija ima raspon $iter_\infty(i)$:

$$T_\infty(n) = \Theta(\lg n) + \max_{1 \le i \le n} iter_\infty(i)$$

Telo (`x = x + 1`) je $\Theta(1)$, pa je $T_\infty(n) = \Theta(\lg n)$.

**Paralelizam:**

$$\frac{T_1(n)}{T_\infty(n)} = \Theta\!\left(\frac{n}{\lg n}\right)$$

> **Napomena:** ova procedura ima **trku do podataka** — sve iteracije upisuju u istu lokaciju `x`, a `x = x + 1` nije jedna instrukcija nego niz (učitaj, uvećaj, upiši). Rad, raspon i paralelizam se ipak računaju iz strukture grafa računanja.

### 6.6 _(dopunjavanje)_

**Napisati teoremu o gornjoj granici vremena izvršavanja algoritma na P procesora. Objasniti korišćene oznake.**

Na `P` procesora, **pohlepni raspoređivač** izvršava paralelni algoritam sa radom $T_1$ i rasponom $T_\infty$ u vremenu

$$T_P \le \frac{T_1}{P} + T_\infty$$

- $T_P$ — vreme izvršavanja na `P` procesora
- $T_1$ — **rad**, vreme izvršavanja na jednom procesoru
- $T_\infty$ — **raspon**, vreme za neograničen broj procesora (kritični put)
- $P$ — broj procesora

**Dve posledice:**

1. $T_P$ nikada nije više od 2 puta veće od optimalnog vremena: $T_P \le 2\,T_P^*$
2. Ako je $P \ll T_1/T_\infty$ (paralelizam algoritma), onda je $T_P \approx T_1/P$, tj. ubrzanje je približno jednako `P`

### 6.7 _(dopunjavanje)_

**Odrediti rad, raspon i paralelizam za proceduru `Foo(A, B)`.**

```
Foo(A, B)
  n = A.rows
  neka je C nova matrica nxn
  parallel_for i = 1 to n
      for j = 1 to n
          C_ij = 0
  parallel_for i = 1 to n
      parallel_for j = 1 to n
          for k = 1 to n
              C_ij = C_ij + A_ik * B_kj
  return C
```

**Rad** — serijalizacija (sve `parallel_for` postaju obične `for`): dominira trostruka ugnježdena petlja.

$$T_1(n) = \Theta(n^3)$$

**Raspon** — obe petlje daju $\Theta(n)$, jer paralelne petlje doprinose samo $\Theta(\lg n)$, a **unutrašnji serijski `for`** doprinosi $\Theta(n)$:

$$T_\infty(n) = \Theta(n)$$

**Paralelizam:**

$$\frac{T_1(n)}{T_\infty(n)} = \frac{\Theta(n^3)}{\Theta(n)} = \Theta(n^2)$$

> **Ključ:** unutrašnja `for` petlja po `k` **nije** paralelizovana (prosta zamena sa `parallel_for` dovela bi do trke do podataka), pa ona i određuje raspon.

---

# 7. Osnovni blokovi

**Podsetnik:** osnovni blok je niz susednih iskaza koji ne sadrži labelu (osim možda na početku) ni skok (osim možda na kraju). **Svaka labela počinje blok, svaki skok završava blok.** Obrnuto ne važi — blok ne mora počinjati labelom, dovoljno je da mu je prethodni iskaz skok.

### 7.1 🔴 _(zadatak)_

**Priloženi kod podeliti horizontalnim linijama na osnovne blokove.**

```mips
main:
    la $t0, var1
--------------------------------
lab1:
    lw $t1, 0($t0)
    li $t0, 5
    blez $t2, lab1
--------------------------------
    li $t2, -5
    blez $t1, lab1
--------------------------------
lab2:
    nop
```

### 7.2 _(zaokruživanje)_

**Sve instrukcije osnovnog bloka osim prve i poslednje predstavljaju njegovu unutrašnjost. Zaokruži slovo ispred instrukcija koje mogu biti u unutrašnjosti osnovnog bloka.**

- ✅ **a) Pristup memoriji**
- ✅ **b) Poziv potprograma**
- ❌ c) Uslovni skok
- ❌ d) Bezuslovni skok
- ✅ **e) MOVE instrukcija**

> Blok završava **samo uslovni ili bezuslovni skok** — sve ostale instrukcije su beznačajne za tok upravljanja i grupišu se u blokove.
>
> Poziv potprograma nije skok u tom smislu: upravljanje se vraća na sledeću instrukciju, pa niz ne puca. Zato i kanonički oblik traži da predak `CALL` čvora bude `EXP` ili `MOVE`, tj. da `CALL` stoji unutar iskaza.

### 7.3 🔴 _(zaokruživanje)_ — _varijanta prethodnog_

**Koje od ovih instrukcija međureprezentacije mogu biti u unutrašnjosti osnovnog bloka?**

- ✅ **a) Pristup memoriji**
- ❌ b) Labela
- ❌ c) Uslovni skok
- ❌ d) Bezuslovni skok

> Blok ne sadrži labelu (osim možda na samom **početku**) ni skok (osim možda na samom **kraju**). Unutrašnjost je sve osim prve i poslednje instrukcije, pa u njoj ne sme biti ni labele ni skoka.
>
> Uporedi sa 7.2: tamo su ponuđeni `poziv potprograma` i `MOVE`, koji **jesu** dozvoljeni. Ovde je umesto njih ponuđena `labela`, koja **nije**.

### 7.4 🔴 _(zadatak)_

**Za dati kod nacrtati graf toka upravljanja i na njemu obeležiti osnovne blokove. Pored svakog osnovnog bloka napisati koje promenljive se u njemu definišu, a koje koriste (`use` i `def` skupovi).**

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

| Blok | Instrukcije             | `def` | `use` |
| ---- | ----------------------- | ----- | ----- |
| B1   | `a = 5`, `x > 5`        | a     | x     |
| B2   | `z = y - a`             | z     | y, a  |
| B3   | `z = x`                 | z     | x     |
| B4   | `b = 7`, `return z - b` | b     | z, b  |

> `def` su promenljive kojima blok **zadaje vrednost**, `use` one koje **očitava**. Skupovi nisu disjunktni: u B4 se `b` i definiše (`b = 7`) i koristi (`return z - b`), pa se javlja u oba.
>
> Granice blokova: B1 se završava uslovnim skokom (`x > 5`), a B4 počinje jer je tačka spajanja obe grane.

### 7.5 🔴 _(zadatak)_ — _varijanta prethodnog_

**Podeliti kod na osnovne blokove i napisati `def` i `use` skupove.**

```c
int foo(int x, int y){
    int z,a,b = 5;
    if(x > 5)
        z = y-a;
    else
        z=x;
    b=7;
    return b-a;
}
```

> **Pazi:** u `int z,a,b = 5;` inicijalizuje se **samo `b`**. Promenljive `z` i `a` ostaju nedefinisane.

| Blok | Instrukcije             | `def` | `use` |
| ---- | ----------------------- | ----- | ----- |
| B1   | `b = 5`, `x > 5`        | b     | x     |
| B2   | `z = y - a`             | z     | y, a  |
| B3   | `z = x`                 | z     | x     |
| B4   | `b = 7`, `return b - a` | b     | b, a  |

Struktura grafa je ista kao u 7.4 (B1 se grana na B2/B3, oba vode u B4).

**Dve zamke ovog koda:**

- `a` se **koristi a nikad ne definiše** — živa je od ulaza u funkciju do `return`.
- `z` se **definiše a nikad ne koristi** (`return b - a` ne čita `z`) — nikad nije živa.

Graf smetnji (brojevi u zagradi su boje/registri):

```
        x(1) --------- y(2)
          \           /
            \       /
              \   /
               a(3)
                |
               b(1)

        z(1)   (izolovan — nikad živa)
```

Trougao `{x, y, a}` — sve tri su žive istovremeno na `if (x > 5)`. Grana `a–b` jer su obe žive na `return b - a`. Graf je **3-obojiv**.

---

# 8. Formalne gramatike

**Podsetnik:** produkcija (smena) je pravilo oblika `a -> b`. Svako pravilo je zasebna produkcija — dva pravila sa istim levim nezavršnim simbolom broje se kao **dve** produkcije, ne kao jedna.

### 8.1 🔴 _(zadatak)_

**Data je sledeća gramatika. Koliko u njoj ima produkcija? Zaokružiti ih.**

```
S -> x = P            (1)
P -> 2 - F            (2)
F -> x                (3)
S -> F = 2 - P / t    (4)
P -> F / t            (5)
F -> 2 - P            (6)
```

> **Odgovor: 6 produkcija** — zaokružuju se sve šest.

Nezavršni simboli `S`, `P` i `F` javljaju se po dva puta sa leve strane, ali to su i dalje šest odvojenih produkcija.

### 8.2 _(zadatak)_

**Data je gramatika jezika J. Ispod svake rečenice napisati da li je ta rečenica deo jezika J, i ako jeste, redosled primene produkcija koji generiše tu rečenicu. Početni simbol je S.**

```
1. S -> x = P
2. S -> F = 2 - P / t
3. P -> 2 - F
4. P -> F / t
5. F -> x
6. F -> 2 - P
```

**`2 - x / t = 2 - t / t`**

> **Nije deo jezika J.** Rečenica počinje sa `2`, pa se mora primeniti produkcija 2, čija desna strana ima oblik `2 - P / t`. Da bi se dobilo `2 - t / t`, `P` bi morao izvesti samo `t` — a to nije moguće (`P -> 2 - F` ili `P -> F / t`).

**`x = 2 - x`**

> **Jeste deo jezika J.** Redosled: **1 → 3 → 5**
>
> `S` →₁ `x = P` →₃ `x = 2 - F` →₅ `x = 2 - x`

**`2 - 2 - x = 2 - 2 - x / t`**

> **Jeste deo jezika J.** Redosled: **2 → 6 → 3 → 5 → 3 → 5**
>
> `S` →₂ `F = 2 - P / t` →₆ `2 - P = 2 - P / t` →₃ `2 - 2 - F = 2 - P / t` →₅ `2 - 2 - x = 2 - P / t` →₃ `2 - 2 - x = 2 - 2 - F / t` →₅ `2 - 2 - x = 2 - 2 - x / t`

**Dopunsko pitanje: da li je data gramatika kontekstno slobodna?**

> **Jeste.**

**Hijerarhija Čomskog:**

| Tip | Naziv | Oblik produkcije |
|---|---|---|
| 0 | Neograničene (rekurzivno nabrojive) | nema ograničenja za `a -> b` |
| 1 | Kontekstno osetljive (zavisne) | `aAb -> aγb`, gde `A ∈ N`, `γ ∈ (N∪T)*` i nije prazno |
| **2** | **Kontekstno slobodne (nezavisne)** | **`A -> γ`, gde `A ∈ N`, `γ ∈ (N∪T)*`** |
| 3 | Regularne | `A -> γ` gde `γ ∈ T`, ili `A -> γB` (odnosno `A -> Bγ`) |

Ovde svih šest produkcija ima **tačno jedan neterminal sa leve strane** (`S`, `P` ili `F`), pa je uslov tipa 2 ispunjen.

### 8.3 _(zadatak)_

**Zadatu gramatiku transformisati u gramatiku bez konflikta.**

```
E -> E + T          T -> id
E -> E - T          T -> num
E -> T              T -> ( E )
```

Gramatika je **levo rekurzivna** (`E -> E + T`), a leva rekurzija je specijalan slučaj preklapanja `FIRST` skupova dve produkcije. Uklanja se prevođenjem u desnu rekurziju.

**Opšte pravilo:**

| Polazne produkcije | Rezultat transformacije |
| ------------------ | ----------------------- |
| `X -> X α₁`        | `X -> β₁ X'`            |
| `X -> X α₂`        | `X -> β₂ X'`            |
| `X -> β₁`          | `X' -> α₁ X'`           |
| `X -> β₂`          | `X' -> α₂ X'`           |
|                    | `X' -> ε`               |

**Rešenje:**

```
E  -> T E'          T -> id
E' -> + T E'        T -> num
E' -> - T E'        T -> ( E )
E' -> ε
```

> **Pazi:** produkcije za `E'` moraju imati **repno `E'`**. Sa `E' -> + T` (bez `E'`) izraz bi mogao imati najviše jedan operator, pa se `id + num - id` ne bi mogao izvesti.

### 8.4 🔴 _(zadatak)_ — _ista gramatika kao 8.1_

**Koliko u njoj ima neterminalnih simbola? Zaokružiti ih.**

```
S -> x = P            P -> 2 - F            F -> x
S -> F = 2 - P / t    P -> F / t            F -> 2 - P
```

> **Odgovor: 3 neterminalna simbola** — `S`, `P`, `F`.

Broje se **različiti simboli**, a ne njihova pojavljivanja.

### 8.5 🔴 _(zadatak)_ — _ista gramatika kao 8.1_

**Koliko u njoj ima terminalnih simbola? Zaokružiti ih.**

> **Odgovor: 6 terminalnih simbola** — `x`, `=`, `2`, `-`, `/`, `t`

**Ista gramatika, tri različita pitanja.** Ne pomešaj ih:

| Pitanje                               | Odgovor                          |
| ------------------------------------- | -------------------------------- |
| Koliko ima **produkcija**?            | 6 (`S`, `P`, `F` po dve)         |
| Koliko ima **neterminalnih** simbola? | 3 — `S`, `P`, `F`                |
| Koliko ima **terminalnih** simbola?   | 6 — `x`, `=`, `2`, `-`, `/`, `t` |

### 8.6 🔴 _(zadatak)_

**Data je sledeća gramatika. Zaokruži produkcije u toj gramatici. Navedi terminalne i neterminalne simbole.**

```
S -> get E from S      L -> quit
S -> begin S L         L -> ; S L
S -> print E END       E -> num EQ num
```

> **Produkcija ima 6** — zaokružuje se svih šest redova.
>
> **Neterminalni simboli (3):** `S`, `L`, `E`
>
> **Terminalni simboli (9):** `get`, `from`, `begin`, `print`, `END`, `quit`, `;`, `num`, `EQ`

Neterminali su oni koji se pojavljuju sa **leve strane** neke produkcije. Sve ostalo su terminali.

### 8.7 🔴 _(zaokruživanje)_

**Date su četiri grupe skupova (terminalni, neterminalni i početni simbol). Zaokružiti one koje mogu predstavljati formalnu gramatiku, a precrtati one koje ne mogu.**

**Podsetnik:** formalna gramatika je četvorka `G(N, T, Σ, P)` gde je `Σ ∈ N`, a skupovi `N` i `T` moraju biti **disjunktni**.

|     | Terminalni          | Neterminalni | Početni |     |
| --- | ------------------- | ------------ | ------- | --- |
| 1   | a, b, c, +, /, d, z | x, y, a, b   | y       | ❌  |
| 2   | a, b, c, +, -, d    | x, y, z      | z       | ✅  |
| 3   | a, b, c, +, -, d    | x, y, z      | a       | ❌  |
| 4   | a, b, c, \*, +      | \*, /        | a       | ❌  |

- **1)** `N ∩ T = {a, b} ≠ ∅` — skupovi nisu disjunktni.
- **2)** Disjunktni su, a `z ∈ N`. **Jedina ispravna.**
- **3)** Disjunktni jesu, ali `a ∉ N` — početni simbol mora biti neterminal.
- **4)** `N ∩ T = {*} ≠ ∅`, a uz to je i `a ∉ N`.

### 8.8 _(zadatak)_ — _levo faktorisanje, ne leva rekurzija_

**Transformisati datu gramatiku tako da ne dođe do konflikta.**

```
E -> T - E        T -> id
E -> T + E        T -> num
E -> T            T -> ( E )
```

Ova gramatika **nije levo rekurzivna**. Problem je što sve tri produkcije za `E` počinju istim simbolom `T`, pa im se **`FIRST` skupovi preklapaju**. Rešenje je **izdvajanje leve zajedničke osnove** (levo faktorisanje).

Opšte pravilo: `A -> α β₁ | α β₂ | α` postaje `A -> α A'`, `A' -> β₁ | β₂ | ε`.

Ovde je `α = T`, `β₁ = - E`, `β₂ = + E`:

```
E  -> T E'        T -> id
E' -> - E         T -> num
E' -> + E         T -> ( E )
E' -> ε
```

> **Uporedi sa 8.3.** Tamo je gramatika bila `E -> E + T` — **levo rekurzivna**, pa se prevodila u desnu rekurziju i produkcije za `E'` imale su **repno `E'`**. Ovde je gramatika već desno rekurzivna, pa se samo izdvaja zajednička osnova i **nema repnog `E'`**.

### 8.9 _(zadatak)_

**Zaokružiti terminalne simbole i prebrojati ih.**

```
S -> x = P            P -> z += x           E -> x * E
S -> x + P            P -> x + y = E        E -> y
S -> x * P / t
```

Neterminali (leve strane produkcija): `S`, `P`, `E`.

> **Terminalni simboli:** `x`, `=`, `+`, `*`, `/`, `t`, `z`, `+=`, `y`
>
> **Broj: 9**

> ⚠️ Ako se `+=` ne tretira kao **jedan** terminal nego kao `+` pa `=`, broj bi bio **8**. Pošto je u gramatici napisan spojeno, računa se kao jedan token.

---

# 9. Dodela resursa — bojenje grafa

**Podsetnik:** rang (stepen) čvora je broj njegovih suseda. Čvor je _značajan_ ako mu je rang ≥ K (broj raspoloživih boja/registara).

- **UPROSTI** — čvor koji nije značajan (rang < K) izvlači se iz grafa i gura na stek; on nije kandidat za prelivanje.
- **PRELIJ** — primenjuje se kad su _svi_ preostali čvorovi značajni. Tada se prelivanje mora uraditi.

Dakle: prelivanje je nužno tačno onda kad se UPROSTI zaglavi. Potpun graf **K₄** traži 4 boje, pa sa 3 registra uvek zahteva prelivanje.

### 9.1 🔴 _(dopunjavanje)_

**Ako graf ima 4 čvora i svaki čvor ima rang 3:**

**a) Koliko taj graf ima ivica?**

Zbir rangova svih čvorova jednak je dvostrukom broju ivica:

$$4 \cdot 3 = 12 = 2E \quad\Rightarrow\quad E = 6$$

> **6 ivica**

**b) Koji je najmanji broj boja sa kojim može biti obojen?**

Svaki čvor je susedan sa preostala 3 — to je **potpun graf K₄**. U potpunom grafu su svaka dva čvora susedna, pa nikoja dva ne mogu deliti boju.

> **4 boje**

**Definicije koje ovo pitanje testira.** *Rang (stepen) čvora* je broj njegovih suseda. *Rang grafa* je rang čvora sa najvećim rangom. *Klika* je deo čvorova grafa koji su svi međusobno povezani. Graf je *potpun* ako svi njegovi čvorovi obrazuju kliku.

**Opšte pravilo.** Graf sa `n` čvorova gde svaki ima rang `n-1` (ekvivalentno: svi čvorovi obrazuju kliku) je potpun graf `Kₙ`: ima $\binom{n}{2} = \frac{n(n-1)}{2}$ ivica, rang mu je `n-1`, i zahteva `n` boja.

Broj ivica sledi iz **zbir rangova = dvostruki broj ivica**: $n(n-1) = 2E$.

**Profesor rotira formulaciju.** Sve tri varijante su isti zadatak:

| Formulacija sa roka | Graf | Ivica | Rang | Boja | Potpun |
|---|---|---|---|---|---|
| 4 čvora, svaki rang 3 | `K₄` | 6 | 3 | 4 | da |
| 5 čvorova, svaki rang 4 | `K₅` | 10 | 4 | 5 | da |
| 6 ivica i 4 čvora | `K₄` | 6 | 3 | 4 | da |
| 6 čvorova koji obrazuju kliku | `K₆` | 15 | 5 | 6 | da |

Kod treće varijante se rang dobija unazad: $\sum \text{rang} = 2E = 12$, a na 4 čvora nijedan ne može imati rang veći od 3, pa svi imaju tačno 3.

Hromatski broj je **veći ili jednak broju čvorova u najvećoj kliki**, a **manji ili jednak broju čvorova** — kod `Kₙ` obe granice daju `n`.

### 9.2 🔴 _(zaokruživanje)_

**Dat je graf smetnji. Zaokružiti tačne, a precrtati netačne odgovore.**

Brojevi u zagradi su **boje** (registri):

```
   A(1) --------- B(2)
     \           /
      \         /
       \       /
        C(3) ------- D(1)
```

Grane: `A–B`, `A–C`, `B–C`, `C–D`. Rangovi: `C` = 3, `A` = 2, `B` = 2, `D` = 1.

- ❌ a) Za bojenje grafa je potrebno minimalno 4 boje — dovoljne su 3.
- ❌ b) Čvorovima `B` i `C` se može dodeliti isti registar — susedni su, dakle u smetnji.
- ✅ **c) Graf se može obojiti sa 3 boje**
- ❌ d) Čvorovima `B` i `D` se **mora** dodeliti isti registar — nisu susedni, pa im se **može**, ali ne mora.

> Najveća klika je trougao `{A, B, C}`, pa treba bar 3 boje. `D` je susedan samo sa `C` i preuzima boju od `A`.
>
> **Zamka je u rečima „može" i „mora".** Dva nesusedna čvora _mogu_ deliti registar; dva susedna _ne mogu_. Nikada ne postoji obaveza da dva čvora dele registar.

### 9.3 🔴 _(zaokruživanje)_

**Dat je graf smetnji za operande kojima se dodeljuju registri opšte namene. Šta su tačne tvrdnje?**

Brojevi u zagradi su **boje** (registri):

```
        a(1) --------- c(3)
          \           /
           \         /
            \       /
             \     /
              b(2)
                |
                |
              y(1)
                |
                |
              x(2)
```

Grane: `a–b`, `a–c`, `b–c`, `b–y`, `x–y`. Rangovi: `b` = 3, `a` = 2, `c` = 2, `y` = 2, `x` = 1.

_(Na roku su `a–c` i `b–y` nacrtane tako da se seku; presek nije čvor. Ovde je isti graf bez preseka.)_

- ❌ a) Čvor `x` je u smetnji sa čvorom `b`, preko čvora `y` — **smetnja nije tranzitivna**.
- ❌ b) Čvorovima `y` i `a` **ne smemo** dodeliti isti registar — nisu susedni, pa **smemo** (oba imaju boju 1).
- ✅ **c) Čvor `a` je u smetnji sa čvorom `c`** — grana `a–c` postoji.
- ❌ d) Čvorovima `a` i `b` **možemo** dodeliti isti registar — susedni su, dakle u smetnji.

> Najveća klika je trougao `{a, b, c}`, pa su potrebne 3 boje.
>
> **Dve zamke.** Prva: „u smetnji **preko** čvora" — smetnja je isključivo direktna grana, nikad putanja. Druga: razlika između „može" i „ne sme" — susedni čvorovi _ne smeju_ deliti registar, nesusedni _smeju_.

### 9.4 🔴 _(zadatak)_

**Obojiti dati graf sa 3 boje.**

U čvorovima su **slovo i boja**:

```
   A(3)-----------B(2)
     \              | \
       \            |   \
         \          |    C(3)
           \        |    /
             \      |   /
               \    |  /
   E(2)----------- D(1)
```

Grane: `A–B`, `A–D`, `B–C`, `B–D`, `C–D`, `E–D`

Rangovi: `D` = 4, `B` = 3, `A` = 2, `C` = 2, `E` = 1

> **Bojenje:** `D` = 1, `B` = 2, `A` = 3, `C` = 3, `E` = 2

Najveća klika je trougao (`A-B-D` odnosno `B-C-D`), pa su tri boje i **nužne** i **dovoljne**. Grane `A–C` nema, pa nema `K₄`.

**Postupak:** kreni od čvora najvišeg ranga (`D`), pa svakom sledećem čvoru dodeli najmanju slobodnu boju koju ne koriste njegovi susedi.

**Bojenje nije jedinstveno.** Čvor `E` ima rang 1 i jedini sused mu je `D` (boja 1), pa mu se može dodeliti **2 ili 3** — svejedno. Čvor `C` je jedinstven: susedi su mu `B`(2) i `D`(1), pa mora dobiti 3.

### 9.5 🔴 _(zaokruživanje)_

**Procesor ima 3 registra opšte namene. Zaokružiti one grafove smetnji koji će moći biti obojeni (neće doći do prelivanja).**

**a)** ✅ Grane: `A–B`, `A–C`, `B–C`, `B–E`, `C–D`, `C–E`, `D–E`

```
   A(3)--------B(2)
     \         / |
      \       /  |
       \     /   |
        \   /    |
         C(1)    |
        /   \    |
       /     \   |
   D(2)-------E(3)
```

**b)** ✅ Grane: `A–C`, `A–B`, `C–D`, `C–B`, `C–E`

```
             A(2)
              |
   D(2)-----C(1)-----B(3)
              |     /
             E(2)
```

**c)** ✅ Grane: `A–B`, `A–D`, `A–E`, `B–E`, `B–C`, `C–E`, `D–E`

```
   A(2)--------B(3)
    |  \        |  \
    |    \      |   C(2)
    |      \    |   /
   D(3)--------E(1)
```

**d)** ❌ Grane: `A–B`, `B–C`, `D–E`, `E–F`, `A–D`, `B–E`, `C–F`, `A–E`, `B–D`, `B–F`, `C–E`

```
   A---------B---------C
   | \     / | \     / |
   |   \ /   |   \ /   |
   |   / \   |   / \   |
   | /     \ | /     \ |
   D---------E---------F
```

> **Odgovor: zaokružuju se a), b) i c).**

Kod a), b) i c) je najveća klika trougao, pa UPROSTI (uklanjanje čvorova ranga < 3) isprazni graf i tri boje su dovoljne.

Kod **d)** svi čvorovi imaju rang ≥ 3 (`B` i `E` po 5, ostali po 3), pa se UPROSTI **odmah zaglavi**. Čvorovi `{A, B, D, E}` čine **K₄** — treba 4 boje, a imamo 3 registra. **Prelivanje je nužno.**

---

# 10. Povezivač i punjač

**Podsetnik:** relokacija je podešavanje svih adresno osetljivih lokacija na dodeljeni memorijski prostor — punjač dodaje konstantu na svaku relokatibilnu adresu. Za svaku adresno osetljivu lokaciju RLD katalog pamti tri podatka: **naziv simbola, vrstu instrukcije i položaj instrukcije.**

Pravilo: adresno osetljiva je svaka instrukcija koja **referiše simbol (labelu)** — dakle svi skokovi i grananja.

- **Jeste osetljivo:** `blez $t1, L1`, `b foo + 6`, `b main` — svaka instrukcija sa labelom kao operandom.
- **Nije osetljivo:** konstanta (`li $t2, -5`), učitavanje literala (`la $t0, 7` — `7` nije simbol), adresiranje preko registra (`lw $t1, 0($t0)`), aritmetika (`addi`, `mult`).

### 10.1 🔴 _(zaokruživanje)_

**Dati su kodovi dva različita programska segmenta. Zaokružite instrukcije koje predstavljaju adresno osetljive lokacije.**

```mips
main:
    la   $t0, 7          # ❌ 7 je literal, nije simbol
    lw   $t1, 0($t0)     # ❌ adresira preko registra
    blez $t1, L1         # ✅ referiše labelu L1
    li   $t0, 5          # ❌ konstanta
L2:
    b    foo + 6         # ✅ referiše simbol foo
L1:
    li   $t2, -5         # ❌ konstanta
```

```mips
foo:
    addi $t1, $t1        # ❌
    mult $t1, $t1        # ❌
    blez $t1, L          # ✅ referiše labelu
    b    main            # ✅ referiše simbol main
L3:
    li   $t2, ...        # ❌ konstanta
```

> **Odgovor: `blez` i `b` u oba segmenta** — tj. sve instrukcije skoka/grananja.

### 10.2 🔴 _(zaokruživanje)_ — _varijanta prethodnog_

**Zaokružite instrukcije koje predstavljaju adresno osetljive lokacije.**

```mips
main:
    la   $t0, 7          # ❌ 7 je literal, nije simbol
lab1:
    lw   $t1, 0($t0)     # ❌ adresira preko registra
    li   $t0, 5          # ❌ konstanta
    b    lab2 + 1        # ✅ referiše simbol lab2
    li   $t2, -5         # ❌ konstanta
    blez lab1            # ✅ referiše simbol lab1
lab2:
    nop
```

> **Odgovor: `b lab2 + 1` i `blez lab1`**

**Bitno:** obe labele su **lokalne**, u istom segmentu — i svejedno su instrukcije koje ih referišu adresno osetljive. Kriterijum nije „apsolutno vs. PC-relativno adresiranje", nego prosto: **da li instrukcija referiše simbol**.

### 10.3 _(dopunjavanje)_

**Navedi četiri osnovne funkcije punjača.**

1. **Alokacija** — dodela memorijskog prostora programima.
2. **Povezivanje** — određivanje vrednosti simboličkih referenci između relokatibilnih programa.
3. **Relokacija** — podešavanje svih adresno osetljivih lokacija na odgovarajući dodeljeni prostor.
4. **Punjenje** — fizički prenos mašinskih instrukcija i podataka u memoriju.

### 10.4 _(dopunjavanje)_

**Ukratko opiši BSS punjač.**

**BSS punjač** omogućava punjenje **više segmenata programa** nad samo **jednim zajedničkim segmentom podataka**.

Izlaz iz asemblera je prevedeni program i informacija o svim drugim programima na koje se on poziva. Navodi se i informacija o tome koje reference treba menjati — **relokaciona informacija**.

Za povezivanje koristi **vektor prelaza**:

```
foo1:   call addr1
foo2:   call addr2
bar1:   call addr3
...     ...
barN:   call addrX
```

**Nedostaci:**

- Vektor prelaza zauzima prostor u memoriji, a koristi se samo za povezivanje.
- Obrađuje segmente procedura, ali ne olakšava pristup segmentima deljivih podataka.

### 10.5 🔴 _(dopunjavanje)_

**Dat je isečak asemblerskog koda nekog procesora. U tabeli su mašinske instrukcije nastale od tog isečka, napunjene na različite početne lokacije. U „Punjenju 3" nedostaje deo jedne instrukcije. Dopuniti ga.**

```
cmpeqc(R1, 100, R2)
beq(R2, Label, R30)
addc(R1, 1, R0)
```

|            | Punjenje 1    | Punjenje 2    | Punjenje 3    |
| ---------- | ------------- | ------------- | ------------- |
| **Adresa** | 0x0000        | 0x0051        | 0x0113        |
| `cmpeqc`   | `0xd041 0064` | `0xd041 0064` | `0xd041 0064` |
| `beq`      | `0x73c2 0005` | `0x73c2 0056` | `0x73c2 ????` |
| `addc`     | `0xc001 0001` | `0xc001 0001` | `0xc001 0001` |

`cmpeqc` i `addc` imaju **konstantne** operande (`0x0064` = 100 i `0x0001` = 1) — ne menjaju se ni u jednom punjenju.

`beq(R2, Label, R30)` referiše **simbol `Label`**, pa je adresno osetljiva lokacija. Punjač njen operand pri relokaciji podešava dodavanjem početne adrese segmenta.

Iz Punjenja 1 (početna adresa `0x0000`) sledi da je `Label` na pomeraju **`0x0005`**.

Provera na Punjenju 2: $\text{0x0051} + \text{0x0005} = \text{0x0056}$ ✓

Punjenje 3: $\text{0x0113} + \text{0x0005} = \text{0x0118}$

> **Odgovor: `0x73c2 0118`**

### 10.6 _(dopunjavanje)_

**Odrediti vrednost simbola `function` koji se nalazi u modulu M3, ako povezivač povezuje module M1, M2, M3 u datom redosledu, a odstojanje simbola `function` unutar modula M3 je `0x210`. Početna adresa punjenja je `0x00800000`, veličine modula su redom `0x2500`, `0x250`, `0x500`.**

| Modul | Početna adresa | Veličina |
| ----- | -------------- | -------- |
| M1    | `0x00800000`   | `0x2500` |
| M2    | `0x00802500`   | `0x250`  |
| M3    | `0x00802750`   | `0x500`  |

$$\text{function} = \text{0x00802750} + \text{0x210} = \mathbf{0x00802960}$$

> **Odgovor: `0x00802960`**

Povezivač dodeljuje memoriju modulima **redom**, pa je početna adresa svakog modula zbir početne adrese punjenja i veličina svih prethodnih modula. Vrednost globalnog simbola je **početna adresa njegovog modula + odstojanje unutar modula**.

> Veličina modula M3 (`0x500`) je suvišan podatak — služi da zavara.

---

# 11. Raspoređivanje instrukcija

### 11.1 _(dopunjavanje)_

**Koje vrste zavisnosti postoje u grafu toka podataka? Kratko ih opisati.**

Tri vrste:

1. **RAW — čitanje posle pisanja** (_prava_, engl. true). Izlaz iz `I₁` je ulaz u `I₂`.
2. **WAR — pisanje posle čitanja** (_antizavisnost_, engl. anti). Izlaz iz `I₂` je ulaz u `I₁`.
3. **WAW — pisanje posle pisanja** (_izlazna_, engl. output). Izlaz iz `I₁` je izlaz i iz `I₂`.

Primer:

```
1. X <- 5 - Z
2. Y <- X * 7
3. X <- 2
```

- `1 → 2` je **RAW**: instrukcija 1 upisuje `X`, instrukcija 2 ga čita.
- `2 → 3` je **WAR**: instrukcija 2 čita `X`, instrukcija 3 ga upisuje.
- `1 → 3` je **WAW**: obe instrukcije upisuju `X`.

---

# 12. Lingvistički nivoi

### 12.1 🔴 _(zaokruživanje)_

**Tehnike definisanja novih lingvističkih nivoa su:**

- ✅ **a) Proširenje** — nove procedure koriste primitive osnovnog sistema
- ✅ **b) Prevođenje** (kompajliranje) — sa novog jezika na jezik osnovnog sistema
- ⚠️ c) Kombinacija — _vidi napomenu_
- ❌ d) Dodavanje — ne postoji takva tehnika

Predavanje pod naslovom **„Tehnike za definisanje novih lingvističkih nivoa"** nabraja tačno **tri**:

1. **Proširenje** — nove procedure koriste primitive osnovnog sistema
2. **Prevođenje** (kompajliranje) — sa novog jezika na jezik osnovnog sistema
3. **Interpretacija** — faze prevođenja i izvršenja su vremenski zavisne

> **⚠️ Nesigurno: opcija c).** „Kombinacija" **nije** među te tri tehnike. Ali drugi slajd kaže: _„Programi definišu novi lingvistički nivo proširivanjem, prevođenjem, interpretacijom **ili nekom kombinacijom** ovih tehnika."_
>
> Dakle: ako se pitanje čita kao spisak tehnika → tačno je samo **a) i b)**. Ako se čita kao „načini definisanja nivoa" → tačno je i **c)**. Proveriti sa profesorom.

**Sigurno:** `d)` je netačno, a **interpretacija** je treća tehnika koja ovde nije bila ponuđena.

---

# 13. Kompaktor

**Podsetnik:** kompaktor barata skupom tehnika hijerarhijski organizovanih u dva nivoa. Tehnike **nižeg nivoa** rade na mikro nivou (nad jednom instrukcijom ili parom instrukcija), a tehnike **višeg nivoa** na makro nivou (nad segmentima, tj. grupama instrukcija). Osnovni zahtev je uvek: **očuvati semantiku programa.**

### 13.1 _(dopunjavanje)_

**Nabrojati tehnike kompaktovanja koda nižeg reda.**

1. **ZAMENI** — zameni redosled zadate instrukcije i zadatog `NOP`-a, na postojećim adresama, unutar segmenta
2. **IZBACI** — izbaci zadati `NOP`
3. **ZAMENI-PREDHODNI** — zameni redosled zadate instrukcije segmenta sa zadatim `NOP`-om iz **prethodnog** segmenta
4. **ZAMENI-NAREDNI** — zameni redosled zadate instrukcije segmenta sa zadatim `NOP`-om iz **narednog** segmenta
5. **PREIMENUJ** — preimenuj resurs (akumulator) sa korišćenog imena na slobodno
6. **MUTIRAJ** — mutiraj instrukciju

> Za poređenje, tehnike **višeg reda** su četiri: `TRAŽI-UNAPRED`, `TRAŽI-UNAZAD`, `KOMPAKTUJ-SA-PRETHODNIM`, `KOMPAKTUJ-SA-NAREDNIM`.
>
> `TRAŽI-UNAPRED` i `TRAŽI-UNAZAD` koriste primitive `ZAMENI` i `IZBACI`. `KOMPAKTUJ-SA-PRETHODNIM` koristi `ZAMENI-PREDHODNI` i `IZBACI`, a `KOMPAKTUJ-SA-NAREDNIM` koristi `ZAMENI-NAREDNI` i `IZBACI`.

### 13.2 _(dopunjavanje)_

**Opisati tehniku kompaktovanja ZAMENI-PREDHODNI.**

Tehnika **nižeg nivoa**: zameni redosled zadate instrukcije segmenta sa zadatim `NOP`-om iz **prethodnog** segmenta.

Slična je tehnici **ZAMENI**, uz dve bitne razlike:

1. **kontekst je segment-preci** (a ne isti segment), i
2. **u svakom pretku se zamenjuje po jedan `NOP`**.

> Mora očuvati semantiku programa. Koristi je tehnika višeg nivoa **KOMPAKTUJ-SA-PRETHODNIM**, zajedno sa primitivom `IZBACI`.

---

# 14. Izbor instrukcija

### 14.1 _(dopunjavanje)_

**Trošak posmatranog čvora stabla međukoda (prilikom izbora instrukcija primenom dinamičkog programiranja) definisan je kao:**

> **Zbir troškova instrukcija koje najbolje (najjeftinije) pokrivaju podstablo čiji je koren taj čvor.**

Za svaki čvor se posmatraju sve pločice (šabloni instrukcija) koje se u njemu mogu uklopiti. Za svaku se sabere trošak same instrukcije i već izračunati minimalni troškovi podstabala koja ta pločica ostavlja nepokrivenim. Trošak čvora je **minimum** po svim tim mogućnostima.

> **Napomena:** predavanje obrađuje samo **maksimalni zalogaj** (engl. _munch_) — subotpimalni algoritam popločavanja koji od korena bira najveći šablon koji se uklapa. Tema optimalnosti se pominje, ali dinamičko programiranje nije izloženo.

---

# 15. Paralelno programiranje

### 15.1 _(dopunjavanje)_

**Navesti 4 uobičajena koraka u pisanju paralelnih programa.**

To su **četiri projektantska prostora**:

**Izražavanje algoritma:**

1. **Pronalaženje paralelizma** — uočavanje konkurentnih zadataka
2. **Struktura algoritma** — preslikavanje zadataka na procese radi korišćenja paralelnih arhitektura

**Konstruisanje programa:**

3. **Pomoćne strukture** — obrasci koda i struktura podataka
4. **Izvedbeni mehanizmi** — mehanizmi niskog nivoa koji se koriste za pisanje paralelnih programa

---

# 16. Leksička analiza

### 16.1 _(dopunjavanje)_

**Tri osnovna zadatka koja čine leksičku analizu koda.**

Lekser (skener) nudi tri funkcije:

1. **Dobavi naredni token**
2. **Vrati nazad poslednji token**
3. **Virni u naredni token** (bez dobavljanja)

> ⚠️ Postavka na roku je bila odsečena. Ovo su tri funkcije leksera iz predavanja o školskom kompajleru — jedino mesto gde predavanja nabrajaju tačno tri stavke uz leksičku analizu. Proveriti sa profesorom ako se pitanje ponovi.
