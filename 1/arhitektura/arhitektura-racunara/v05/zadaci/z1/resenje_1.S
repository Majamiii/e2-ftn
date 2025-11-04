#   1. Napisati potprogram u asemblerskom jeziku kojim se računa n-ti element Fibonačijevog niza:
#       a. Zaglavlje funkcije (potprograma) dato je u glavni.c fajlu u Z1 folderu
#       b. Potprogram kao povratnu vrednost vraća kod greške – greška nastupa ukoliko dođe
#           do prekopračenja pri sabiranju (za vežbu, možete proširiti zadatak tako da greška
#           nastupa i kada je prosleđeno nevalidno n); potprogram vraća 0 ukoliko nije nastupila
#           greška, a bilo šta drugo ukoliko jeste nastupila
#       c. Potprogram vraća pronađeni n-ti element niza preko parametra unsigned int* rez
#           prenetog po adresi
#       d. Fajl resenje_1.S sadrži rešenje sa manje uključenih parametara, dok fajl
#           resenje_2_za_testiranje.S sadrži rešenje koje se može proslediti skripti za testiranje

# .section .data
.section .text
.globl fibonaci


# g = fibonaci(n, &f);

fibonaci:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %eax          # n se nalazi u eax
    movl 12(%ebp), %ebx         # adresa za rezultat je u ebx

greska:
    cmpl $0, %eax
    jle eror

    # telo funkcije
    movl $1, %ecx
    movl $0, %esi
    movl $0, %ebx

petlja:
    movl %esi, %edx
    addl %ecx, %esi
    jc eror

    movl %edx, %ecx

    addl $1, %ebx
    cmpl %ebx, %eax
    jne petlja

    movl 12(%ebp),%ebx
    movl %esi, (%ebx)

    movl $0, %eax

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret

eror:
    movl $1, %eax

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret

