#   oktalni - OZNACENI


.section .text
.globl oct_str_to_inter

oct_str_to_inter:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %esi      # adresa za string
    movl 12(%ebp), %edi     # kod greske

    movl $8, %ecx           # baza sistema
    movl $0, %edx
    movl $0, %eax           # rezultat
    movl $0, %ebx

    movb (%esi), %bl
    cmpb $0, (%esi)
    je prazan

    cmpb $'+', %bl
    je plus

    cmpb $'-', %bl
    je minus

    jmp petlja

plus:
    incl %esi
    jmp petlja

minus:
    movb %bl, (%esi)
    incl %esi

petlja:
    movb (%esi), %bl
    cmpb $0, %bl
    je kraj

    cmpb $'0', %bl
    jl nedozvoljen

    cmpb $'7', %bl
    jg nedozvoljen

    subb $'0', %bl
    mull %ecx
    jo prekoracenje

    addl %ebx, %eax
    jo prekoracenje

    incl %esi
    jmp petlja  

prazan:
    movl $1, (%edi)
    jmp ocisti_stek

nedozvoljen:
    movl $1, (%edi)
    jmp ocisti_stek

prekoracenje:
    movl $2, (%edi)
    jmp ocisti_stek

kraj:
    movl $0, (%edi)

ocisti_stek:
    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret