.section .data
    poruka_unos: .ascii "Unesite namirnice:\n"
    poruka_unos_len  = .- poruka_unos
    poruka_greska: .ascii "Pogresna oznaka makro-nutrijenta.\n"
    poruka_greska_len  = .- poruka_greska
    poruka_kalorije: .ascii "Ukupno kalorija: "
    poruka_kalorije_len  = .- poruka_kalorije
    poruka_p: .ascii "Protein: "
    poruka_p_len  = .- poruka_p
    poruka_c: .ascii "Ugljenih-hidrati: "
    poruka_c_len  = .- poruka_c
    poruka_f: .ascii "Masti: "
    poruka_f_len  = .- poruka_f

    MAX_LEN = 1000
    korisnicki_unos: .fill MAX_LEN,1,42
    ukupno_kalorija_ispis: .fill 5,1,42    
    ukupno_proteina_ispis: .fill 5,1,42   # 3 cifre, g, enter
    ukupno_hidrata_ispis: .fill 5,1,42
    ukupno_masti_ispis: .fill 5,1,42

    ukupno_kalorija: .long 0
    ukupno_proteina: .long 0
    ukupno_hidrata: .long 0
    ukupno_masti: .long 0
    greska: .long 0
.section .text
.global main
main:
    movl $4, %eax
    movl $1, %ebx
    movl $poruka_unos, %ecx
    movl $poruka_unos_len, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    movl $korisnicki_unos, %ecx
    movl $MAX_LEN, %edx
    int $0x80

parsiraj_namirnicu:
    cmpb $'\n', (%ecx)
    je izracunaj_kalorije
    cmpb $':', (%ecx)   # nakon naziva namirnice ide ':', odatle na dalje je odredjen oblik
    je izvuci_nutrijente    
    incl %ecx
    jmp parsiraj_namirnicu
izvuci_nutrijente:
    addl $2, %ecx   # space, P
    cmpb $'P', (%ecx)
    jne greska_ispis
    addl $2, %ecx   # -, na prvu cifru

    xorl %edx, %edx
    movb $' ', %dl  # prvi separator je space
    pushl %edx
    pushl %ecx
    call str_to_int
    addl $8, %esp
    addl %eax, ukupno_proteina

    incl %ecx # space, na C 
    cmpb $'C', (%ecx)
    jne greska_ispis
    addl $2, %ecx   # -, na prvu cifru

    xorl %edx, %edx
    movb $' ', %dl  # drugi separator je space
    pushl %edx
    pushl %ecx
    call str_to_int
    addl $8, %esp
    addl %eax, ukupno_hidrata

    incl %ecx # space, na F 
    cmpb $'F', (%ecx)
    jne greska_ispis
    addl $2, %ecx   # -, na prvu cifru
    
    xorl %edx, %edx
    movb $',', %dl  # treci separator je zarez
    pushl %edx
    pushl %ecx
    call str_to_int
    addl $8, %esp
    addl %eax, ukupno_masti

    jmp parsiraj_namirnicu
izracunaj_kalorije:
    movl ukupno_proteina, %eax
    addl ukupno_hidrata, %eax
    movl $4, %ecx   # broj hidrata i proteina se mnozi za 4 za broj kalorija
    mull %ecx
    movl %eax, ukupno_kalorija

    movl ukupno_masti, %eax
    movl $9, %ecx
    mull %ecx
    addl ukupno_kalorija, %eax  # ukupan broj kalorija je u %eax

    movl $ukupno_kalorija_ispis, %ecx
    pushl %ecx
    pushl %eax
    call int_to_str
    addl $8, %ebp
    movl %eax, %esi # duzina buffera za ispis

    movl $4, %eax
    movl $1, %ebx
    movl $poruka_kalorije, %ecx
    movl $poruka_kalorije_len, %edx
    int $0x80 

    movl $4, %eax
    movl $1, %ebx
    movl $ukupno_kalorija_ispis, %ecx
    movl %esi, %edx
    int $0x80
    
    # void formatiraj_ispis(char *poruka_za_ispis, int kolicina, char *naziv_nutrijenta, int duzina_naziva)
    # poruka_za_ispis - poruka u kojoj je neophodno dodati g
    # kolicina - kolicina nutrijenta koju je potrebno konvertovati
    # naziv_nutrijenta - naziv nutrijenta koji se ispisuje, npr. "Protein: "
    # duzina_naziva - duzina naziva nutrijenta koji je poslan
    pushl $poruka_p_len
    pushl $poruka_p
    pushl ukupno_proteina
    pushl $ukupno_proteina_ispis
    call formatiraj_ispis
    addl $20, %esp

    pushl $poruka_c_len
    pushl $poruka_c
    pushl ukupno_hidrata
    pushl $ukupno_hidrata_ispis
    call formatiraj_ispis
    addl $20, %esp

    pushl $poruka_f_len
    pushl $poruka_f
    pushl ukupno_masti
    pushl $ukupno_masti_ispis
    call formatiraj_ispis
    addl $20, %esp
    
    jmp kraj
