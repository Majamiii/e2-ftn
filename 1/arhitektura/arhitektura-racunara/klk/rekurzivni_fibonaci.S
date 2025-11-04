#   int fibonaci(int n, unsigned int* rez);


# dakle n nam govori koji element trazimo, i njegovu vrednost pisemo na adresu koja je prosledjena kao drugi parametar

# povratna vrednost funkcije je 0 ako nije doslo do greske
# ako je 0 onda je doslo do greske

.section .text
.globl fibonaci

fibonaci:
    pushl %ebp
    movl %esp, %ebp

#   oslobadjanje registara za koriscenje

    pushl %ebx
    pushl %esi
    pushl %edi
    pushl %edx

    movl 8(%ebp), %ebx      #   tu nam se nalazi n
    movl 12(%ebp), %ecx     #   tu nam je adresa za rezultat

    movl $0, (%ecx)

    #   F(n) = F(n-1) + F(n-2)
    #   F(1) = 1, F(2)=1

    cmpl $0, %ebx
    jle greska

    cmpl $1, %ebx
    je baza

    cmpl $2, %ebx
    je baza

    movl (%ecx), %edx       # tu cemo sad da sabiramo fibonacije, rez ide u edx pa cemo ga vratiti u ecx

    decl %ebx   # F(n-1)

    pushl %ecx
    pushl %ebx
    call fibonaci
    addl $8, %esp

    addl (%ecx), %edx

    decl %ebx   # F(n-2)

    pushl %ecx
    pushl %ebx
    call fibonaci
    addl $8, %esp

    addl (%ecx), %edx


    movl %edx, (%ecx)
    jmp ok_kraj

baza:
    movl $1, (%ecx)
    jmp ok_kraj

greska:
    movl $1, %eax
    jmp ocisti_stek

ok_kraj:
    movl $0, %eax

ocisti_stek:
    popl %edx
    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret