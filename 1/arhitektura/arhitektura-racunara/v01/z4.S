#   4. Napisati asemblerski program koji računa faktorijel broja n
#       a. Proizvoljan broj n se na početku programa postavlja u neki od dostupnih registara opšte namene, instrukcijom “mov”
#       b. Konačan rezultat treba se naći u nekom od dostupnih registara opšte namene
#       c. Primer: za n = 5, rezultat je 5! = 5*4*3*2*1 = 120
#       d. Napomena: za množenje koristiti ranije implementirano množenje pomoću sabiranja

.section .data
.section .text
.globl main

main:
    movl $5, %eax       # ukupan proizvod
    movl $0, %ebx       # sa cime sledece mnozimo
    movl $5, %edx       # iterator
    movl $0, %ecx

fibonaci:

    movl %edx, %ebx
    subl $1, %ebx
    subl $1, %edx

    cmpl $0, %edx
    je kraj


# mnozenje: ovo u a sa ovim u b i smesta se u c

    movl $0, %ecx

    cmpl %eax, %ebx         # namestamo da je u ebx manji broj, i to ce ujedno biti i iterator
    ja zameni
    jmp petlja              # ako je sve ok onda idemo direktno u petlju

zameni:
    xchgl %eax, %ebx

petlja:
    cmpl $0, %ebx
    je proizvod

    addl %eax, %ecx
    subl $1, %ebx
    jmp petlja

proizvod:
    movl %ecx, %eax
    jmp fibonaci

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80


