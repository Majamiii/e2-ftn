#   Izbacuje Uspeli kao rezultat jer ne znam jos da ispisem broj vec samo proverava da li je
#   za n=5 rezultat 120 i ako jeste onda napise to


#   u praktikumu ima njihov pr za faktorijel dosta je krace ali to je to manje vise
#   tj samo telo te rekurzivne funkcije

.section .data
    a: .long 5      # 5*4*3*2*1=120
    lena = . - a
    k_str: .ascii "Uspeli!!!\n\0"
    lenk = . - k_str
    vrednost: .long 1
.section .text
.globl main

main:
    movl a, %ebx
    movl $1, %eax
    movl $vrednost, %ecx

    pushl %ebx
    pushl %eax
    pushl %ecx
    call pp
    addl $12, %esp

    movl %eax, %ecx

    cmpl $120, %ecx
    je kraj

kraj:
    movl $4, %eax
    movl $1, %ebx
    leal k_str, %ecx
    movl $lenk, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80


pp:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %ecx
    pushl %edx
    pushl %edi
    pushl %esi

    movl 8(%ebp), %esi      # ovo je adresa gde pisemo br
    movl 12(%ebp), %ebx      # tu je na pocetku 1, taj br mnozimo
    movl 16(%ebp), %ecx     # ovde je n

    cmpl $1, %ecx
    je baza

    mull %ecx
    movl %ecx, (%esi)
    decl %ecx

    movl $vrednost, %esi

    pushl %ecx
    pushl %ebp
    pushl %esi
    call pp
    addl $12, %esp



    jmp ocisti_stek

baza:

ocisti_stek:
    popl %esi
    popl %edi
    popl %edx
    popl %ecx
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret