# Napisati asemblerski program koji pronalazi n-ti  element  Fibonačijevog  niza,  koristeći 
# promenljive dvostruke preciznosti 
#     a. Osnovna ideja je identična kao i kod prethodnog zadatka 
#     b. Razlika: smatrati da su članovi niza (uzastopni Fibonačijevi sabirci), pa ujedno i 
#     konačan rezultat, 64-bitni; broj n može biti u jednostrukoj preciznosti

.section .data
    n: .long 6
    b: .long 0x0000
    c: .long 0x0001 # next
    b_up: .long 0x0000
    c_up: .long 0x0000
    result: .quad 0x00000000
    g: .byte 0
.section .text
.globl main

main:
    movl b, %ebx
    movl c, %ecx

    movl b+4, %eax
    movl %eax, b_up
    movl c+4, %edx
    movl %edx, c_up

    cmpl $1, n
    je kraj

    cmpl $2, n
    je dvojka
    jne petlja

dvojka:
    movl $2, %ebx
    movl %ebx, b
    je kraj

petlja:
    cmpl $0, n
    je kraj

    movl n, %eax
    subl $1, %eax
    movl %eax, n

    
    movl b, %eax              # eax = b (low)
    addl c, %eax              # eax = b + c
    movl %eax, b              # b = b + c

    movl b_up, %edx           # edx = b_up
    adcl c_up, %edx           # edx = b_up + c_up + carry
    movl %edx, b_up

    jc greska

    # rotiraj vrednosti: c = stara b
    movl c, %eax
    movl b, %ecx
    movl %eax, b
    movl %ecx, c

     movl c_up, %eax
    movl b_up, %ecx
    movl %eax, b_up
    movl %ecx, c_up

    jmp petlja

greska:
    movb $1, g

kraj:
    movl b, %ebx
    movl %ebx, result
    movl b_up, %eax
    movl %eax, result+4
    mov $1, %eax
    mov $0, %ebx
    int $0x80