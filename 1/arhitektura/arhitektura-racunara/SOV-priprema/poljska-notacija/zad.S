# autor: Maja Milović RA69/2024
.section .data
    izraz_maks_d = 101
    rezultat_str: .fill izraz_maks_d    # ovde smestiti stringovnu reprezentaciju rezultata i ne menjati naziv promenljive

    izraz_str: .fill 101, 1, 42

    int_proba: .long 19
    str_proba: .ascii "20 1   \n\0"

    rezultat: .long 0

    # NE MENJATI TEKST PORUKA!
    poruka_ulaz: .ascii "Unesite izraz: \0"
    ulaz = . - poruka_ulaz
    poruka_rez: .ascii "Rezultat je: \0"
    poruka_rez_duzina = . - poruka_rez
    poruka_greska1: .ascii "Unet je prazan izraz!\n\0"
    greska1 = . - poruka_greska1
    poruka_greska2: .ascii "U nekoj od ulaznih vrednosti postoji cifra koja ne pripada brojnoj osnovi!\n\0"
    greska2 = . - poruka_greska2
    poruka_greska3: .ascii "Doslo je do prekoracenja prilikom konverzije nekog od operanada!\n\0"
    greska3 = . - poruka_greska3
    poruka_greska4: .ascii "Doslo je do prekoracenja prilikom sabiranja!\n\0"
    greska4 = . - poruka_greska4
.section .text
.globl main


main:
    movl $4, %eax
    movl $1, %ebx
    leal poruka_ulaz, %ecx
    movl $ulaz, %edx
    int $0x80

    # unos izraza
    movl $3, %eax
    movl $0, %ebx
    leal izraz_str, %ecx
    movl $izraz_maks_d, %edx
    int $0x80

    movl $0, %esi

    leal izraz_str, %ecx
    
    movb (%ecx), %dl
    cmpb $'\0', %dl
    je prazan_izraz
    cmpb $0, %dl
    je prazan_izraz
    cmpb $'\n', %dl
    je prazan_izraz


do_broja:
    movb (%ecx), %dl
    cmpb $'\0', %dl
    je ispis
    cmpb $0, %dl
    je ispis
    cmpb $'\n', %dl
    je ispis

    cmpb $'0', %dl
    jae druga_provera

    cmpb $' ', %dl
    jne cetvrta_provera

    incl %ecx
    jmp do_broja

cetvrta_provera:
    cmpb $'+', %dl
    jne nije_dekadni
    incl %ecx
    jmp do_broja


druga_provera:
    cmpb $'9',%dl
    jbe nastavak

    cmpb $'+', %dl
    jne nije_dekadni

    incl %ecx
    jmp do_broja

nastavak:
    pushl %ecx
    call str_to_int
    addl $4, %esp

    cmpl $3, %eax
    je konverzija_prekoracenje
    cmpl $4, %eax
    je sabiranje_prekoracenje

    #   incl %ecx

    jmp do_broja



ispis:
# poruka za kraj:
    movl $4, %eax
    movl $1, %ebx
    leal poruka_rez, %ecx
    movl $poruka_rez_duzina, %edx
    int $0x80

# pretvaranje rez u str
    movl %esi, %edx
    leal rezultat_str, %ecx
    pushl %edx      # prvo se pushuje broj pa onda string gde se smesta
    pushl %ecx
    call int_to_str
    addl $8, %esp

    movl %eax, %edx

    # ispis rezultata
    movl $4, %eax
    movl $1, %ebx
    leal rezultat_str, %ecx
    int $0x80
    
    movl $0, %ebx

    jmp dobar_kraj

prazan_izraz:
    movl $4, %eax
    movl $1, %ebx
    leal poruka_greska1, %ecx
    movl $greska1, %edx
    int $0x80
    movl $1, %ebx
    jmp kraj

nije_dekadni:
    movl $4, %eax
    movl $1, %ebx
    leal poruka_greska2, %ecx
    movl $greska2, %edx
    int $0x80
    movl $2, %ebx
    jmp kraj

konverzija_prekoracenje:
    movl $4, %eax
    movl $1, %ebx
    leal poruka_greska3, %ecx
    movl $greska3, %edx
    int $0x80
    movl $3, %ebx
    jmp kraj

sabiranje_prekoracenje:
    movl $4, %eax
    movl $1, %ebx
    leal poruka_greska4, %ecx
    movl $greska4, %edx
    int $0x80
    movl $4, %ebx
    jmp kraj

dobar_kraj:
    movl $0, %ebx

kraj:
    movl $1, %eax
    int $0x80





int_to_str:
    # prvo se pushovao broj pa onda gde se smesta
    # dakle na 8 je loc stringa a na 12 ta vrednost
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %ecx
    movl 12 (%ebp), %eax

    movl $10, %ebx      # baza
    movl $0, %edi       # brojac koliko ima karaktera

petlja:
    xorl %edx, %edx
    divl %ebx
    addb $'0', %dl
    movb %dl, (%ecx)
    incl %ecx

    incl %edi
    
    cmpl $0, %eax
    jg petlja

obrni_pocetak:
    movb $'\n', %dl
    movb %dl, (%ecx)
    decl %ecx
    movl 8(%ebp), %ebx

obrni:
    cmpl %ebx, %ecx
    jbe ocisti_stek

    movb (%ebx), %dh
    movb (%ecx), %dl
    movb %dl, (%ebx)
    movb %dh, (%ecx)

    decl %ecx
    incl %ebx

    jmp obrni

ocisti_stek:
    incl %edi
    movl %edi, %eax
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
    pushl %edi

    movl 8(%ebp), %ecx      # adresa stringa kog moramo da konvertujemo
    movl $0, %eax
    movl $10, %ebx

    # u esi cuvamo tu vrednost

petlja_to_int:

    xorl %edx, %edx
    mull %ebx

    cmpl $0, %edx
    jne prekoracenje_konverzija
    xorl %edx, %edx

    movb (%ecx), %dl
    cmpb $'0', %dl
    jb kraj_2
    cmpb $'9', %dl
    ja kraj_2
    # konvertujemo samo fr brojeve


    incl %ecx

    subb $'0', %dl
    addl %edx, %eax
    #   jc prekoracenje_konverzija

    movb (%ecx), %dl
    cmpb $'0', %dl
    jb kraj_2
    cmpb $'9', %dl
    ja kraj_2

    jmp petlja_to_int

kraj_2:
    #   xorl %edx, %edx
    #   divl %ebx
    addl %eax, %esi
    jc prekoracenje_sabiranje
    movl $0, %eax

    popl %edi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret

prekoracenje_konverzija:
    movl $3, %eax

    movl $0, %esi

    popl %edi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret


prekoracenje_sabiranje:
    movl $4, %eax

    movl $0, %esi

    popl %edi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret

