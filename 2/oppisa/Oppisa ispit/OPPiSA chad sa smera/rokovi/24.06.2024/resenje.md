# Rok 24.06.2024 — rešenja

## Eliminacioni deo — `1..jpg`

*Sve ispravno odgovoreno donosi 10 poena; jedna ili više grešaka donosi 0 poena na celom ispitu.*

---

### 1. Napisati telo funkcije `foo` tako da njeno vreme izvršavanja na jednom jezgru ima asimptotski usku granicu Θ(n³)

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

### 2. Koliki je rad funkcije `foo` iz prethodnog pitanja? Kratko obrazložiti.

> $T_1 = \Theta(n^3)$

Rad je vreme izvršavanja na jednom procesoru, a ono za `foo` ima asimptotski usku granicu Θ(n³).

---

### 3. Šta je tačno, a šta nije?

- ❌ a) Tabela simbola definiše razliku između mašinskih i pseudo instrukcija.
- ✅ **b) Popunjena tabela simbola je ulaz u drugi prolaz asemblera.**
- ❌ c) Popunjena tabela simbola je ulaz u prvi prolaz asemblera (tj. ugrađena je u asembler).
- ❌ d) Tabela simbola pridružuje kod operacije broju koji predstavlja njegovu vrednost.

Razliku između mašinskih i pseudo operacija definiše **tabela koda operacije**. Prvi prolaz **popunjava** tabelu simbola, drugi je **koristi**. Tabela simbola pridružuje **simbol** broju koji predstavlja njegovu vrednost.

---

### 4. Koliko u gramatici ima neterminalnih simbola? Zaokružiti ih.

```
S -> x = P            P -> 2 - F            F -> x
S -> F = 2 - P / t    P -> F / t            F -> 2 - P
```

> **3 neterminalna simbola:** `S`, `P`, `F`

Broje se **različiti simboli**, a ne njihova pojavljivanja. Ista gramatika ima **6 produkcija** i **6 terminalnih** simbola (`x`, `=`, `2`, `-`, `/`, `t`).

---

### 5. Za dati graf toka upravljanja zaokružiti tačne i precrtati netačne tvrdnje

```
1: a := 0
2: b := a + 1     <- povratna grana iz čvora 5
3: c := c + b
4: a := b * 2
5: a < N          -> nazad na 2, ili dalje na 6
6: return c
```

| Čvor | `def` | `use` | `in` | `out` |
|---|---|---|---|---|
| 1 | a | — | c | a, c |
| 2 | b | a | a, c | b, c |
| 3 | c | c, b | b, c | b, c |
| 4 | a | b | b, c | a, c |
| 5 | — | a | a, c | a, c |
| 6 | — | c | c | — |

- ✅ **a) Promenljiva `c` se definiše u čvoru 3** — `c := c + b`.
- ✅ **b) Promenljiva `a` je živa na ulazu u čvor 5** — `in[5] = {a, c}`.
- ✅ **c) Promenljiva `a` je živa na izlazu iz čvora 4** — `out[4] = {a, c}`.
- ❌ d) Promenljiva `b` se definiše u čvoru 4 — u čvoru 4 (`a := b * 2`) se `b` **koristi**, a definiše se `a`.

---

### 6. Ako graf ima 5 čvorova i svaki čvor ima rang 4

**a) Koliko taj graf ima ivica?**

Zbir rangova svih čvorova jednak je dvostrukom broju ivica:

$$5 \cdot 4 = 20 = 2E \quad\Rightarrow\quad E = 10$$

> **10 ivica**

**b) Koji je najmanji broj boja sa kojim može biti obojen?**

Svaki čvor je susedan sa preostala 4 — to je **potpun graf K₅**. U potpunom grafu su svaka dva čvora susedna, pa nikoja dva ne mogu deliti boju.

> **5 boja**

Opšte: graf sa `n` čvorova gde svaki ima rang `n-1` je `Kₙ`, ima $\frac{n(n-1)}{2}$ ivica i zahteva `n` boja.

---

## Glavni deo — `2..jpg` – `4..jpg`

*Ispravan odgovor donosi 4 poena, negativnih bodova nema.*

---

### 1. Primenom Master teoreme odrediti asimptotsko ograničenje za T(n) = 7T(n/8) + n lg n

$a = 7$, $b = 8$, $f(n) = n\lg n$

$$\log_b a = \log_8 7 = 0{,}9358 \quad\Rightarrow\quad n^{\log_b a} = n^{0,9358}$$

Iz $7 = 8^x$ sledi $x \in (0,1)$, pa je $n^x < n \le n\lg n$ — $f(n)$ je **polinomijalno veća** → **slučaj 3**.

Uslov regularnosti: $7\cdot\tfrac{n}{8}\lg\tfrac{n}{8} = \tfrac{7}{8}n(\lg n - 3) \le \tfrac{7}{8}n\lg n$, sa $c = 7/8 < 1$. Ispunjen.

> $$T(n) = \Theta(f(n)) = \Theta(n \lg n)$$

**Pazi:** nije dovoljno izračunati $\log_b a$ i napisati $\Theta(n^{\log_b a})$. `f(n)` se **poredi** sa $n^{\log_b a}$, i veća od te dve funkcije određuje rešenje.

---

### 2. Rad 2048s i raspon 1s izmenjeni na rad 1024s i raspon 8s. Kako su se promenile gornje i donje granice na 32 i 512 jezgara?

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

