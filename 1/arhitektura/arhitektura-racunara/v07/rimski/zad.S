.section .text
.globl inter_to_roman
dec:    .long 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
rom1:   .ascii "MCDCCXLXXIVII"
rom2:   .ascii " M D C L X V "

#   int inter_to_roman(unsigned int broj, char* str, int duzina)

inter_to_roman:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 12(%ebp), %edx     # gde ga smestamo
    #   8(%ebp)   -  koji broj
    #   16(%ebp)  -  max duzina
    movl $0, %ecx        # brojac

petlja:

    movl dec(,%ecx,4), %eax
    cmpl %eax, 8(%ebp)
    jb sledeci

    subl %eax, 8(%ebp)

    movb rom1(,%ecx,1), %bl
    movb %bl, (%edx)
    incl %edx
    decl 16(%ebp)
    jz greska

    movb rom2(,%ecx,1), %bl
    cmpb $' ', %bl
    je petlja

    movb %bl, (%edx)
    incl %edx
    decl 16(%ebp)
    jz greska

    jmp petlja

sledeci:
    incl %ecx

    cmpl $13, %ecx
    jl petlja

    movb $0, (%edx)
    jmp sve_ok

greska:
    movl $1, %eax
    jmp ocisti_stek

sve_ok:
    movl $0, %eax

ocisti_stek:
    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret

