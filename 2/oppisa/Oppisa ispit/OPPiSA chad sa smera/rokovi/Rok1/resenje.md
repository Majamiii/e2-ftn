# Rok 1 — rešenja

## Eliminacioni deo — `1.jpg`

*Sve ispravno odgovoreno donosi 10 poena; jedna ili više grešaka donosi 0 poena na celom ispitu.*

---

### 1. Napisati telo funkcije `foo` tako da njeno vreme izvršavanja na procesoru sa jednim jezgrom ima asimptotski usku granicu Θ(n²)

```cpp
void foo(int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cout << "nesto" << endl;
}
```

Dve ugnježdene petlje po `n` iteracija, telo Θ(1) → Θ(n²).

---

### 2. Šta je tačno, a šta nije?

- ❌ a) Tabela simbola definiše razliku između mašinskih i pseudo instrukcija.
- ✅ **b) Popunjena tabela simbola je ulaz u drugi prolaz asemblera.**
- ❌ c) Popunjena tabela simbola je ulaz u prvi prolaz asemblera (tj. ugrađena je u asembler).
- ❌ d) Tabela simbola pridružuje kod operacije broju koji predstavlja njegovu vrednost.

Razliku između mašinskih i pseudo operacija definiše **tabela koda operacije**. Prvi prolaz **popunjava** tabelu simbola, drugi je **koristi**. Tabela simbola pridružuje **simbol** broju koji predstavlja njegovu vrednost.

---

### 3. Koje grupe skupova mogu predstavljati formalnu gramatiku?

Formalna gramatika je četvorka `G(N, T, Σ, P)` gde je `Σ ∈ N`, a `N` i `T` moraju biti **disjunktni**.

| | Terminalni | Neterminalni | Početni | |
|---|---|---|---|---|
| 1 | a, b, c, +, /, d, z | x, y, a, b | y | ❌ |
| 2 | a, b, c, +, -, d | x, y, z | z | ✅ |
| 3 | a, b, c, +, -, d | x, y, z | a | ❌ |
| 4 | a, b, c, \*, + | \*, / | a | ❌ |

- **1)** `N ∩ T = {a, b} ≠ ∅` — skupovi nisu disjunktni.
- **2)** Disjunktni su, a `z ∈ N`. **Ispravna.**
- **3)** Disjunktni jesu, ali `a ∉ N` — početni simbol mora biti neterminal.
- **4)** `N ∩ T = {*} ≠ ∅`, a uz to je i `a ∉ N`. Dve greške.

**Zaokružuje se samo grupa 2**, ostale tri se precrtavaju.

---

### 4. Za dati graf toka upravljanja zaokružiti tačne i precrtati netačne tvrdnje

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

- ✅ **a) Promenljiva `c` se koristi (use) u čvoru 3** — `c := c + b`.
- ❌ b) Promenljiva `b` se koristi (use) u čvoru 2 — tu se `b` **definiše**.
- ✅ **c) Promenljiva `a` je živa na izlazu iz čvora 4** — `out[4] = {a, c}`.
- ✅ **d) Promenljiva `a` je živa na ulazu u čvor 2** — `in[2] = {a, c}`.

---

## Glavni deo — `2.jpg` – `4.jpg`

*Ispravan odgovor donosi 4 poena, negativnih bodova nema.*

---

### 1. Primenom Master teoreme odrediti asimptotsko ograničenje za T(n) = 4T(n/5) + n lg n

$a = 4$, $b = 5$, $f(n) = n\lg n$

$$\log_b a = \log_5 4 = 0{,}861 \quad\Rightarrow\quad n^{\log_b a} = n^{0,861}$$

Iz $4 = 5^x$ sledi $x \in (0,1)$, pa je $n^x < n \le n\lg n$ — dakle $f(n)$ je **polinomijalno veća** → **slučaj 3**.

Uslov regularnosti: $4 \cdot \tfrac{n}{5}\lg\tfrac{n}{5} = \tfrac{4}{5}n(\lg n - \lg 5) \le \tfrac{4}{5}n\lg n$, sa $c = 4/5 < 1$. Ispunjen.

> $$T(n) = \Theta(f(n)) = \Theta(n \lg n)$$

**Pazi:** nije dovoljno izračunati $\log_b a$ i napisati $\Theta(n^{\log_b a})$. `f(n)` se poredi sa $n^{\log_b a}$, i **veća od te dve funkcije određuje rešenje**.

---

### 2. Da li postoji mogućnost za savršeno linearno ubrzanje na 4 procesora, ako je rad 33 a raspon 9?

**Ne.**

Savršeno linearno ubrzanje znači $T_1/T_P = P$, odnosno

$$T_P = \frac{T_1}{P} = \frac{33}{4} = 8{,}25$$

Ali **zakon raspona** kaže $T_P \ge T_\infty = 9$. Kako je $8{,}25 < 9$, takvo vreme je nemoguće.

Ekvivalentno preko paralelizma: $T_1/T_\infty = 33/9 = 3{,}67 < 4 = P$. Paralelizam je gornja granica ubrzanja, pa se sa 4 procesora ne može dostići ubrzanje 4.

---

### 3. Kako bi izgledao kod istih svojstava (rad i raspon), ali koristeći samo `_Cilk_spawn` i `_Cilk_sync`?

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

Rad: $\Theta(N)$. Raspon: $\Theta(\lg N)$ — isto kao `_Cilk_for`.

**Zašto ne prosto `for` + `_Cilk_spawn`?** Tada bi sama `for` petlja bila serijska, pa bi raspon bio $\Theta(N)$ umesto $\Theta(\lg N)$.

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

### 6. Pored svake petlje napisati da li je dobro formirana

Petlja je *dobro formirana* ako se broj iteracija zna unapred — tokom prevođenja (*veoma dobro formirana*) ili bar pre prve iteracije.

```c
for (i = 0; i < foo(y); ++i) { y = (y + x) % 7; }
```
> **Nije** — `foo(y)` se računa svake iteracije, a `y` se menja u telu.

```c
i = 0; while (i < 10) { y *= x; i += 1; }
```
> **Jeste**, i to *veoma dobro formirana* — broj iteracija (10) poznat je pri prevođenju.

```c
for (i = 7; i < N; i += 5) { y /= z; }
```
> **Jeste** — `N` se ne menja u telu, pa je broj iteracija poznat pre prve iteracije. Nije *veoma dobro formirana*.

```c
for (i = 6; i <= 100; i *= 5) { y += i; }
```
> **Nije** — `i *= 5` nije kanonički oblik; iteraciona promenljiva se množi umesto da se uvećava za konstantan korak.

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

**Graf smetnji** (spajaju se čvorovi čiji se opsezi preklapaju):

```
        x --------- y
          \        /
            \    /
              \/
              a


        z --------- b
```

Trougao `{x, y, a}` — sve tri su žive istovremeno na `if (x > 5)`. Zasebna grana `z — b`, jer su obe žive na `return z - b`. Opseg `a` se završava tamo gde `z` počinje, pa oni **nisu** u smetnji.

Graf je 3-obojiv (`x`=1, `y`=2, `a`=3, `z`=1, `b`=2), pa su tri registra dovoljna:

```
      (1) --------- (2)
        \          /
          \      /
            \  /
            (3)


      (1) --------- (2)
```

---

### 9. Koje vrste zavisnosti postoje u grafu toka podataka?

1. **RAW — čitanje posle pisanja** (*prava*, true). Izlaz iz `I₁` je ulaz u `I₂`.
2. **WAR — pisanje posle čitanja** (*antizavisnost*, anti). Izlaz iz `I₂` je ulaz u `I₁`.
3. **WAW — pisanje posle pisanja** (*izlazna*, output). Izlaz iz `I₁` je izlaz i iz `I₂`.

---

### 10. Navedi četiri osnovne funkcije punjača

1. **Alokacija** — dodela memorijskog prostora programima.
2. **Povezivanje** — određivanje vrednosti simboličkih referenci između relokatibilnih programa.
3. **Relokacija** — podešavanje svih adresno osetljivih lokacija na dodeljeni prostor.
4. **Punjenje** — fizički prenos mašinskih instrukcija i podataka u memoriju.
