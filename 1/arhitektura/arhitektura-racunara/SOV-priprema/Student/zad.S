# Student: miami lovich

#   Unesite namirnice: 
#   Jaja: P-26 C-2 F-22,Hleb: P-18 C-100 F-7,Meso: P-90 C-0 F-20,Kikiriki: P-13 
#   C-10 F-25,Pirinac: P-5 C-56 F-1
#   Ukupno kalorija: 1955
#   Protein: 152g
#   Ugljeni-hidrati: 168g
#   Masti: 75g
#   Izlazni kod: 0

.section .data
    poruka_unos: .ascii "Unesite namirnice:\n"
    unos_l = . - poruka_unos
    poruka_greska: .ascii "Pogresna oznaka makro-nutrijenta.\n"
    greska_l = . - poruka_greska
    poruka_kalorije: .ascii "Ukupno kalorija: "
    kalorije_l = . - poruka_kalorije
    poruka_p: .ascii "Protein: "
    protein_l = . - poruka_p
    poruka_c: .ascii "Ugljeni-hidrati: "
    carbo_l = . - poruka_c
    poruka_f: .ascii "Masti: "
    fats_l = . - poruka_f

    korisnicki_unos: .ascii "Jaja: P-26 C-2 F-22,Hleb: P-18 C-100 F-7,Meso: P-90 C-0 F-20,Kikiriki: P-13 C-10 F-25,Pirinac: P-5 C-56 F-1\0"

    MAX_LEN = 1000
    #   korisnicki_unos: .fill MAX_LEN,1,42
    ukupno_kalorija_ispis: .fill 5,1,42    
    ukupno_proteina_ispis: .fill 5,1,42
    ukupno_hidrata_ispis: .fill 5,1,42
    ukupno_masti_ispis: .fill 5,1,42

    ukupno_kalorija: .long 0
    ukupno_proteina: .long 0
    ukupno_hidrata: .long 0
    ukupno_masti: .long 0
    greska: .long 0
.section .text
.globl main

main:
    # ispis prvog stringa
    pushl $poruka_unos
    pushl $unos_l
    call ispis
    addl $8, %esp

    # unos svih namirnica
/*
    leal korisnicki_unos, %ecx
    movl $MAX_LEN, %edx
    movl $3, %eax
    movl $0, %ebx
    int $0x80

    movl %eax, %edi         # duzina unetog stringa
*/  
    leal korisnicki_unos, %ecx
    xorl %edx, %edx
    xorl %eax, %eax

namirnica:
    cmpb $'\n', (%ecx)
    je ispisi
    cmpb $'\0', (%ecx)
    je ispisi
    cmpb $':', (%ecx)
    je podaci_unos
    cmpb $'*', (%ecx)
    je ispisi
    incl %ecx
    jmp namirnica

    jmp kraj

neuspesno:
    movl $4, %eax
    movl $1, %ebx
    leal poruka_greska, %ecx
    movl $greska_l, %edx
    int $0x80

    movl $1, %eax
    movl $1, %ebx
    int $0x80

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80

podaci_unos:
    addl $2, %ecx

    cmpb $'P', (%ecx)
    jne neuspesno
    addl $2, %ecx
    
    xorl %edx, %edx
    movb $' ', %dl
    pushl %edx
    pushl %ecx
    call str_to_int
    addl $8, %esp

    movl $0, %edx
    movl $4, %ebx       # proteini idu *4 za kcal
    mull %ebx
    addl %eax, ukupno_proteina

    addl %eax, ukupno_kalorija

    incl %ecx
    movl $0, %eax

    cmpb $'C', (%ecx)
    jne neuspesno
    addl $2, %ecx
    
    xorl %edx, %edx
    movb $' ', %dl
    pushl %edx
    pushl %ecx
    call str_to_int
    addl $8, %esp

    movl $0, %edx
    movl $4, %ebx       # u-h idu *4 za kcal
    mull %ebx
    addl %eax, ukupno_hidrata

    addl %eax, ukupno_kalorija

    # isto str to int za fats

    incl %ecx
    movl $0, %eax

    cmpb $'F', (%ecx)
    jne neuspesno
    addl $2, %ecx
    
    xorl %edx, %edx
    movb $' ', %dl
    pushl %edx
    pushl %ecx
    call str_to_int
    addl $8, %esp

    movl $0, %edx
    movl $9, %ebx       # u-h idu *9 za kcal
    mull %ebx
    addl %eax, ukupno_masti

    addl %eax, ukupno_kalorija

    incl %ecx

    jmp namirnica

ispisi:
    # sad ispisujemo kalorije

    pushl $ukupno_kalorija_ispis
    pushl $ukupno_kalorija
    call int_to_str
    addl $8, %esp

    movl %eax, %edi
    incl %edi

    pushl $ukupno_kalorija_ispis
    pushl %edi
    call ispis
    addl $8, %esp

    # dalje, proteini


    pushl $ukupno_proteina_ispis
    pushl $ukupno_proteina
    call int_to_str
    addl $8, %esp

    movl %eax, %edi
    incl %edi

    pushl $ukupno_proteina_ispis
    pushl %edi
    call ispis
    addl $8, %esp


    pushl $ukupno_hidrata_ispis
    pushl $ukupno_hidrata
    call int_to_str
    addl $8, %esp

    movl %eax, %edi
    incl %edi

    pushl $ukupno_hidrata_ispis
    pushl %edi
    call ispis
    addl $8, %esp


    pushl $ukupno_masti_ispis
    pushl $ukupno_masti
    call int_to_str
    addl $8, %esp

    movl %eax, %edi
    incl %edi

    pushl $ukupno_masti_ispis
    pushl %edi
    call ispis
    addl $8, %esp

    jmp kraj


ispis:      # kad se poziva prvo pushujemo string pa onda duzinu
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %edx     # duzina ide u edx
    movl 12(%ebp), %ecx     # adresa ide u ecx

    movl $4, %eax
    movl $1, %ebx
    int $0x80

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret


int_to_str:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %esi      # adresa gde je $ukupno_xy
    movl (%esi), %eax
    movl $0, %edi           # brojac lokacija klk smo se pomerili
    movl 12(%ebp), %esi     # prvi argument, adresa gde treba sve da ispisujemo
    
    movl $10, %ecx

petlja2:

    xorl %edx, %edx
    divl %ecx

    addb $'0', %dl

    movb %dl, (%esi)
    incl %esi
    incl %edi

    cmpl $0, %eax
    jne petlja2
    
    movb $10, (%esi)
    decl %esi

    movl 12(%ebp), %ebx

obrni:
    cmpl %ebx, %esi
    jae nastavi2
    jmp ocisti_stek2

nastavi2:
    movb (%ebx), %dl
    movb (%esi), %dh
    movb %dh, (%ebx)
    movb %dl, (%esi)

    incl %ebx
    decl %esi

    jmp obrni
    
ocisti_stek2:
    movl %edi, %eax         # br koliko ima char
    popl %edi
    popl %esi
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret




str_to_int:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %ecx      # adresa gde je taj str
    #   u 12 ebp se nalazi space
    movl $10, %ebx      # baza
    xorl %eax, %eax

petlja:
    xorl %edx, %edx
    movb 12(%ebp), %dl
    cmpb (%ecx), %dl
    je ocisti_stek
    cmpb $'\n', (%ecx) # da li smo dosli do znaka za novi red
    je ocisti_stek
    cmpb $',', (%ecx)
    je ocisti_stek
    # cmpb $'\', (%ecx)
    # je ocisti_stek
    cmpb $0, (%ecx)
    je ocisti_stek
    #   cmpb $'0', (%ecx)
    #   jl ocisti_stek
    #   cmpb $'9', (%ecx)
    #   jg ocisti_stek

    mull %ebx
    movb (%ecx), %dl
    subb $'0', %dl
    addl %edx, %eax

    incl %ecx
    jmp petlja

ocisti_stek:
    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret