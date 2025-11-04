#   Napisati potprogram u asembleru kojim se pokomponentno sabiraju dva niza a i b, a rezultat
#   sabiranja smešta se u niz c (c[0] = a[0] + b[0], c[1] = a[1] + b[1], ..., c[n] = a[n] + b[n]):
#       a. Elementi sva tri niza su u dvostrukoj preciznosti
#       b. Zaglavlje funkcije (potprograma) dato je u glavni.c fajlu u Z3 folderu
#       c. Sva tri niza prosleđena su potprogramu kao parametri preneti po adresi
#       d. Potprogram kao povratnu vrednost vraća kod greške; greška nastupa ukoliko dođe
#           do prekoračenja pri sabiranju; potprogram vraća 0 ukoliko nije bilo greške, a bilo šta
#           drugo ukoliko jeste

# int saberi_niz(long long *a, long long *b, long long *c, int n);

.section .text
.globl saberi_niz

saberi_niz:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl $0, %ebx       # ebx je brojac od 0 do n-1
    movl 20(%ebp), %ecx     # u ecx je n, broj elemenata

petlja:
    cmpl %ecx, %ebx
    jge kraj

# Uzimanje adresa: a[i], b[i], c[i]
    movl 8(%ebp), %esi      # esi = a
    movl 12(%ebp), %edi      # edi = b

    movl (%esi,%ebx,8), %eax
    movl 4(%esi, %ebx,8), %edx

    addl (%edi, %ebx, 8), %eax
    adcl 4(%edi, %ebx,8), %edx
    
    jo overflow
    
    movl 16(%ebp), %edi     # edi = c
    movl %eax, (%edi, %ebx,8)
    movl %edx, 4(%edi, %ebx,8)

    incl %ebx
    jmp petlja


overflow:
    movl $1, %eax          # vrati kod greške 1
    jmp izadji

kraj:
    movl $0, %eax          # uspešno sabiranje

izadji:
    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret


