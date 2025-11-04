# 3. Napisati asemblerski program koji pronalazi n-ti element Fibonačijevog niza
#        a. Proizvoljan broj n se na početku programa postavlja u neki od dostupnih registara opšte namene, instrukcijom “mov”
#        b. Konačan rezultat treba se naći u nekom od dostupnih registara opšte namene
#        c. Fibonačijev niz – vrednost prvog i drugog elementa niza je 1; svaki naredni element računa se kao zbir prethodna dva; prvih nekoliko elemenata niza:
#        1, 1, 2, 3, 5, 8, 13, 21, 34, 55
#        Na primer, vrednost 7. elementa je 5 + 8 = 13
#        d. Primer: ako je n = 6, rezultat je 8


.section .data
.section .text
.globl main

main:
    movl $6, %eax   # n
    movl $0, %ebx   # prethodni
    movl $1, %ecx   # rezultat
    movl $1, %edx   # iterator


petlja:
    addl %ebx, %ecx
    xchgl %ebx, %ecx

    cmpl $1, %eax
    je kraj
    
    addl $1, %edx
    cmpl %eax, %edx
    jle petlja

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80