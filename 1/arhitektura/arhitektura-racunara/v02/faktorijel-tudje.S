# gavrilovic nikola faktorijel


.section .data
n:  .quad 50
rez:    .quad 1
g:  .byte 0
.section .text
.globl main
main:
prvaI:
    cmpl $0, n+4
    jne dalje
    cmpl $1, n
    je kraj
dalje:
    movl n+4, %eax
    movl n, %ebx
    movl rez+4, %ecx
    movl rez, %edx
    movl $0, rez
    movl $0, rez+4
    jmp druga
prvaII:
    subl $1, n
    sbbl $0, n+4
    jmp prvaI
druga:
    cmpl $0, %eax
    jne daljeII
    cmpl $0, %ebx
    je prvaII
daljeII:
    addl %ecx, rez+4
    adcl %edx, rez
    jc greska
    subl $1, %ebx
    sbbl $0, %eax
    jmp druga
greska:
    movb $1, g
kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80