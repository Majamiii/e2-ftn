
.section .text
.globl saberi

saberi:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi


    movl 8(%ebp), %eax
    addl 12(%ebp), %eax

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret

