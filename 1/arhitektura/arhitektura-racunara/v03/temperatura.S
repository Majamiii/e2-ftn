# Zadatak je da se u zadatom podintervalu prebroje dani kod kojih je temperatura unutar zadatog opsega.

# Napomene uz primer:
# – Pojedinačnim vrednostima niza pristupa se pomoću indeksnog adresiranja.
# – Kao brojač iteracija glavne petlje programa (koja počinje labelom jedan_dan) koristi se
# registar ecx. Za njegovo dekrementiranje, testiranje i uslovno grananje moguće je koristiti
# specijalnu naredbu loop koja podrazumeva korišćenje samo ovog registra (zbog
# neortogonalnosti skupa naredbi 80386). U ovom slučaju, loop jedan_dan bilo bi
# ekvivalentno nizu naredbi
#   decl %ecx
#   jnz jedan_dan
# – Obratiti pažnju na korišćenje 16-bitnih i 32-bitnih registara (na primer, paralelno se koriste
# kako registar bx, tako i registar ebx).

.section .data
    niz: .long 5,6,7,3,4,5,0,8      # u opsegu od 4 do 7 u intervalu od 2. do 7. clana su projevi: 7,3,4,5
    NELEM = 8
    d_prvi: .long 2
    d_poslednji: .long 7
    g_gornja: .long 7
    g_donja: .long 4
    brojac: .long 0
    greska: .byte 0
.section .text
.globl main

main:
    movl $0, %ebx                   # rezultat (brojac dana u opsegu)
    movl %ebx, brojac
    movl d_poslednji, %ecx                # indeksni registar
    subl $1, %ecx
    movl $niz, %edx                   # adresni registar
    jmp granice_err

petlja:
    movl (%edx, %ecx, 4), %eax
    jmp provera

nazad_petlja:
    subl $1, %ecx
    cmpl d_prvi, %ecx
    jge petlja

    movl brojac, %ebx
    jmp kraj

provera:
    cmpl g_gornja, %eax
    jg nazad_petlja 
    cmpl g_donja, %eax
    jl nazad_petlja

    addl $1, brojac
    jmp nazad_petlja  

granice_err:
    movl g_gornja, %eax
    subl g_donja, %eax
    cmpl $0, %eax
    jle err
    jmp petlja          # ili dalja provera

err:
    movl greska, %ebx

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80
