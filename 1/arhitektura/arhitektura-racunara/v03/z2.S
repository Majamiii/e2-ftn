#   Napisati asemblerski program koji nalazi minimalni i maksimalni element niza označenih
#   brojeva:
#       a. Rezervisati memorijski prostor za dve promenljive – min i max, koje će po završetku
#       programa sadržati minimalni i maksimalni element niza
#       b. Koristiti indirektno adresiranje


.section .data
    niz: .long 5,6,1,9,-2,700,56,3
    NELEM = 8
    min: .long 0
    max: .long 0
.section .text
.globl main

main:
    movl $niz, %esi
    movl (%esi), %eax
    movl %eax, min
    movl (%esi), %eax
    movl %eax, max

petlja:
    movl (%esi), %eax
    addl $4, %esi
    cmpl min, %eax
    jl manji
    cmpl max, %eax
    jg veci

    cmpl $niz+NELEM*4, %esi
    jl petlja
    jmp kraj

manji:
    movl %eax, min
    jmp petlja

veci:
    movl %eax, max
    jmp petlja

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80