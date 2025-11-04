#   Napisati asemblerski program koji računa faktorijel broja n, koristeći promenljive 
#       a. Zadatak je identičan zadatku 4 sa prvog termina vežbi; jedina razlika je što broj n, kao 
#       i rezultat, treba smestiti u promenljive (označene memorijske lokacije) umesto u 
#       registre;  brojevi  se  mogu  smestiti  u  promenljive  odmah  pri  inicijalizaciji  (u  .section 
#       .data delu koda), ne mora se koristiti mov instrukcija

.section .data
    a: .long 6
    n: .long 1
.section .text
.globl main

main:
    cmpl $0, a
    je kraj
    movl $1, %ecx

petlja:
    cmpl %ecx, a
    je kraj

    movl n, %edx     # edx je brojac

mnozi:  # treba n*ecx i da se smesti u n, dakle dodajemo exc na n sve dok brojac od ecx ne dodje do 1

    cmpl $0, %edx
    je nazad

    addl %ecx, n

    subl $1, %edx
    jmp mnozi
nazad:
    addl $1, %ecx
    jmp petlja

kraj:
    movl n, %ebx
    movl $1, %eax
    movl $0, %ebx
    int $0x80