# Rok 14.07.2024 — rešenja

## Eliminacioni deo — `1.jpg`

*Sve ispravno odgovoreno donosi 10 poena; jedna ili više grešaka donosi 0 poena na celom ispitu.*

---

### 1. Ako je napisano T(n) = Θ(n²), to znači:

- ❌ a) da je funkcija `T(n)` jednaka **funkciji** `Θ(n²)`
- ✅ **b) da funkcija `T(n)` pripada skupu funkcija `Θ(n²)`**
- ❌ c) da funkcija `Θ(n²)` pripada skupu funkcija `T(n)`
- ❌ d) da je vreme izvršavanja jednako `n²` sekundi

`Θ(n²)` je **skup funkcija**, a znak `=` u zapisu `T(n) = Θ(n²)` zapravo znači **pripadnost** tom skupu. Nije ni jednakost funkcija, ni tvrdnja o konkretnom broju sekundi.

---

### 2. Ako vreme izvršavanja neke funkcije na jednom jezgru ima asimptotski usku granicu Θ(n²), koliki je rad te funkcije?

> $T_1 = \Theta(n^2)$

Rad je po definiciji vreme izvršavanja na jednom procesoru, pa je jednak datoj granici.

---

### 3. Šta je tačno, a šta nije?

- ❌ a) Tabela simbola definiše razliku između mašinskih i pseudo instrukcija.
- ✅ **b) Popunjena tabela simbola je ulaz u drugi prolaz asemblera.**
- ❌ c) Popunjena tabela simbola je ulaz u prvi prolaz asemblera (tj. ugrađena je u asembler).
- ❌ d) Tabela simbola pridružuje kod operacije broju koji predstavlja njegovu vrednost.

---

### 4. Zaokruži produkcije u gramatici. Navedi terminalne i neterminalne simbole.

```
S -> get E from S      L -> quit
S -> begin S L         L -> ; S L
S -> print E END       E -> num EQ num
```

> **Produkcija ima 6** — zaokružuje se svih šest redova.
>
> **Neterminalni (3):** `S`, `L`, `E`
>
> **Terminalni (9):** `get`, `from`, `begin`, `print`, `END`, `quit`, `;`, `num`, `EQ`

Neterminali su oni koji se pojavljuju sa **leve strane** neke produkcije. Sve ostalo su terminali.

---

### 5. Za dati kod nacrtati graf toka upravljanja i obeležiti osnovne blokove (`use` i `def` skupovi)

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

`def` su promenljive kojima blok zadaje vrednost, `use` one koje očitava. Skupovi **nisu disjunktni**: u B4 se `b` i definiše (`b = 7`) i koristi (`return z - b`).

Granice blokova: `B1` se završava uslovnim skokom (`x > 5`), a `B4` počinje jer je tačka spajanja obe grane.

---

### 6. Ako graf ima 6 ivica i 4 čvora

**a) Koliki je njegov rang?**

Zbir rangova svih čvorova jednak je dvostrukom broju ivica:

$$\sum \text{rang} = 2E = 12$$

Na 4 čvora prosečan rang je $12/4 = 3$. Kako u prostom grafu sa 4 čvora nijedan čvor ne može imati rang veći od 3, svi čvorovi imaju rang tačno 3.

**Rang grafa** je rang čvora sa najvećim rangom:

> **Rang grafa = 3**

**b) Koji je najmanji broj boja sa kojim može biti obojen?**

> **4 boje**

**c) Da li je potpun?**

> **Da.**

Svaki čvor je susedan sa preostala 3, pa svi čvorovi obrazuju kliku — to je definicija potpunog grafa. To je `K₄`, i hromatski broj je jednak broju čvorova u najvećoj kliki, dakle 4.

---

## Glavni deo — `2.jpg` – `4.jpg`

*Ispravan odgovor donosi 4 poena, negativnih bodova nema.*

---

### 1. Primenom Master teoreme odrediti asimptotsko ograničenje za T(n) = 7T(n/8) + n lg n

$a = 7$, $b = 8$, $f(n) = n\lg n$

$$\log_b a = \log_8 7 = 0{,}9358 \quad\Rightarrow\quad n^{\log_b a} = n^{0,9358}$$

Iz $7 = 8^x$ sledi $x \in (0,1)$, pa je $n^x < n \le n\lg n$ — $f(n)$ je **polinomijalno veća** → **slučaj 3**.

Uslov regularnosti: $7\cdot\tfrac{n}{8}\lg\tfrac{n}{8} = \tfrac{7}{8}n(\lg n - 3) \le \tfrac{7}{8}n\lg n$, sa $c = 7/8 < 1$. Ispunjen.

> $$T(n) = \Theta(n \lg n)$$

---

### 2. Koliki su rad, raspon i paralelizam procedure `Arithmetic-Sum(n)`?

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

