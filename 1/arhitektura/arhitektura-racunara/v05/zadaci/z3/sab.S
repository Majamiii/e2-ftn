#   Napisati potprogram u asembleru kojim se pokomponentno sabiraju dva niza a i b, a rezultat
#   sabiranja smešta se u niz c (c[0] = a[0] + b[0], c[1] = a[1] + b[1], ..., c[n] = a[n] + b[n]):
#       a. Elementi sva tri niza su u dvostrukoj preciznosti
#       b. Zaglavlje funkcije (potprograma) dato je u glavni.c fajlu u Z3 folderu
#       c. Sva tri niza prosleđena su potprogramu kao parametri preneti po adresi
#       d. Potprogram kao povratnu vrednost vraća kod greške; greška nastupa ukoliko dođe
#           do prekoračenja pri sabiranju; potprogram vraća 0 ukoliko nije bilo greške, a bilo šta
#           drugo ukoliko jeste

# int saberi_niz(long long *a, long long *b, long long *c, int n);

#       8(%ebp)  -  pokazivac na niz a
#       12(%ebp)  -  pokazivac na niz b
#       16(%ebp)  -  pokazivac na niz c
#       20(%ebp)  -  kod greske


.section .text
.globl saberi_niz

saberi_niz:
    pushl %ebp
    movl %esp, %ebp

    pushl %edi
    pushl %esi
    pushl %ebx

    movl $0, %ebx   # brojac

# namestanje registara i inicijalizacija
namestanje:
    movl 8(%ebp), %eax
    movl 12(%ebp), %edx
    movl 16(%ebp), %ecx

element:
    #   esi koristimo za nizi deo, edi za visi!

    movl (%eax, %ebx, 8), %esi
    movl 4(%eax, %ebx, 8), %edi

    addl (%edx, %ebx, 8), %esi
    adcl 4(%edx, %ebx, 8), %edi

    jo greska

    movl %esi, (%ecx,%ebx,8)
    movl %edi, 4(%ecx, %ebx, 8)

    incl %ebx
    cmpl 20(%ebp), %ebx
    je bez_greske

    jmp element


greska:
    movl $1, 20(%ebp)
    jmp ocisti_stek

bez_greske:
    movl $0, 20(%ebp)

ocisti_stek:
    movl 20(%ebp), %eax

    popl %ebx
    popl %esi
    popl %edi

    movl %ebp, %esp
    popl %ebp
    ret