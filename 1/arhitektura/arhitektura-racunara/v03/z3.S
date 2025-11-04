#   Napisati asemblerski program za sortiranje niza 16-bitnih označenih vrednosti (u
#   proizvoljnom redosledu):
#       a. Koristiti proizvoljni tip adresiranja
#       b. Dostupno rešenje sortira niz u rastućem redosledu, primenom bubble-sort algoritma    


.section .data
    niz: .long 8,7,6,5,2,3,4,1
    NELEM = 32
    greske: .long -1
    brojac: .long 0
.section .text
.globl main

main:

petlja:
    movl $niz, %esi
    movl $0, brojac

    movl (%esi), %eax
    addl $4, %esi
    movl (%esi), %ebx
    subl $4, %esi

    cmpl $0, greske
    je kraj

    movl $0, greske

    
    cmpl %eax, %ebx
    jl menjaj

nastavi:
    addl $4, brojac

    movl $NELEM, %edx
    addl $4, brojac
    cmpl %edx, brojac
    jge petlja
    subl $4, brojac

    movl $niz, %esi
    addl brojac, %esi

    movl (%esi), %eax
    addl $4, %esi
    movl (%esi), %ebx
    subl $4, %esi

    cmpl %eax, %ebx
    jl menjaj

    jmp nastavi

menjaj:
    # addl brojac, %esi
    movl (%esi), %edx
    addl $4, %esi
    movl (%esi), %ecx

    addl $4, brojac
    movl brojac,%eax
    movl %edx, niz(%eax)
    subl $4, %eax
    movl %ecx, niz(%eax)
    subl $4, brojac

    addl $1, greske
    jmp nastavi

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80