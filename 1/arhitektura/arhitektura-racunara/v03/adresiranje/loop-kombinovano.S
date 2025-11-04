.section .data
    NELEM = 10
    niz: .long 1,2,3,4,5,6,7,8,9,10
    suma: .long 0
.section .text
.globl main
main:
    movl $niz, %esi             # bazni registar
    movl $NELEM, %ecx           # indeksni registar
    movl $0, %eax               # eax se koristi za računanje sume
petlja:
    addl -4(%esi, %ecx, 4), %eax
    loopl petlja
kraj:
    movl %eax, suma
    movl $1, %eax
    movl $0, %ebx
    int $0x80