**Pazi na donju granicu.** Važe **oba** zakona ($T_P \ge T_1/P$ i $T_P \ge T_\infty$), pa je prava donja granica njihov maksimum. Za izmenjenu verziju na 512 jezgara $T_1/P = 2$, ali je $T_\infty = 8$, pa je donja granica **8**, a ne 2.

---

### 3. Napisati telo funkcija `foo` i `bar` tako da `foo` ima Θ(n^2.5), a `bar` Θ(lg n)

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

$n \cdot n \cdot \sqrt{n} = n^{2,5}$

```c
void bar(int n) {
    int x = 1;
    int y = 2;
    for (int i = 1; i < n; i *= 2)
        x += y;
}
```

`i` uzima vrednosti $1, 2, 4, 8, \dots$, pa se petlja izvrši $\lfloor\lg n\rfloor + 1$ puta $= \Theta(\lg n)$.

> **Pazi:** korak mora biti `i *= 2`. Sa `i*2` se `i` ne menja i petlja je beskonačna.

---

### 4. Poželjne osobine međukoda su

- **a)** Pogodan je za davanje značenja čvorovima stabla sintaksne analize
- **b)** Pogodan je za prevođenje u mašinski jezik odredišnog procesora
- **c)** Čvorovi stabla međukoda treba da imaju jasna i jednostavna značenja
  *(radi lake specifikacije i realizacije optimizacionih transformacija)*

---

### 5. Napisati jednačine životnog veka promenljivih za čvor n

$$in[n] = use[n] \cup (out[n] - def[n])$$

$$out[n] = \bigcup_{succ[n]} in[s]$$

- $in[n]$ — promenljive koje žive na ulazu u čvor
- $out[n]$ — promenljive koje žive na izlazu čvora
- $use[n]$ — promenljive koje čvor koristi
- $def[n]$ — promenljive koje čvor definiše
- $\bigcup_{succ[n]}$ — unija po svim čvorovima naslednicima čvora n

---

### 6. Zadatu gramatiku transformisati u gramatiku bez konflikta

```
E -> E + T          T -> id
E -> E - T          T -> num
E -> T              T -> ( E )
```

Gramatika je **levo rekurzivna** (`E -> E + T`), a leva rekurzija je specijalan slučaj preklapanja `FIRST` skupova dve produkcije. Uklanja se prevođenjem u desnu rekurziju:

```
E  -> T E'          T -> id
E' -> + T E'        T -> num
E' -> - T E'        T -> ( E )
E' -> ε
```

**Pazi:** produkcije za `E'` moraju imati **repno `E'`**. Bez njega bi izraz mogao imati najviše jedan operator, pa se `id + num - id` ne bi mogao izvesti.

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

Sekcije `.data` i `.text` imaju **odvojene** brojače lokacija, oba počinju od 0.

---

### 8. Graf smetnji i graf toka upravljanja za dati Ce kod

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

**Graf toka upravljanja:**

```
              +----------------+
              |  B1            |
              |    a = 5       |
              |    x > 5       |
              +----------------+
                 |          |
            da   |          |   ne
                 v          v
   +---------------+    +---------------+
   |  B2           |    |  B3           |
   |    z = y - a  |    |    z = x      |
   +---------------+    +---------------+
                 |          |
                 v          v
              +----------------+
              |  B4            |
              |    b = 7       |
              |    return z-b  |
              +----------------+
```

**Opsezi životnog veka:**

| Promenljiva | Živa od | Živa do |
|---|---|---|
| `x` | ulaz u funkciju | `x > 5` i `z = x` |
| `y` | ulaz u funkciju | `z = y - a` |
| `a` | `a = 5` | `z = y - a` |
| `z` | `z = y - a` / `z = x` | `return z - b` |
| `b` | `b = 7` | `return z - b` |

**Graf smetnji** (brojevi u zagradi su boje/registri):

```
        x(1) --------- y(2)
          \           /
            \       /
              \   /
              a(3)


        z(1) --------- b(2)
```

Grane: `x–y`, `x–a`, `y–a`, `z–b`

Trougao `{x, y, a}` — sve tri su žive istovremeno na `if (x > 5)`. Zasebna grana `z—b`, jer su obe žive na `return z - b`. Opseg `a` se završava tamo gde `z` počinje, pa oni **nisu** u smetnji.

> Graf je **3-obojiv** — tri registra su dovoljna.

---

### 9. Koje vrste zavisnosti postoje u grafu toka podataka?

1. **RAW — čitanje posle pisanja** (*prava*, true). Izlaz iz `I₁` je ulaz u `I₂`.
2. **WAR — pisanje posle čitanja** (*antizavisnost*, anti). Izlaz iz `I₂` je ulaz u `I₁`.
3. **WAW — pisanje posle pisanja** (*izlazna*, output). Izlaz iz `I₁` je izlaz i iz `I₂`.

Primer:

```
1. X <- 5 - Z
2. Y <- X * 7
3. X <- 2
```

`1 → 2` je RAW, `2 → 3` je WAR, `1 → 3` je WAW.

---

### 10. Navedi četiri osnovne funkcije punjača

1. **Alokacija** — dodela memorijskog prostora programima.
2. **Povezivanje** — određivanje vrednosti simboličkih referenci između relokatibilnih programa.
3. **Relokacija** — podešavanje svih adresno osetljivih lokacija na dodeljeni prostor.
4. **Punjenje** — fizički prenos mašinskih instrukcija i podataka u memoriju.
