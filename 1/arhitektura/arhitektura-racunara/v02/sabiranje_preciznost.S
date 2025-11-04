# sabiranje neoznacenih
# kod oznacenih isto samo jno kraj -> overload umesto carry


.section .data
    a: .quad 0x8000
    b: .long 0x8000,1
    greska: .byte 0
.section .text
.globl main

main:
    movb $0, greska
    movl a, %eax
    addl b, %ebx
    movl a+4, %edx
    adcl b+4, %edx

    jnc kraj
    incb greska

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80