greska_ispis:
    incl greska

    movl $4, %eax
    movl $1, %ebx
    movl $poruka_greska, %ecx
    movl $poruka_greska_len, %edx
    int $0x80
kraj:
    movl $1, %eax
    movl greska, %ebx
    int $0x80
/*
NAPOMENA ZA POTPROGRAME U ASEMBLERU KADA SE NE ZOVU IZ C PROGRAMA:
1) Nije neophodno pushovati registre, svi su dostupni
2) Mogu se i dalje pushovati registri, ako se neki registar pushuje i popuje,
   njegova vrednost pre i nakon funkcije ce ostati *nepromenjena*, u suprotnom
   po povratnu iz funkcije zadrzava vrednost koju je imao u trenutku povratka
*/

# ------- POTPROGRAMI -------
# void int_to_str(int num, char *str)
int_to_str: 
    pushl %ebp 
    movl %esp, %ebp
    
    subl $4, %esp
    movl $0, -4(%ebp)

    pushl %esi
    pushl %edi

    movl 8(%ebp), %eax
    movl 12(%ebp), %esi
    movl $10, %ecx 

cifra:
    xorl %edx, %edx
    divl %ecx

    addb $'0', %dl
    movb %dl, (%esi)
    incl %esi
    incl -4(%ebp)

    andl %eax, %eax
    jnz cifra

    movb $10, (%esi)
    decl %esi
    movl 12(%ebp), %edi
obrni: 
    cmpl %esi, %edi
    jae ispis_f1

    movb (%esi), %al
    movb (%edi), %ah
    movb %ah, (%esi)
    movb %al, (%edi)

    incl %edi
    decl %esi
    jmp obrni
ispis_f1:
    movl -4(%ebp), %eax
    incl %eax

    popl %edi
    popl %esi
    movl %ebp, %esp
    popl %ebp
    ret

# int str_to_int(char *str, char separator)
str_to_int:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx

    movl 8(%ebp), %ecx
    movl $10, %ebx

    xorl %eax, %eax
    xorl %edx, %edx
slovo: 
    movl 12(%ebp), %edx
    cmpb %dl, (%ecx)   # da li smo dosli do separatora
    je ispis_f2
    cmpb $'\n', (%ecx) # da li smo dosli do znaka za novi red
    je ispis_f2

    mull %ebx
    movb (%ecx), %dl
    subb $'0', %dl
    addl %edx, %eax

    incl %ecx
    jmp slovo
ispis_f2:
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret

# void formatiraj_ispis(char *poruka_za_ispis, int kolicina, char *naziv_nutrijenta, int duzina_naziva)
formatiraj_ispis:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %ecx
    movl 12(%ebp), %eax

    pushl %ecx
    pushl %eax
    call int_to_str
    addl $8, %esp

    movl 8(%ebp), %ecx
    addl %eax, %ecx
    decl %ecx   # vracamo se sa duzine na indeks
    movb $'g', (%ecx)   # ubacujemo g na mesto entera
    incl %ecx   # idemo na naredni karakter
    movb $'\n', (%ecx)  # ubacujemo enter na kraj
    incl %eax   # dodali smo g, duzina se povecava za 1
    movl %eax, %esi # cuvamo duzinu buffera

    movl $4, %eax
    movl $1, %ebx
    movl 16(%ebp), %ecx
    movl 20(%ebp), %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    movl 8(%ebp), %ecx
    movl %esi, %edx
    int $0x80 

    movl %ebp, %esp
    popl %ebp
    ret