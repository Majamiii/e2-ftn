#   Napisati asemblerski potprogram za konverziju iz znakovnog oblika (ceo neoznačeni
#   oktalni broj) u interni oblik:
#       a. Direktorijum oktalni.
#       b. Potpis funkcije:
#           unsigned int oct_str_to_inter(char* str, unsigned int* greska)
#       c. Povratna vrednost – interni oblik broja.
#       d. Potprogram proverava greške:
#           i. pojava cifre van dozvoljenog opsega u ulaznom stringu, kao i prazan
#               string, vraćaju grešku 1,
#           ii. prekoračenje kapaciteta vraća grešku 2


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

    movb (%esi), %dl
    cmpb $0, (%esi)
    je prazan

petlja:
    movb (%esi), %bl
    cmpb $0, %bl
    je kraj

    cmpb $'0', %bl
    jb nedozvoljen

    cmpb $'7', %bl
    ja nedozvoljen

    subb $'0', %bl
    mull %ecx
    jc prekoracenje

    addl %ebx, %eax
    jc prekoracenje

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