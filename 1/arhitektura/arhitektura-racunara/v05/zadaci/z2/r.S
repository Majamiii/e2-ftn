.section .text
.globl fibonaci


fb:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %edi

    movl 8(%ebp), %eax      # n
    movl 12(%ebp), %ebx     # adresa za rez
    
    movl $0, %edx

    cmpl $2, %eax
    jg rekurzija

    movl $0, (%ebx)           # nema greske
    movl $1, %eax
    jmp kraj


greska:
    movl $1, (%ebx)

kraj:
    popl %edi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret


rekurzija:
    decl %eax               # n-1
    movl %eax, %edx
    subl $4, %esp           # za vr rezultata
    leal (%esp), %edi       # !!!!!!!!!!! JAKO BITNO !!!!!!!!!!! - edi ce sad cuvati adresu za lokalni rezultat
    pushl %edi              # rezultat - adresa
    pushl %edx              # n-1
    call fb
    addl $8, %esp

    cmpl $0, (%ebx)
    jne greska

    movl (%edi), %edx       # stavljamo dobijenu vrednost u edx
    addl $4, %esp


    decl %eax
    movl %eax, %ecx
    subl $4, %esp
    leal (%esp), %edi
    pushl %edi
    pushl %ecx
    call fb
    addl $8, %esp

    cmpl $0, (%ebx)
    jne greska

    movl (%edi), %ecx
    addl $4, %esp


    addl %ecx, %edx
    jc greska

    movl %edx, %eax
    movl $0, (%ebx)
    jmp kraj


fibonaci:
    pushl %ebp
    movl %esp, %ebp

    pushl 12(%ebp)      # adresa za rez
    pushl 8(%ebp)       # n
    call fb
    addl $8, %esp

    movl %ebp, %esp
    popl %ebp
    ret