# mnozenje double 

# mnozenje sa promenljivima
# pitanje da li je dobro


.section .data
    a: .quad 5
    b: .quad 0x10000000A
    c: .quad 0          # a*b
    g: .byte 0
.section .text
.globl main

main:
    movl $0, %ecx    # nizi deo rezultata
    movl $0, %edx   # visi deo rezultata

petlja:
    cmpl $0, a+4
    jne dalje
    cmpl $0, a
    je kraj

dalje:
    addl b, %ecx
    adcl b+4, %edx

    jc greska

    subl $1, a
    sbbl $0, a+4    # smanjujemo ako se desila pozajmica

    jmp petlja

greska:
    movb $1, g

kraj:
    movl %ecx, c
    movl %edx, c+4
    movl $1, %eax
    movl $0, %ebx
    int $0x80





