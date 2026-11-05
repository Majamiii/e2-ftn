# Rok 6 — rešenja

*Ovaj rok sadrži samo eliminacioni deo (jedna strana).*

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

### 2. Kolika je asimptotski uska granica rada za funkciju `foo` iz prethodnog pitanja?

> $T_1 = \Theta(n)$

Rad je vreme izvršavanja na jednom procesoru, a ono za `foo` ima asimptotski usku granicu Θ(n).

---

### 3. Za dati kod nacrtati graf toka upravljanja i na njemu obeležiti osnovne blokove

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

`B1` se završava uslovnim skokom (`x > 5`), a `B4` počinje jer je tačka spajanja obe grane.

---

### 4. Koliko u gramatici ima produkcija? Zaokružiti ih.

```
S -> x = P            P -> 2 - F            F -> x
S -> F = 2 - P / t    P -> F / t            F -> 2 - P
```

> **6 produkcija** — zaokružuje se svih šest.

Nezavršni simboli `S`, `P` i `F` javljaju se po dva puta sa leve strane, ali to su i dalje šest odvojenih produkcija.

---

### 5. Dat je graf smetnji za operande kojima se dodeljuju registri opšte namene. Šta su tačne tvrdnje?

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

Grane: `a–b`, `a–c`, `b–c`, `b–y`, `x–y`

*(Na samom roku su grane `a–c` i `b–y` nacrtane tako da se seku, ali presek nije čvor. Ovde je isti graf nacrtan bez preseka.)*

Rangovi: `b` = 3, `a` = 2, `c` = 2, `y` = 2, `x` = 1

Najveća klika je trougao `{a, b, c}`, pa su potrebne **3 boje**. Bojenje: `a`=1, `b`=2, `c`=3, `y`=1, `x`=2.

- ❌ a) Čvor `x` je u smetnji sa čvorom `b`, preko čvora `y`. — **Smetnja nije tranzitivna.** Grane `x–b` nema, pa oni nisu u smetnji, bez obzira što oba imaju vezu sa `y`.
- ❌ b) Čvorovima `y` i `a` **ne smemo** dodeliti isti registar. — `y` i `a` **nisu susedni**, pa im **smemo** dodeliti isti registar. U bojenju gore obojeni su istom bojom (1).
- ✅ **c) Čvor `a` je u smetnji sa čvorom `c`.** — grana `a–c` postoji.
- ❌ d) Čvorovima `a` i `b` **možemo** dodeliti isti registar. — `a` i `b` **jesu susedni**, dakle u smetnji, pa im **ne možemo** dodeliti isti registar.

> **Odgovor: tačna je samo tvrdnja c).**

**Napomena:** na skeniranom roku su zaokružene b) i g), a precrtana v) — **to je pogrešno**. Grana `a–c` jasno postoji (ona koja preseca granu `b–y`), a grana `a–b` takođe, dok grane `a–y` nema.

---

### 6. Dopuniti instrukciju koja nedostaje u „Punjenju 3"

```
cmpeqc(R1, 100, R2)
beq(R2, Label, R30)
addc(R1, 1, R0)
```

| | Punjenje 1 | Punjenje 2 | Punjenje 3 |
|---|---|---|---|
| **Adresa** | 0x0000 | 0x0051 | 0x0113 |
| `cmpeqc` | `0xd041 0064` | `0xd041 0064` | `0xd041 0064` |
| `beq` | `0x73c2 0005` | `0x73c2 0056` | `0x73c2 ????` |
| `addc` | `0xc001 0001` | `0xc001 0001` | `0xc001 0001` |

**Rezonovanje.** `cmpeqc` i `addc` imaju **konstantne** operande (`0x0064` = 100 i `0x0001` = 1) — oni se ne menjaju ni u jednom punjenju.

`beq(R2, Label, R30)` referiše **simbol `Label`**, pa je to **adresno osetljiva lokacija**. Njen operand je apsolutna adresa i punjač ga pri relokaciji podešava dodavanjem početne adrese segmenta.

Iz Punjenja 1 (početna adresa `0x0000`) čita se da je `Label` na pomeraju **`0x0005`** od početka segmenta.

Provera na Punjenju 2: $0x0051 + 0x0005 = 0x0056$ ✓

Punjenje 3, početna adresa `0x0113`:

$$0x0113 + 0x0005 = 0x0118$$

> **Odgovor: `0x73c2 0118`**
