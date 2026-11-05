# Rok 4 — rešenja

*Ovaj rok sadrži samo eliminacioni deo (jedna strana). Identičan je roku `primer 1.pdf`.*

## Eliminacioni deo — `1.jpg`

*Sve ispravno odgovoreno donosi 10 poena; jedna ili više grešaka donosi 0 poena na celom ispitu.*

---

### 1. Ako je u vezi sa vremenom izvršavanja nekog algoritma napisano T(n) = Θ(n²), to znači:

- ❌ a) da je funkcija `T(n)` jednaka **funkciji** `Θ(n²)`
- ❌ b) da je funkcija `T(n)` asimptotski jednaka **funkciji** `Θ(n²)`
- ✅ **c) da funkcija `T(n)` pripada skupu funkcija `Θ(n²)`**
- ❌ d) da funkcija `Θ(n²)` pripada skupu funkcija `T(n)`

`Θ(n²)` je **skup funkcija**, a znak `=` u zapisu `T(n) = Θ(n²)` zapravo znači **pripadnost** tom skupu: `T(n) ∈ Θ(n²)`.

---

### 2. Na osnovu zakona rada i raspona možemo biti sigurni da je:

- ❌ a) vreme izvršavanja na P procesora uvek manje ili jednako srednjoj vrednosti rada i raspona
- ❌ b) vreme izvršavanja na P procesora uvek strogo manje od srednje vrednosti rada i raspona
- ✅ **c) vreme izvršavanja na P procesora uvek veće ili jednako rasponu**
- ❌ d) vreme izvršavanja na P procesora uvek veće ili jednako radu

- **Zakon rada:** $T_P \ge T_1/P$
- **Zakon raspona:** $T_P \ge T_\infty$

Zamka je opcija d): donja granica je **rad podeljen sa P**, a ne sam rad.

---

### 3. Priloženi kod podeliti horizontalnim linijama na osnovne blokove

Osnovni blok je niz susednih iskaza koji ne sadrži labelu (osim možda na početku) ni skok (osim možda na kraju). **Svaka labela počinje blok, svaki skok završava blok.** Obrnuto ne važi — blok ne mora počinjati labelom, dovoljno je da mu je prethodni iskaz skok.

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

> **4 osnovna bloka.** Treći blok je onaj koji se najlakše promaši: nema labelu, ali svejedno počinje novi blok jer mu prethodi skok.

---

### 4. Koliko u gramatici ima produkcija? Zaokružiti ih.

```
S -> x = P            (1)
P -> 2 - F            (2)
F -> x                (3)
S -> F = 2 - P / t    (4)
P -> F / t            (5)
F -> 2 - P            (6)
```

> **6 produkcija** — zaokružuje se svih šest.

Nezavršni simboli `S`, `P` i `F` javljaju se po dva puta sa leve strane, ali to su i dalje šest odvojenih produkcija. Ko ih spoji, odgovoriće 3 — i pogrešiti.

---

### 5. Dati su grafovi smetnji. Ako u arhitekturi imamo 3 registra, kod kojih grafova se mora uraditi prelivanje?

**Kriterijum.** Čvor je *značajan* ako mu je rang ≥ K (ovde K = 3).

- **UPROSTI** — čvor koji nije značajan (rang < 3) izvlači se iz grafa i gura na stek.
- **PRELIJ** — primenjuje se kad su *svi* preostali čvorovi značajni. Tada je prelivanje nužno.

Dakle: prelivanje treba tačno onda kad se UPROSTI zaglavi.

| Graf | Rangovi | UPROSTI | Prelivanje |
|---|---|---|---|
| a) | 4, 3, 2, 2, 1 | isprazni se | ❌ ne |
| b) | 3, 2, 2, 1 | isprazni se | ❌ ne |
| **v)** | 4, 4, 3, 3, 1, 1 | **zaglavi se** | ✅ **da** |
| g) | 5, 3, 2, 2, 1, 1 | isprazni se | ❌ ne |

**Zašto samo v).** Posle uklanjanja dva čvora ranga 1, u grafu v) ostaju četiri čvora, svi ranga 3 — oni čine **K₄** (potpun graf na 4 čvora). K₄ zahteva 4 boje, a imamo 3 registra.

Kod grafova a), b) i g) najveća klika je trougao, pa su tri boje dovoljne.

> **Odgovor: samo graf v)**

**Napomena:** na skeniranom roku su zaokruženi a) i g), a precrtano v) — **to je pogrešno**. Provera: graf v) je jedini koji je morao biti obojen sa četiri boje.

---

### 6. Dati su kodovi dva različita programska segmenta. Zaokružite instrukcije koje predstavljaju adresno osetljive lokacije.

Adresno osetljiva je svaka instrukcija koja **referiše simbol (labelu)** — takvu lokaciju punjač mora podesiti pri relokaciji. Za svaku takvu lokaciju RLD katalog pamti **naziv simbola, vrstu instrukcije i položaj instrukcije**.

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

**Pazi:** kriterijum nije „apsolutno vs. PC-relativno adresiranje". Predavanje izričito navodi `beq(R2, Label, R30)` kao adresno osetljivu lokaciju, isto kao `jmp(Label)`.
