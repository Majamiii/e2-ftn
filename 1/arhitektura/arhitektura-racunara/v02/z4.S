#  4. Napisati asemblerski program koji pronalazi n-ti  element  Fibonačijevog  niza,  koristeći 
#  promenljive 
#      a. Zadatak je identičan zadatku 3 sa prvog termina vežbi; jedina razlika je što broj n, kao 
#      i rezultat, treba smestiti u promenljive (označene memorijske lokacije) umesto u 
#      registre;  brojevi  se  mogu  smestiti  u  promenljive  odmah  pri  inicijalizaciji  (u  .section 
#      .data delu koda), ne mora se koristiti mov instrukcija 
#      b. Dostupna su dva rešenja ovog zadatka; drugo rešenje (optimizovano) je kraće i koristi 
#      manje registara 

.section .data
    a: .long 6          # n
    c: .long 1          # rezultat
    b: .long 0
.section .text
.globl main

main:
    movl b, %ebx   # prethodni    -   efektivno ovde ostaje rezultat
    movl $1, %edx   # iterator
    movl c, %ecx
    # movl b, %ebc

petlja:
    addl %ebx, %ecx
    xchgl %ebx, %ecx

    cmpl $1, a
    
    je kraj
    
    addl $1, %edx
    cmpl a, %edx
    jle petlja

kraj:
    movl %ebx, b
    movl $1, %eax
    movl $0, %ebx
    int $0x80


