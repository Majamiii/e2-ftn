#   1. Napraviti potprogram int uvecaj(int x) koji na argument dodaje 1 i vraća dobijeni broj.

.section .text
.globl uvecaj

uvecaj:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    incl %eax
   
    movl %ebp, %esp
    popl %ebp
    ret


