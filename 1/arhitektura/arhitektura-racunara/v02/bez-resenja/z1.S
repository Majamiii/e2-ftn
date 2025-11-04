# 1. Napisati asemblerski program koji računa NZD dva broja, koristeći promenljive 
#     a. Izmeniti primer računanja NZD-a sa prvog termina vežbi, tako da se za brojeve i 
#     rezultat umesto registara koriste promenljive (inicijalizovane u .section .data delu 
#     koda, ne mora se koristiti mov instrukcija za početne vrednosti) 


.section .data
    a: .long 35
    b: .long 25
.section .text
.globl main


main:
    movl a, %eax
    cmpl %eax, b
    je kraj

petlja:
    cmpl %eax, b
    jle a_manje

    # b_manje
    subl %eax, b

    cmpl %eax, b
    je kraj
    jmp petlja

a_manje:
    # od b oduzimamo a
    subl b, %eax

    cmpl %eax, b
    je kraj
    jmp petlja

kraj:
    movl %eax,a
    movl $1, %eax
    movl $0, %ebx
    int $0x80