> **Napomena:** ova procedura ima **trku do podataka** — sve iteracije upisuju u istu lokaciju `x`, a `x = x + 1` nije jedna instrukcija nego niz (učitaj, uvećaj, upiši).

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

### 6. Data je gramatika jezika J. Ispod svake rečenice napisati da li je deo jezika J i redosled primene produkcija. Da li je data gramatika kontekstno slobodna?

```
1. S -> x = P          3. P -> 2 - F          5. F -> x
2. S -> F = 2 - P / t  4. P -> F / t          6. F -> 2 - P
```

**`2 - x / t = 2 - t / t`**

> **Nije deo jezika J.** Rečenica počinje sa `2`, pa se mora primeniti produkcija 2, čija desna strana ima oblik `2 - P / t`. Da bi se dobilo `2 - t / t`, `P` bi morao izvesti samo `t` — a to nije moguće (`P -> 2 - F` ili `P -> F / t`).

**`x = 2 - x`**

> **Jeste.** Redosled: **1 → 3 → 5**
>
> `S` →₁ `x = P` →₃ `x = 2 - F` →₅ `x = 2 - x`

**`2 - 2 - x = 2 - 2 - x / t`**

> **Jeste.** Redosled: **2 → 6 → 3 → 5 → 3 → 5**

**Da li je data gramatika kontekstno slobodna?**

> **Jeste.**

Gramatika je kontekstno slobodna (Čomski, **tip 2**) ako svaka produkcija ima oblik `A -> γ`, gde `A` pripada skupu neterminala `N`, a `γ` pripada `(N ∪ T)*`. Ovde svih šest produkcija ima **tačno jedan neterminal sa leve strane** (`S`, `P` ili `F`), pa je uslov ispunjen.

---

### 7. Tokom asembliranja datog MIPS koda, koje su vrednosti simbola `val1` i `end`?

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

**Pazi na dve razlike u odnosu na uobičajenu verziju ovog zadatka:**

1. `arr1` ima **tri** vrednosti (`5 87 63`), ne četiri → zauzima 12 B, pa `arr2` počinje na 12, a `val1` na **16**.
2. Labela `end` stoji **iznad `lw`**, a ne iznad `jr $ra` → `end` pokazuje na treću instrukciju, dakle **8**.

Vrednost simbola je stanje brojača lokacija u trenutku kada asembler naiđe na labelu. Sekcije `.data` i `.text` imaju **odvojene** brojače, oba počinju od 0.

---

### 8. Za dati graf toka upravljanja zaokružiti tačne i precrtati netačne tvrdnje

| Čvor | `def` | `use` | `in` | `out` |
|---|---|---|---|---|
| 1 | a | — | c | a, c |
| 2 | b | a | a, c | b, c |
| 3 | c | c, b | b, c | b, c |
| 4 | a | b | b, c | a, c |
| 5 | — | a | a, c | a, c |
| 6 | — | c | c | — |

- ❌ a) Životni vek promenljive `a` i `b` se preklapa — nijedan `in`/`out` skup ne sadrži i `a` i `b`.
- ✅ **b) Promenljiva `c` je živa na izlazu iz čvora 2** — `out[2] = {b, c}`.
- ✅ **c) Promenljive `a` i `c` su u smetnji** — `c` je živa tamo gde se `a` definiše (čvorovi 1 i 4).
- ✅ **d) Promenljiva `c` je živa na ulazu u čvor 2** — `in[2] = {a, c}`.

---

### 9. Koje vrste zavisnosti postoje u grafu toka podataka? Kratko ih opisati i dati primere.

Primer:

```
1. X <- 5 - Z
2. Y <- X * 7
3. X <- 2
```

1. **RAW — čitanje posle pisanja** (*prava*, engl. true). Izlaz iz `I₁` je ulaz u `I₂`.
   *Primer:* `1 → 2` — instrukcija 1 upisuje `X`, instrukcija 2 ga čita.
2. **WAR — pisanje posle čitanja** (*antizavisnost*, engl. anti). Izlaz iz `I₂` je ulaz u `I₁`.
   *Primer:* `2 → 3` — instrukcija 2 čita `X`, instrukcija 3 ga upisuje.
3. **WAW — pisanje posle pisanja** (*izlazna*, engl. output). Izlaz iz `I₁` je izlaz i iz `I₂`.
   *Primer:* `1 → 3` — obe instrukcije upisuju `X`.

---

### 10. Navedi četiri osnovne funkcije punjača

1. **Alokacija** — dodela memorijskog prostora programima.
2. **Povezivanje** — određivanje vrednosti simboličkih referenci između relokatibilnih programa.
3. **Relokacija** — podešavanje svih adresno osetljivih lokacija na dodeljeni prostor.
4. **Punjenje** — fizički prenos mašinskih instrukcija i podataka u memoriju.
