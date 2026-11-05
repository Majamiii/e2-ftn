# Rok 3 — rešenja

## Eliminacioni deo — `1.jpg`

*Sve ispravno odgovoreno donosi 10 poena; jedna ili više grešaka donosi 0 poena na celom ispitu.*

---

### 1. Napisati telo funkcije `foo` tako da njeno vreme izvršavanja na jednom jezgru ima asimptotski usku granicu Θ(n)

```cpp
void foo(int n) {
    for (int i = 0; i < n; ++i)
        cout << "foo" << endl;
}
```

Petlja se izvršava tačno `n` puta, telo je Θ(1) → Θ(n).

---

### 2. Ako je napisano T(n) = Θ(n²), to znači:

- ❌ a) da je funkcija `T(n)` jednaka **funkciji** `Θ(n²)`
- ✅ **b) da funkcija `T(n)` pripada skupu funkcija `Θ(n²)`**
- ❌ c) da funkcija `Θ(n²)` pripada **skupu funkcija** `T(n)`

`Θ(n²)` je **skup funkcija**, a znak `=` u zapisu `T(n) = Θ(n²)` zapravo znači **pripadnost** tom skupu.

---

### 3. Šta je tačno, a šta nije?

- ❌ a) Tabela simbola definiše razliku između mašinskih i pseudo instrukcija.
- ✅ **b) Popunjena tabela simbola je izlaz iz prvog prolaza asemblera.**
- ❌ c) Popunjena tabela simbola je ulaz u prvi prolaz asemblera (tj. ugrađena je u asembler).
- ❌ d) Tabela simbola pridružuje kod operacije broju koji predstavlja njegovu vrednost.

Razliku između mašinskih i pseudo operacija definiše **tabela koda operacije**. Prvi prolaz **popunjava** tabelu simbola, drugi je **koristi**. Tabela simbola pridružuje **simbol** broju koji predstavlja njegovu vrednost.

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

### 5. Obojiti dati graf sa najmanjim mogućim brojem boja

Graf ima 6 čvorova i 7 ivica. U čvorovima su **slovo i boja**:

```
   A(1)-------B(2)           C(1)
    |  \        |  \          /
    |    \      |    \      /
    |      \    |      \  /
    |        \  |        X
    |          \|      /   \
   D(2)-------E(3)          F(1)
```

Grane: `A–B`, `A–D`, `A–E`, `B–E`, `B–F`, `C–E`, `D–E`

Rangovi: `E` = 4, `A` = 3, `B` = 3, `D` = 2, `C` = 1, `F` = 1

Najveća klika je trougao `{A, B, E}` (ili `{A, D, E}`), pa je potrebno **bar 3 boje**. Grane `B–D` **nema**, pa nema `K₄` i tri boje su dovoljne.

> **Odgovor: 3 boje**

---

## Glavni deo — `2.jpg` – `3.jpg`

*Ispravan odgovor donosi 4 poena, negativnih bodova nema.*

---

### 1. Primenom Master teoreme odrediti asimptotsko ograničenje za T(n) = 3T(n/4) + n lg n

$a = 3$, $b = 4$, $f(n) = n\lg n$

$$\log_b a = \log_4 3 = 0{,}792 \quad\Rightarrow\quad n^{\log_b a} = n^{0,792}$$

Iz $3 = 4^x$ sledi $x \in (0,1)$, pa je $n^x < n \le n\lg n$ — $f(n)$ je **polinomijalno veća** → **slučaj 3**.

Uslov regularnosti: $3\cdot\tfrac{n}{4}\lg\tfrac{n}{4} = \tfrac{3}{4}n(\lg n - 2) \le \tfrac{3}{4}n\lg n$, sa $c = 3/4 < 1$. Ispunjen.

> $$T(n) = \Theta(f(n)) = \Theta(n \lg n)$$

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

**Raspon** — paralelna petlja se realizuje kao rekurzija podeli-pa-vladaj, pa je njena dubina logaritamska. Za paralelnu petlju sa `n` iteracija u kojoj `i`-ta iteracija ima raspon $iter_\infty(i)$:

$$T_\infty(n) = \Theta(\lg n) + \max_{1 \le i \le n} iter_\infty(i)$$

Telo petlje (`x = x + 1`) je $\Theta(1)$, pa je

$$T_\infty(n) = \Theta(\lg n)$$

**Paralelizam:**

$$\frac{T_1(n)}{T_\infty(n)} = \Theta\!\left(\frac{n}{\lg n}\right)$$

> **Napomena:** ova procedura ima **trku do podataka** — sve iteracije upisuju u istu lokaciju `x`, a `x = x + 1` nije jedna instrukcija nego niz (učitaj, uvećaj, upiši). Rezultat zato nije determinističan, ali rad, raspon i paralelizam se računaju iz strukture grafa računanja.

---

### 3. Kako se računa raspon grafa T∞(A ∪ B) ako su dva podgrafa povezana na sledeća dva načina?

**a) Redno** (`A → B`):

$$T_\infty(A \cup B) = T_\infty(A) + T_\infty(B)$$

**b) Paralelno** (grananje na `A` i `B`, pa spajanje):

$$T_\infty(A \cup B) = \max\bigl(T_\infty(A),\ T_\infty(B)\bigr)$$

Analiza raspona je analiza **kritičnog puta**. Kod redne veze putevi se nadovezuju, pa se rasponi sabiraju; kod paralelne veze kritični put ide kroz duži od dva podgrafa, pa se uzima maksimum.

---

### 4. Navesti osnovne module asemblera i skicirati odnos među njima

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

Oba prolaza koriste modul za izračunavanje izraza i modul za konverziju konstanti.

---

### 5. Data je gramatika jezika J. Ispod svake rečenice napisati da li je deo jezika J i redosled primene produkcija

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

---

### 6. Poželjne osobine međukoda su

- **a)** Pogodan je za davanje značenja čvorovima stabla sintaksne analize
- **b)** Pogodan je za prevođenje u mašinski jezik odredišnog procesora
- **c)** Čvorovi stabla međukoda treba da imaju jasna i jednostavna značenja
  *(radi lake specifikacije i realizacije optimizacionih transformacija)*

---

### 7. Koje instrukcije mogu biti u unutrašnjosti osnovnog bloka?

- ✅ **a) Pristup memoriji**
- ✅ **b) Poziv potprograma**
- ❌ c) Uslovni skok
- ❌ d) Bezuslovni skok
- ✅ **e) MOVE instrukcija**

Blok završava **samo uslovni ili bezuslovni skok** — sve ostale instrukcije su beznačajne za tok upravljanja. Poziv potprograma nije skok u tom smislu: upravljanje se vraća na sledeću instrukciju, pa niz ne puca.

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

- ❌ a) Životni vek promenljive `a` i `b` se preklapa — nijedan skup ne sadrži i `a` i `b`.
- ✅ **b) Promenljiva `c` je živa na izlazu iz čvora 2** — `out[2] = {b, c}`.
- ✅ **c) Promenljive `a` i `c` su u smetnji** — `c` je živa tamo gde se `a` definiše (čvorovi 1 i 4).
- ✅ **d) Promenljiva `c` je živa na ulazu u čvor 2** — `in[2] = {a, c}`.
