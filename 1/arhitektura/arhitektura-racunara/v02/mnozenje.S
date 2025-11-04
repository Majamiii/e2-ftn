# mnozenje sa promenljivima


.section .data
    a: .long 3
    b: .long 5
    c: .long 0          # a*b
.section .text
.globl main

main:
    movl b, %eax

petlja:
    cmpl $0, a
    je kraj

    addl %eax, c

    subl $1, a
    jmp petlja

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80





