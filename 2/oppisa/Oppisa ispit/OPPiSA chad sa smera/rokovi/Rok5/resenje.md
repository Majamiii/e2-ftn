# Rok 5 — rešenja

*Strana `2.jpg` nedostaje. Numeracija pitanja na `3.jpg` nastavlja se sa 5 i 6, pa su verovatno i ona deo eliminacionog dela.*

## Eliminacioni deo — `1.jpg`, `3.jpg`

*Sve ispravno odgovoreno donosi 10 poena; jedna ili više grešaka donosi 0 poena na celom ispitu.*

---

### 1. Za date petlje sa nezavisnim iteracijama, zaokružiti tačne a precrtati netačne tvrdnje

```c
_Cilk_for (int i = 0; i < N; i++) {      for (int i = 0; i < N; i++) {
    foo(i);                                  _Cilk_spawn foo(i);
}                                        }
                                         _Cilk_sync;
```

- ✅ **a) Obe petlje daju isti rezultat.**
- ✅ **b) Obe petlje imaju jednako vreme izvršavanja na procesoru sa jednim jezgrom.**
- ❌ c) Obe petlje imaju isti raspon.

Serijalizacija obe petlje daje isti kod — običnu `for` petlju sa `n` poziva `foo`. Zato je i rezultat isti (a) i rad isti, pa i vreme na jednom jezgru (b).

Razlikuju se samo po **rasponu**: `_Cilk_for` je skraćeni zapis za rekurziju podeli-pa-vladaj → Θ(lg n); kod druge petlje je sama `for` petlja serijska → Θ(n).

---

### 2. Koliki je rad za svaku od petlji iz prethodnog pitanja? Kratko obrazložiti.

> $T_1 = \Theta(n)$ za **obe** petlje.

Rad je vreme izvršavanja na jednom procesoru. Serijalizacija obe petlje je obična `for` petlja sa `n` poziva funkcije `foo`.

---

### 3. Za dati graf toka upravljanja zaokružiti tačne i precrtati netačne tvrdnje

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

- ✅ **a) Promenljiva `a` je živa na ulazu u čvor 2** — čvor 2 koristi `a`.
- ❌ b) Promenljiva `b` se koristi u čvoru 2 — tu se `b` **definiše**.
- ✅ **c) Promenljiva `a` je živa na izlazu iz čvora 4** — naslednik (čvor 5) koristi `a`.
- ✅ **d) Promenljiva `c` se koristi u čvoru 3** — `c := c + b`.

---

### 4. Šta je tačno, a šta nije?

- ❌ a) Tabela simbola definiše razliku između mašinskih i pseudo instrukcija.
- ✅ **b) Popunjena tabela simbola je izlaz iz prvog prolaza asemblera.**
- ❌ c) Popunjena tabela simbola je ulaz u prvi prolaz asemblera (tj. ugrađena je u asembler).
- ❌ d) Tabela simbola pridružuje kod operacije broju koji predstavlja njegovu vrednost.

Razliku između mašinskih i pseudo operacija definiše **tabela koda operacije**. Prvi prolaz **popunjava** tabelu simbola, drugi je **koristi**. Tabela simbola pridružuje **simbol** broju koji predstavlja njegovu vrednost.

---

### 5. Koje grupe skupova mogu predstavljati formalnu gramatiku?

Formalna gramatika je četvorka `G(N, T, Σ, P)` gde je `Σ ∈ N`, a `N` i `T` moraju biti **disjunktni**.

| | Terminalni | Neterminalni | Početni | |
|---|---|---|---|---|
| 1 | a, b, c, +, /, d, z | x, y, a, b | y | ❌ |
| 2 | a, b, c, +, -, d | x, y, z | z | ✅ |
| 3 | a, b, c, +, -, d | x, y, z | a | ❌ |
| 4 | a, b, c, \*, + | \*, / | a | ❌ |

- **1)** `N ∩ T = {a, b} ≠ ∅` — skupovi nisu disjunktni.
- **2)** Disjunktni su, a `z ∈ N`. **Jedina ispravna.**
- **3)** Disjunktni jesu, ali `a ∉ N` — početni simbol mora biti neterminal.
- **4)** `N ∩ T = {*} ≠ ∅`, a uz to je i `a ∉ N`.

---

### 6. Dat je graf smetnji. Zaokružiti tačne, a precrtati netačne odgovore.

Brojevi u zagradi su **boje** (registri):

```
   A(1) --------- B(2)
     \           /
      \         /
       \       /
        C(3) ------- D(1)
```

Grane: `A–B`, `A–C`, `B–C`, `C–D`. Rangovi: `C` = 3, `A` = 2, `B` = 2, `D` = 1.

Najveća klika je trougao `{A, B, C}`, pa je potrebno **bar 3 boje**. Čvor `D` je susedan samo sa `C`, pa preuzima boju `A`. Tri boje su dovoljne.

- ❌ a) Za bojenje grafa je potrebno minimalno 4 boje — dovoljne su 3.
- ❌ b) Čvorovima `B` i `C` se može dodeliti isti registar — `B` i `C` su **susedni** (u smetnji), pa moraju dobiti različite registre.
- ✅ **c) Graf se može obojiti sa 3 boje**
- ❌ d) Čvorovima `B` i `D` se **mora** dodeliti isti registar — `B` i `D` nisu susedni, pa im se **može** dodeliti isti registar, ali ne mora. Ovde su čak dobili različite boje (2 i 1).

**Zamka je u rečima „može" i „mora".** Dva nesusedna čvora *mogu* deliti registar; dva susedna *ne mogu*. Nikada ne postoji obaveza da dva čvora dele registar.
