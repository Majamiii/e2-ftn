# Rok 8 — rešenja

*Ovaj rok sadrži samo eliminacioni deo (jedna strana). Pitanja 1–5 su identična roku `Rok7`.*

## Eliminacioni deo — `1.jpg`

*Sve ispravno odgovoreno donosi 10 poena; jedna ili više grešaka donosi 0 poena na celom ispitu.*

---

### 1. Tehnike definisanja novih lingvističkih nivoa su:

- ✅ **a) Proširenje** — nove procedure koriste primitive osnovnog sistema
- ✅ **b) Prevođenje** (kompajliranje) — sa novog jezika na jezik osnovnog sistema
- ⚠️ c) Kombinacija — *vidi napomenu*
- ❌ d) Dodavanje — ne postoji takva tehnika

Predavanje pod naslovom **„Tehnike za definisanje novih lingvističkih nivoa"** nabraja tačno **tri**: proširenje, prevođenje i **interpretacija** (kod interpretacije su faze prevođenja i izvršenja vremenski zavisne).

> **⚠️ Nesigurno: opcija c).** „Kombinacija" nije među te tri tehnike. Ali drugi slajd kaže: *„Programi definišu novi lingvistički nivo proširivanjem, prevođenjem, interpretacijom **ili nekom kombinacijom** ovih tehnika."*
>
> Ako se pitanje čita kao spisak tehnika → tačno je samo a) i b). Ako se čita kao „načini definisanja nivoa" → tačno je i c). Proveriti sa profesorom.

---

### 2. Data je gramatika. Navedi terminalne i neterminalne simbole.

```
S -> get E from S      L -> quit
S -> begin S L         L -> ; S L
S -> print E END       E -> num EQ num
```

> **Neterminalni (3):** `S`, `L`, `E`
>
> **Terminalni (9):** `get`, `from`, `begin`, `print`, `END`, `quit`, `;`, `num`, `EQ`

---

### 3. Koje od ovih instrukcija međureprezentacije mogu biti u unutrašnjosti osnovnog bloka?

- ✅ **a) Pristup memoriji**
- ❌ b) Labela
- ❌ c) Uslovni skok
- ❌ d) Bezuslovni skok

Osnovni blok **ne sadrži labelu (osim možda na samom početku) ni skok (osim možda na samom kraju)**. Unutrašnjost je sve osim prve i poslednje instrukcije, pa u njoj ne sme biti ni labele ni skoka. Pristup memoriji ne prenosi upravljanje, pa sme biti bilo gde.

---

### 4. Od koje do koje linije traje životni vek promenljive `a`?

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

Promenljiva je živa od svoje **definicije** (linija 2) do **poslednje upotrebe** (linija 6, `return z - a`).

**Pazi na liniju 5.** Tamo se `a` ne pominje, ali je i dalje živa — postoji putanja od te tačke do upotrebe u liniji 6 koja ne prolazi kroz nijednu novu definiciju `a`.

**Napomena:** rukom upisan odgovor na roku nije čitljiv na skenu; deluje kao `7`. Linija 7 je zatvorena vitičasta zagrada, u njoj nema nikakve upotrebe `a`, pa bi to bilo netačno. Tačan odgovor je **6**.

---

### 5. Obojiti dati graf sa 3 boje

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

**Bojenje:** `D` = 1, `B` = 2, `A` = 3, `C` = 3, `E` = 2

Najveća klika je trougao (`A-B-D` odnosno `B-C-D`), pa su tri boje i nužne i dovoljne. Nema `K₄` — grane `A–C` nema.

**Bojenje nije jedinstveno.** Čvoru `E` (rang 1, jedini sused `D` sa bojom 1) može se dodeliti **2 ili 3**. Čvor `C` je jedinstven: susedi su mu `B`(2) i `D`(1), pa mora dobiti 3.

---

### 6. Zaokružite instrukcije koje predstavljaju adresno osetljive lokacije

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

Adresno osetljiva je svaka instrukcija koja **referiše simbol (labelu)** — takvu lokaciju punjač mora podesiti pri relokaciji. RLD katalog za svaku pamti **naziv simbola, vrstu instrukcije i položaj instrukcije**.

**Bitno:** obe labele (`lab1`, `lab2`) su **lokalne**, u istom segmentu — i svejedno su instrukcije koje ih referišu adresno osetljive. Kriterijum nije „apsolutno vs. PC-relativno adresiranje", nego prosto: **da li instrukcija referiše simbol**.

**Napomena:** na skeniranom roku su zaokružene `la`, `lw`, `li` i `li` — **to je pogrešno**. Nijedna od njih ne referiše simbol: `7`, `5` i `-5` su konstante, a `lw` adresira preko registra `$t0`.
