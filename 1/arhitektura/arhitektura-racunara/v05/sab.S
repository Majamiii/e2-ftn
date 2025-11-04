.section .data
    a: .long 123
    b: .long 456
.section .text
.globl main

main:
    pushl b
    pushl a
    call saberi
    addl $8, %esp

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80

