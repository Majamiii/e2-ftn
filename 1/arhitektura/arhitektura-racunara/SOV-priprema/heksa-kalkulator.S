#   Realizovati asemblerski program za kalkulator neoznačenih 64-bitnih brojeva sa
#   3 osnovne logičke operacije. Unos i ispis treba da budu u heksadecimalnom
#   brojnom sistemu, pri čemu su na ulazu dozvoljena i velika i mala slova, dok na
#   izlazu treba da budu samo velika slova. Program treba da omogući unos prvog
#   broja, unos logičke operacije i unos drugog broja i da na ekranu ispiše rezultat ili
#   poruku o grešci ukoliko dođe do greške (pogrešan unos). Ulaz treba da je oblika:
#   heksadecimalni_broj
#   operacija
#   heksadecimalni_broj
#   pri čemu između operacije i heksadecimalnog broja može postojati jedan ili više
#   razmaka. Dozvoljene operacje su
#   &
#   (and),
#   |
#   (or) i
#   ^
#   (xor). Primeri rada sa
#   programom:
#   Unesite izraz: A41f ^ F123
#   Rezultat: 553C
#   Unesite izraz: 1234 + FFff
#   Nepoznata operacija!
#   Unesite izraz: 12345 | ABCDEFG
#   Pogrešan drugi operand!
#   Unesite izraz: 1234567890ABCDEF0123 | ABCD
#   Prekoračenje prvog operanda!
#   Dodatni primeri se mogu napraviti uz pomoć kalkulatora

# hajde prvo 32-bitni

.section .data
    izraz: .ascii "A41f ^ F123\n"
    string: .fill 50,1,42
    # string: .ascii "FFFF  &   0010    \n"
    heksa: .long 0       # 1EC6
    heksa_2: .long 0
    rezultat: .long 0
    string_krajnji: .fill 50,1,42
    unos_str: .ascii "Unesite izraz: \0"
    unos_str_len = . - unos_str
    operacija_err: .ascii "Nepoznata operacija!\n"
    operacija_len = . - operacija_err
.section .text
.globl main

main:
    # ispis teksta
    movl $4, %eax
    movl $1, %ebx
    leal unos_str, %ecx
    movl $unos_str_len, %edx
    int $0x80

    # unos broja
    movl $3, %eax
    movl $0, %ebx
    leal string, %ecx
    movl $40, %edx
    int $0x80

    movl %eax, %esi         # toliko je dug str

    # str to int: prvo se pushuje adresa za broj, pa onda adresa stringa.
    leal string, %ecx
    pushl heksa
    pushl %ecx
    call str_to_int
    addl $8, %esp

    movl %eax, heksa

    # u ecx ce biti prvi sledeci razmak!

do_operacije:
    movb (%ecx), %dl
    cmpb $' ', %dl
    jne provera_operacije
    incl %ecx
    jmp do_operacije

#    &
#   (and),
#   |
#   (or) i
#   ^
#   (xor).

provera_operacije:
    cmpb $'&', %dl
    je anduj
    cmpb $'|', %dl
    je oruj
    cmpb $'^', %dl
    je xoruj
    jmp nepoznata_operacija

anduj:
    incl %ecx
    movb (%ecx), %dl
    cmpb $' ', %dl
    je anduj

    # ok dosli smo do necega sto nije razmak, treba da unesemo to
    pushl heksa_2
    pushl %ecx
    call str_to_int
    addl $8, %esp

    movl %eax, heksa_2

    movl heksa, %ebx
    movl heksa_2, %ecx
    andl %ecx, %ebx
    movl %ebx, rezultat

    jmp ispis
    
xoruj:
    incl %ecx
    movb (%ecx), %dl
    cmpb $' ', %dl
    je xoruj

    # ok dosli smo do necega sto nije razmak, treba da unesemo to
    pushl heksa_2
    pushl %ecx
    call str_to_int
    addl $8, %esp

    movl %eax, heksa_2

    movl heksa, %ebx
    movl heksa_2, %ecx
    xorl %ecx, %ebx
    movl %ebx, rezultat

    jmp ispis

oruj:
    incl %ecx
    movb (%ecx), %dl
    cmpb $' ', %dl
    je oruj

    # ok dosli smo do necega sto nije razmak, treba da unesemo to
    pushl heksa_2
    pushl %ecx
    call str_to_int
    addl $8, %esp

    movl %eax, heksa_2

    movl heksa, %ebx
    movl heksa_2, %ecx
    orl %ecx, %ebx
    movl %ebx, rezultat

    jmp ispis


    # priprema za ispis!!!!
ispis:
    # int to str: prvo se pushuje broj, pa adresa za string. povratna vrednost je eax. tu je br slova.
    leal string_krajnji, %ebx
    pushl rezultat
    pushl %ebx
    call int_to_str
    addl $8, %esp

    movl %eax, %edx

    # ispis broja
    movl $4, %eax
    movl $1, %ebx
    leal string_krajnji, %ecx
    int $0x80
    jmp good_kraj

nepoznata_operacija:
    movl $4, %eax
    movl $1, %ebx
    leal nepoznata_operacija, %ecx
    movl $operacija_len, %edx
    int $0x80

bad_kraj:
    movl $1, %ebx
    jmp kraj

good_kraj:
    movl $0, %ebx
kraj:
    movl $1, %eax
    int $0x80






# potprogram za konverziju internog broja u string (heksadecimalan)
# 1010 - A;     1001 - 9;       1000 - 8;       0111-7
# povratna vrednost je br cifata

int_to_str:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %edi
    pushl %esi

    movl 8(%ebp), %ecx      # lokacija
    movl 12(%ebp), %eax     # nas broj
    movl 12(%ebp), %edi

    movl $0x0000000F, %ebx  # maska za 4 najmanje znacajne cifre
    # a mogli smo i da delimo sa 10000 i uzmemo ostatak
    movl $0, %esi

sledeci_set_od_cetiri:
    movl %edi, %eax
    andl %ebx, %eax         # u eax ce ostati samo ta 4 najmanja

    incl %esi

    cmpl $9, %eax
    ja slovo

# dakle broj je
# i treba ga pretvoriti u int
# dodajemo 0, i stavljamo ga na ecx
broj_petlja:
    addb $'0', %al
    movb %al, (%ecx)
    incl %ecx

    shrl %edi
    shrl %edi
    shrl %edi
    shrl %edi
    cmpl $0, %edi
    jne sledeci_set_od_cetiri
    je obrni

slovo:
    # oduzeti 10 od tog broja, i dodati A (-48 + 65 = +17)
    subl $10, %eax
    addb $'A', %al
    movb %al, (%ecx)
    incl %ecx

    shrl %edi
    shrl %edi
    shrl %edi
    shrl %edi
    cmpl $0, %edi
    jne sledeci_set_od_cetiri

obrni:
    movb $'\n', (%ecx)
    decl %ecx
    movl 8(%ebp), %ebx

obrni_petlja:

    cmpl %ebx, %ecx
    jle kraj_to_str

    movb (%ebx), %dh
    movb (%ecx), %dl
    movb %dl, (%ebx)
    movb %dh, (%ecx)

    incl %ebx
    decl %ecx
    jmp obrni_petlja


kraj_to_str:
    movl %esi, %eax     # vracamo koliko ima karaktera taj string
    incl %eax

    popl %esi    
    popl %edi
    popl %ebx
    
    movl %ebp, %esp
    popl %ebp
    ret





#   potprogram za konverziju heksa string u interni

    # str to int: prvo se pushuje adresa za broj, pa onda adresa stringa.

str_to_int:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %ecx      # adresa stringa
    movl 12(%ebp), %eax     # promenljiva gde je broj

    movl $16, %ebx

petlja_to_int:
    xorl %edx, %edx
    mull %ebx

    movb (%ecx), %dl

    cmpb $'\n', %dl
    je ocisti_stek

    cmpb $'9', %dl
    ja slovo_to_int
    cmpb $'0', %dl
    jb ocisti_stek

    subb $'0', %dl
    addl %edx, %eax
    incl %ecx

    jmp petlja_to_int

slovo_to_int:
    cmpb $'A', %dl
    jb ocisti_stek
    cmpb $'F', %dl
    ja mala_slova

    subb $'A', %dl
    addl $10, %edx
    addl %edx, %eax
    incl %ecx
    jmp petlja_to_int

mala_slova:
    cmpb $'a', %dl
    jb ocisti_stek
    cmpb $'f', %dl
    ja ocisti_stek

    subb $'a', %dl
    addl $10, %edx
    addl %edx, %eax
    incl %ecx
    jmp petlja_to_int


ocisti_stek:
    xorl %edx, %edx
    divl %ebx

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret
