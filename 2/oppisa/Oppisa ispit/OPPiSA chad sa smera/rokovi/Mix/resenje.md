# Mix — rešenja

*Isečci sa više rokova. Sekcije su imenovane po slikama.*

---

# `Nesto.jpg` — Eliminacioni deo

### 1. Napisati petlju u C++ koja ima gornju usku asimptotsku granicu O(n²)

```cpp
void foo(int n){
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cout << "foo" << endl;
}
```

Dve ugnježdene petlje po `n` iteracija, telo Θ(1) → O(n²), i granica je **uska** (petlja zaista dostiže n²).

---

### 2. Odrediti gornju usku asimptotsku granicu raspona prethodno napisane petlje

> $T_\infty = O(n^2)$

Petlja je **potpuno serijska** — nema `parallel_for` ni `spawn`. Kod serijskog koda kritični put je ceo program, pa je raspon jednak radu: $T_\infty = T_1 = O(n^2)$.

---

### 3. Podeliti kod na osnovne blokove i napisati `def` i `use` skupove

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

```
              +----------------+
              |  B1            |   def = {b}
              |    b = 5       |   use = {x}
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
              |    b = 7       |   use = {b, a}
              |    return b-a  |
              +----------------+
```

| Blok | `def` | `use` |
|---|---|---|
| B1 | b | x |
| B2 | z | y, a |
| B3 | z | x |
| B4 | b | b, a |

`def` i `use` nisu disjunktni: u B4 se `b` i definiše (`b = 7`) i koristi (`return b - a`).

---

# `Nesto2.jpg` — Glavni deo

### 1. Master teorema za T(n) = T(2n/3) + 1

$a = 1$, $b = 3/2$, $f(n) = 1 = n^0$

$$\log_b a = \log_{3/2} 1 = 0 \quad\Rightarrow\quad n^{\log_b a} = n^0 = 1$$

Kako je $f(n) = \Theta(n^0) = \Theta(1)$, to je **slučaj 2**.

> $$T(n) = \Theta\!\left(n^{\log_b a} \lg n\right) = \Theta(\lg n)$$

---

### 2. Napisati teoremu o gornjoj granici vremena izvršavanja algoritma na P procesora. Objasniti korišćene oznake.

**Teorema o gornjoj granici $T_P$:** na `P` procesora, **pohlepni raspoređivač** izvršava paralelni algoritam sa radom $T_1$ i rasponom $T_\infty$ u vremenu

$$T_P \le \frac{T_1}{P} + T_\infty$$

Oznake:

- $T_P$ — vreme izvršavanja na `P` procesora
- $T_1$ — **rad**, vreme izvršavanja na jednom procesoru
- $T_\infty$ — **raspon**, vreme za neograničen broj procesora (kritični put)
- $P$ — broj procesora

Posledice:

- $T_P$ nikada nije više od 2 puta veće od optimalnog vremena $T_P^*$, tj. $T_P \le 2\,T_P^*$
- Ako je $P \ll T_1/T_\infty$ (paralelizam algoritma), onda je $T_P \approx T_1/P$, tj. ubrzanje je približno jednako `P`

---

### 3. Odrediti RAD, RASPON i PARALELIZAM za proceduru `Foo(A, B)`

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

**RAD** — serijalizacija (sve `parallel_for` postaju obične `for`): dominira trostruka ugnježdena petlja.

$$T_1(n) = \Theta(n^3)$$

**RASPON** — za paralelnu petlju sa `n` iteracija važi $T_\infty(n) = \Theta(\lg n) + \max_i iter_\infty(i)$.

- Prva petlja: `parallel_for` → $\Theta(\lg n)$, unutrašnji **serijski** `for` → $\Theta(n)$. Ukupno $\Theta(n)$.
- Druga petlja: dve ugnježdene `parallel_for` → $\Theta(\lg n)$, unutrašnji **serijski** `for` po `k` → $\Theta(n)$. Ukupno $\Theta(n)$.

$$T_\infty(n) = \Theta(n)$$

**PARALELIZAM:**

$$\frac{T_1(n)}{T_\infty(n)} = \frac{\Theta(n^3)}{\Theta(n)} = \Theta(n^2)$$

---

### 4. Navesti 4 uobičajena koraka u pisanju paralelnih programa

To su **četiri projektantska prostora**:

**Izražavanje algoritma:**

1. **Pronalaženje paralelizma** — uočavanje konkurentnih zadataka
2. **Struktura algoritma** — preslikavanje zadataka na procese radi korišćenja paralelnih arhitektura

**Konstruisanje programa:**

3. **Pomoćne strukture** — obrasci koda i struktura podataka
4. **Izvedbeni mehanizmi** — mehanizmi niskog nivoa koji se koriste za pisanje paralelnih programa

---

### 5. Tri osnovna zadatka koja čine leksičku analizu koda

Lekser (skener) nudi tri funkcije:

1. **Dobavi naredni token**
2. **Vrati nazad poslednji token**
3. **Virni u naredni token** (bez dobavljanja)

> ⚠️ Postavka je na slici odsečena. Ovo su tri funkcije leksera iz predavanja o školskom kompajleru — jedino mesto gde predavanja nabrajaju tačno tri stavke uz leksičku analizu.

---

# `Nesto3.jpg`

### 9. Opisati tehniku kompaktovanja ZAMENI-PREDHODNI

**ZAMENI-PREDHODNI** je tehnika **nižeg nivoa**: zameni redosled zadate instrukcije segmenta sa zadatim `NOP`-om iz **prethodnog** segmenta.

Slična je tehnici **ZAMENI**, uz dve bitne razlike:

1. **kontekst je segment-preci** (a ne isti segment), i
2. **u svakom pretku se zamenjuje po jedan NOP**.

Kao i sve tehnike kompaktora, mora da očuva semantiku programa. Koristi je tehnika višeg nivoa **KOMPAKTUJ-SA-PRETHODNIM** (zajedno sa primitivom IZBACI).

---

### 10. Odrediti vrednost simbola `function` u modulu M3

Povezivač redom smešta module M1, M2, M3. Početna adresa punjenja: `0x00800000`. Veličine: `0x2500`, `0x250`, `0x500`. Odstojanje simbola `function` unutar M3 je `0x210`.

| Modul | Početna adresa | Veličina |
|---|---|---|
| M1 | `0x00800000` | `0x2500` |
| M2 | `0x00802500` | `0x250` |
| M3 | `0x00802750` | `0x500` |

$$\text{function} = \text{0x00802750} + \text{0x210} = \mathbf{0x00802960}$$

> **Odgovor: `0x00802960`**

Povezivač dodeljuje memoriju segmentima redom, a vrednost globalnog simbola je **početna adresa njegovog modula + odstojanje unutar modula**.

---

# `Nesto4.jpg`

### 5. Transformisati datu gramatiku tako da ne dođe do konflikta

```
E -> T - E        T -> id
E -> T + E        T -> num
E -> T            T -> (E)
```

Ova gramatika **nije levo rekurzivna** — problem je što sve tri produkcije za `E` počinju istim simbolom `T`, pa im se **`FIRST` skupovi preklapaju**. Rešenje je **izdvajanje leve zajedničke osnove** (levo faktorisanje), a ne uklanjanje leve rekurzije.

Opšte pravilo: `A -> α β₁ | α β₂ | α` postaje `A -> α A'`, `A' -> β₁ | β₂ | ε`.

Ovde je `α = T`, `β₁ = - E`, `β₂ = + E`:

```
E  -> T E'        T -> id
E' -> - E         T -> num
E' -> + E         T -> (E)
E' -> ε
```

---

### 6. Ispod svake petlje napisati da li je dobro formirana

Petlja je *dobro formirana* ako se broj iteracija zna unapred — tokom prevođenja (*veoma dobro formirana*) ili bar pre prve iteracije.

```c
for(int i = 0; i < foo(y); i++){ y = (y + x) % 7; }
```
> **Nije dobro formirana** — `foo(y)` se računa svake iteracije, a `y` se menja u telu.

```c
int i = 0;
while(i < 10){ y *= i; i++; }
```
> **Dobro formirana**, i to *veoma dobro* — broj iteracija (10) poznat je pri prevođenju.

```c
for(int i = 7; i < 20; i+=5){ y += i; }
```
> **Dobro formirana**, i to *veoma dobro* — `i` uzima 7, 12, 17, dakle 3 iteracije, sve poznato pri prevođenju.

```c
for(int i = 5; i < N; i*= 5){ y += i; }
```
> **Nije dobro formirana** — `i *= 5` nije kanonički oblik; iteraciona promenljiva se množi umesto da se uvećava za konstantan korak.

---

# `Nesto5.jpg`

### 4. Zaokružiti terminalne simbole i prebrojati ih

```
S -> x = P            P -> z += x           E -> x * E
S -> x + P            P -> x + y = E        E -> y
S -> x * P / t
```

Neterminali (leve strane produkcija): `S`, `P`, `E`.

> **Terminalni simboli:** `x`, `=`, `+`, `*`, `/`, `t`, `z`, `+=`, `y`
>
> **Broj terminalnih simbola: 9**

> ⚠️ Ako se `+=` ne tretira kao **jedan** terminal nego kao `+` pa `=`, broj bi bio **8**. Pošto je u gramatici napisan spojeno, računamo ga kao jedan token.

---

### 5. Procesor ima 3 registra. Zaokružiti grafove smetnji koji će moći biti obojeni (neće doći do prelivanja)

Kriterijum: **UPROSTI** uklanja čvorove ranga < 3. Ako se graf isprazni, nema prelivanja. Ako ostane skup u kome svi imaju rang ≥ 3, mora se preliti. Potpun graf `K₄` uvek zahteva prelivanje sa 3 registra.

**a)** ✅ *može se obojiti*

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
Grane: `A–B`, `A–C`, `B–C`, `B–E`, `C–D`, `C–E`, `D–E`
Rangovi: `C`=4, `B`=3, `E`=3, `A`=2, `D`=2 → UPROSTI: `A`(2), `D`(2), pa ostatak. **Nema K₄.**

**b)** ✅ *može se obojiti*

```
             A(2)
              |
              |
   D(2)-----C(1)-----B(3)
              |    /
              |   /
             E(2)
```
Grane: `A–C`, `A–B`, `C–D`, `C–B`, `C–E`
Rangovi: `C`=4, `A`=2, `B`=2, `D`=1, `E`=1 → trougao `{A, B, C}`, tri boje dovoljne.

**c)** ✅ *može se obojiti*

```
   A(2)--------B(3)
    |  \        |  \
    |    \      |   C(2)
    |      \    |   /
    |        \  |  /
   D(3)--------E(1)
```
Grane: `A–B`, `A–D`, `A–E`, `B–E`, `B–C`, `C–E`, `D–E`
Rangovi: `E`=4, `A`=3, `B`=3, `C`=2, `D`=2 → UPROSTI: `C`(2), `D`(2), pa ostatak. **Nema K₄.**

**d)** ❌ *mora se preliti*

```
   A---------B---------C
   | \     / | \     / |
   |   \ /   |   \ /   |
   |   / \   |   / \   |
   | /     \ | /     \ |
   D---------E---------F
```
Grane: `A–B`, `B–C`, `D–E`, `E–F`, `A–D`, `B–E`, `C–F`, `A–E`, `B–D`, `B–F`, `C–E`

Svi čvorovi imaju rang ≥ 3 (`B` i `E` po 5, ostali po 3), pa se **UPROSTI odmah zaglavi**. Čvorovi `{A, B, D, E}` čine **K₄** — treba 4 boje, a imamo 3 registra.

> **Odgovor: zaokružuju se a), b) i c). Graf d) zahteva prelivanje.**

---

### 6. Zaokružiti tačne tvrdnje a precrtati netačne

- ❌ a) Tabela simbola sadrži vrstu sa kodom operacije i njegovom vrednošću
- ❌ b) Tabela simbola razlikuje mašinske i pseudo-instrukcije
- ❌ c) Tabela simbola je ulaz u prvi prolaz asemblera (ugrađena u asembler)
- ✅ **d) Tabela simbola je izlaz prvog prolaza asemblera**

Kod operacije drži **tabela koda operacije**, i ona takođe definiše razliku između mašinskih i pseudo operacija. Tabela simbola pridružuje **simbol** broju koji predstavlja njegovu vrednost. Prvi prolaz je **popunjava**, drugi je **koristi**.

---

# `Nesto6.jpg`

### 7. Vrednosti simbola `val1` i `end` nakon prvog prolaza asemblera

```mips
.globl main
.data                       # brojač lokacija = 0
arr:    .word 4 5 6 7       # 0   (4 x 4 = 16 B)
val0:   .word 1             # 16  (4 B)
val1:   .space 9            # 20  (9 B)
.text                       # brojač lokacija = 0
main:
        lw $t3, val0        # 0
        la $t1, arr         # 4
        lw $t2, val1        # 8
end:
        jr $ra              # 12
```

> **val1 = 20**, **end = 12**

Vrednost simbola je stanje brojača lokacija u trenutku kada asembler naiđe na labelu. Sekcije `.data` i `.text` imaju **odvojene** brojače, oba počinju od 0.

---

### 8. Nacrtati graf toka upravljanja i graf smetnji za dati kod

*(isti kod kao u `Nesto.jpg`, pitanje 3)*

**Graf toka upravljanja** — vidi `Nesto.jpg` pitanje 3.

**Životni vek promenljivih:**

| Promenljiva | Živa od | Živa do |
|---|---|---|
| `x` | ulaz u funkciju | `if (x > 5)` i `z = x` |
| `y` | ulaz u funkciju | `z = y - a` |
| `a` | ulaz u funkciju (nikad se ne definiše!) | `return b - a` |
| `b` | `b = 7` | `return b - a` |
| `z` | — | **nikad nije živa** |

Dve zamke ovog koda: `a` se **koristi a nikad ne definiše**, a `z` se **definiše a nikad ne koristi** (`return b - a` ne čita `z`). Prva dodela `b = 5` je takođe mrtva, jer se `b` prepiše sa `b = 7` pre svake upotrebe.

**Graf smetnji** (brojevi u zagradi su boje/registri):

```
        x(1) --------- y(2)
          \           /
            \       /
              \   /
               a(3)
                |
                |
               b(1)

        z(1)   (izolovan — nikad živa)
```

Grane: `x–y`, `x–a`, `y–a`, `a–b`

Trougao `{x, y, a}` — sve tri su žive istovremeno na `if (x > 5)`. Grana `a–b` jer su obe žive na `return b - a`. Čvor `z` nema nijednu granu.

> **Graf je 3-obojiv** — tri registra su dovoljna.

---

# `Nesto7.jpg` — Ispitni (glavni) deo

### 1. Master teorema za T(n) = 24,7 · T(n/3) + n²

$a = 24{,}7$, $b = 3$, $f(n) = n^2$

$$\log_b a = \log_3 24{,}7 = 2{,}919 \quad\Rightarrow\quad n^{\log_b a} = n^{2,919}$$

Provera: $3^3 = 27 > 24{,}7$, pa je $\log_3 24{,}7$ nešto malo manje od 3.

Ovde je $f(n) = n^2$ **polinomijalno manja** od $n^{2,919}$ → **slučaj 1**.

> $$T(n) = \Theta\!\left(n^{\log_3 24,7}\right) \approx \Theta(n^{2,919})$$

**Pazi:** nije dovoljno izračunati $\log_b a$; `f(n)` se **poredi** sa $n^{\log_b a}$, i veća od te dve funkcije određuje rešenje. Ovde je veća $n^{\log_b a}$.

---

### 2. Navesti osobine invarijante petlje koja se koristi radi dokazivanja korektnosti algoritma

1. **Inicijalizacija** — istinita je pre prve iteracije petlje.
2. **Održavanje** — ako je istinita pre iteracije petlje, ostaje istinita posle iteracije.
3. **Završetak** — kada se petlja završi, invarijanta daje korisnu osobinu za dokazivanje korektnosti.

Velika je sličnost sa matematičkom indukcijom, s tim što se ovde postupak zaustavlja kada se petlja završi.

---

### 3. Rad 2048s i raspon 1s → rad 1024s i raspon 8s. Kako se menjaju donja i gornja granica na 32 i 512 jezgara?

Donja granica: $T_P \ge \max(T_1/P,\ T_\infty)$. Gornja granica: $T_P \le T_1/P + T_\infty$.

| | $P$ | donja | gornja |
|---|---|---|---|
| original | 32 | $\max(64, 1) = 64$ | $64 + 1 = 65$ |
| optimizovan | 32 | $\max(32, 8) = 32$ | $32 + 8 = 40$ |
| original | 512 | $\max(4, 1) = 4$ | $4 + 1 = 5$ |
| optimizovan | 512 | $\max(2, 8) = 8$ | $2 + 8 = 10$ |

> **Na 32 jezgra** obe granice se smanjuju (64 → 32 i 65 → 40) — **poboljšanje**.
>
> **Na 512 jezgara** obe granice se povećavaju (4 → 8 i 5 → 10) — **pogoršanje**.

Na malom broju jezgara dominira rad, pa se isplati njegovo smanjenje. Na velikom broju jezgara dominira raspon, pa ga povećanje sa 1s na 8s odmah pokvari.

---

### 4. Kako bi izgledala petlja `_cilk_for` napisana pomoću `_cilk_spawn` i `_cilk_sync`?

`_cilk_for` je skraćeni zapis za rekurziju podeli-pa-vladaj:

```c
void recursion(int start, int end) {
    if (end - start <= 1) {
        for (int i = start; i < end; ++i)
            _do_something(i);
    }
    else {
        int middle = start + (end - start) / 2;
        _cilk_spawn recursion(start, middle);
        recursion(middle, end);
        _cilk_sync;
    }
}

recursion(0, N);
```

Rad $\Theta(N)$, raspon $\Theta(\lg N)$ — isto kao `_cilk_for`.

**Nije rešenje** staviti `_cilk_spawn` unutar obične `for` petlje: tada je sama petlja serijska, pa raspon postaje $\Theta(N)$.

---

# `Nesto8.jpg`

### 7. Dve osobine kanoničkog stabla međukoda

1. **Ne sadrži `SEQ` čvorove** (niz od dva iskaza) **ni `ESEQ` čvorove** (niz od jednog iskaza i jednog izraza).
2. **Predak `CALL` čvora** (poziv funkcije) **je čvor `EXP`** (izraz) **ili `MOVE`** (prebaci rezultat izraza u zadatu lokaciju).

---

### 8. Trošak posmatranog čvora stabla međukoda (pri izboru instrukcija primenom dinamičkog programiranja)

Trošak čvora je **zbir troškova instrukcija koje najbolje (najjeftinije) pokrivaju podstablo čiji je koren taj čvor.**

Drugim rečima, za svaki čvor se posmatraju sve pločice (šabloni instrukcija) koje se mogu uklopiti u njemu; za svaku se sabere trošak same instrukcije i već izračunati minimalni troškovi podstabala koja ta pločica ostavlja nepokrivenim. Trošak čvora je **minimum** po svim tim mogućnostima.

> ⚠️ Predavanje `P10.1` obrađuje samo **maksimalni zalogaj** (munch), koji je *subotpimalni* algoritam popločavanja, i pominje temu optimalnosti, ali ne izlaže dinamičko programiranje. Ovaj odgovor je standardna definicija.

---

### 9. Dva pravila za dodavanje nove smetnje u graf smetnji

1. Za svaku **definiciju promenljive `a` u čvoru koji nije `MOVE`**, dodaj smetnje između `a` i **svake promenljive žive na izlazu čvora**.
2. Za **`MOVE` instrukciju `a = c`**, dodaj smetnje između `a` i svake promenljive žive na izlazu čvora **koja nije `c`**.

Drugo pravilo postoji zato što `a` i `c` posle `MOVE`-a imaju istu vrednost, pa mogu deliti registar — time se omogućava kasnije uklanjanje suvišnih `MOVE` instrukcija spajanjem čvorova.

---

### 10. Nabrojati tehnike kompaktovanja koda nižeg reda

1. **ZAMENI** — zameni redosled zadate instrukcije i zadatog `NOP`-a, na postojećim adresama, unutar segmenta
2. **IZBACI** — izbaci zadati `NOP`
3. **ZAMENI-PREDHODNI** — zameni redosled zadate instrukcije segmenta sa zadatim `NOP`-om iz **prethodnog** segmenta
4. **ZAMENI-NAREDNI** — zameni redosled zadate instrukcije segmenta sa zadatim `NOP`-om iz **narednog** segmenta
5. **PREIMENUJ** — preimenuj resurs (akumulator) sa korišćenog imena na slobodno
6. **MUTIRAJ** — mutiraj instrukciju

Za poređenje, tehnike **višeg reda** su: `TRAŽI-UNAPRED`, `TRAŽI-UNAZAD`, `KOMPAKTUJ-SA-PRETHODNIM`, `KOMPAKTUJ-SA-NAREDNIM`.
