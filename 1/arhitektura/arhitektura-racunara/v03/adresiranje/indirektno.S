# Ova varijanta programa je podesna za pretvaranje u potprogram, pošto se u glavnoj petlji
# nigde eksplicitno ne navodi adresa niza (ona je pre glavne petlje postavljena u registar esi).


.section .data
    NELEM = 10
    niz: .long 1,2,3,4,5,6,7,8,9,10
    suma: .long 0
.section .text
.globl main
main:
    movl $niz, %esi           # indeksni registar
    movl $0, %eax           # eax se koristi za računanje sume
petlja:
    addl (%esi), %eax
    addl $4, %esi
    cmpl $niz+NELEM*4, %esi
    jl petlja
kraj:
    movl %eax, suma
    movl $1, %eax
    movl $0, %ebx
    int $0x80