# 1. Napisati asemblerski program koji računa zbir prvih n prirodnih brojeva
#   a. Proizvoljan broj n se na početku programa postavlja u neki od dostupnih registara opšte namene, instrukcijom “mov”
#   b. Konačan rezultat treba se naći u nekom od dostupnih registara opšte namene
#   c. Primer: ako je n = 5, rezultat je 1+2+3+4+5 = 15

.section .data
.section .text
.globl main

main:

    movl $5, %eax
    movl $0, %ecx   # zbir

proveri:
    cmpl $0, %eax
    je kraj
    addl %eax, %ecx
    subl $1, %eax

    jmp proveri

    # cmpl %ebx, %eax

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80



