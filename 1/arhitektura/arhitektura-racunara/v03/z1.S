# Napisati asemblerski program koji određuje sumu elemenata podniza:
#   a. Rezervisati memorijski prostor za dve promenljive tipa long – ind1 i ind2; sabrati
#   elemente koji se nalaze između ova dva indeksa
#   b. Koristiti indeksno adresiranje


.section .data
    ind1: .long 2
    ind2: .long 7
    niz: .long 1,1,1,1,0,0,5,0       # 1+1+0+0+5
    suma: .long 0
    NELEM = 8
.section .text
.globl main

main:
    movl ind1, %esi           # indeksni registar
    movl $0, %eax

petlja:
    addl niz(,%esi,4), %eax
    incl %esi
    cmpl ind2, %esi
    jl petlja

kraj:
    movl %eax, suma
    movl $1, %eax
    movl $0, %ebx
    int $0x80