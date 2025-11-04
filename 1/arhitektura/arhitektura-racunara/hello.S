.section .data
.section .text
.globl main
main:
    movl $5, %eax        # l znaci da su long, th 32-bitni
    movl $3, %ebx

    addl %eax, %ebx

kraj:                # return 0
    movl $1, %eax
    movl $0, %ebx
    int $0x80


# -o onda nazoves kako se zove izlazni fajl


# gcc -m32 -g -o primer hello.S
# ls
# ./primer