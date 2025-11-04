.section .data
    poruka1: .ascii "Unesite ime i prezime: \0"
    poruka1_duzina = . - poruka1
    poruka2: .ascii "Vi ste: \0"
    poruka2_duzina = . - poruka2
    imeprez: .fill 50,1,42
    #   imeprez: .ascii "Maja"
    imeprez_duzina = . - imeprez
.section .text
.globl main

# 65-A, 90-Z, 97-a, 122-z       dakle oduzimamo 32 od malih da bismo dobili velika slova

main:
# stampanje prvog stringa
    movl $4, %eax
    movl $1, %ebx
    leal poruka1, %ecx
    movl $poruka1_duzina, %edx
    int $0x80

# upis naseg imena i prezimena
    movl $3, %eax
    movl $0, %ebx
    leal imeprez, %ecx
    movl $imeprez_duzina, %edx
    int $0x80

    cmpl $0, %eax
    jl eror

    movl $4, %esi     # cuvamo duzinu unetog stringa, bice ista i posle menjanja
    leal imeprez, %eax       # do kod smo karaktera stigli

petlja:
    cmpb $'a', (%eax)
    jl petlja2
    cmpb $'z', (%eax)
    jg petlja2
    subb $32, (%eax)

    cmpb $0, (%eax)
    jne petlja2
    jmp gotovo

petlja2:
    incl %eax
    cmpb $0, (%eax)
    je gotovo
    jmp petlja

gotovo:
# stampanje drugog stringa
    movl $4, %eax
    movl $1, %ebx
    leal poruka2, %ecx
    movl $poruka2_duzina, %edx
    int $0x80

# stampanje naseg imena i prezimena
    movl $4, %eax
    movl $1, %ebx
    leal imeprez, %ecx
    movl %esi, %edx
    int $0x80

    pushl $0x0A     # ascii za novi red
    movl $4, %eax
    movl $1, %ebx
    movl %esp, %ecx
    movl $1, %edx
    int $0x80
    addl $4, %esp

/*
    movb $0x0A, 1(%eax)
    movl $4, %eax
    movl $1, %ebx
    leal imeprez, %ecx
    addl %esi, %ecx
    movl $1, %edx
    int $0x80
*/
    jmp end

eror:


end:
    movl $1, %eax
    movl $0, %ebx
    int $0x80