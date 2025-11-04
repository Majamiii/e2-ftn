# 7. U asemblerskom jeziku implementirati deljenje dva broja pomoću oduzimanja, uz čuvanje 
# ostatka, koristeći promenljive dvostruke preciznosti 
#     a. Zadatak je identičan zadatku 5 sa prvog termina vežbi; jedina razlika je što deljenik, 
#     delilac, količnik i ostatak treba smestiti u promenljive (označene memorijske lokacije) 
#     umesto u registre; brojevi se mogu smestiti u promenljive odmah pri inicijalizaciji (u 
#     .section .data delu koda), ne mora se koristiti mov instrukcija 

.section .data
    p: .long 22  # deljenik
    q: .long 3  # delilac
    r: .long 0  # rezultat      -  treba da bude 7
    o: .long 0  # ostatak       - treba da bude 1
.section .text
.globl main

main:
    movl q, %ebx
    cmpl $0, p
    je kraj
    cmpl $0, q
    je kraj

deli:
    cmpl %ebx, p
    jl ostatak

    subl %ebx, p
    addl $1, r
    jmp deli

ostatak:
    movl p, %ebx
    movl %ebx, o

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80