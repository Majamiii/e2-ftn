# samo pr programa - upis necega i ispis istog tog stringa

.section .data
    duzina = 28 # za 7 karaktera
    tekst: .fill duzina, 1, 42
.section .text
.globl main

main:
    movl $3, %eax
    movl $0, %ebx
    leal tekst, %ecx
    movl $duzina, %edx
    int $0x80

    movl %eax, %edx     # broj procitanih bajtova??

    movl $4, %eax
    movl $1, %ebx
    leal tekst, %ecx
    movl $duzina, %edx
    int $0x80

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80
