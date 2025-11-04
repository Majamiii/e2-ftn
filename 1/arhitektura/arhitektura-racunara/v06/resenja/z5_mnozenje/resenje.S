#   Napisati potprogram u asemblerskom jeziku koji implementira množenje sabiranjem i
#   pomeranjem:

#       a. C program za ovaj zadatak u dvostrukoj preciznosti, kao i potpis funkcije, dostupni su
#           u .c fajlu u direktorijumu z5_mnozenje
#       
#       b. Objašnjenje logike, kao i deo rešenja (deo sa glavnom logikom), dostupni su u
#           praktikumu u glavi 7.3

#   potprogram za množenje pomoću šiftovanja

#   int mnozi_bin(unsigned long long a, unsigned long long b,
#                 unsigned long long *r);


# program stavlja kod greske u eax a resenje u r

.section .text
.globl mnozi_bin

mnozi_bin:
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    pushl %edi
    pushl %ebx

    movl 24(%ebp), %edx     # eax = r
    movl $0, (%edx)         # nizi deo = 0
    movl $0, 4(%edx)        # visi deo = 0

    movl 8(%ebp), %esi      # nizi deo prvog
    movl 12(%ebp), %edi     # visi deo prvog

    movl 16(%ebp), %ebx     # nizi deo drugog
    movl 20(%ebp), %ecx     # visi deo drugog

    cmpl $0, %esi
    je nastavi_proveru
    jmp algoritam

nastavi_proveru:
    cmpl $0, %edi
    je nula

#   ALGORITAM

algoritam:
    cmpl $0, %ebx
    je provera_drugi
nastavak:
    testl $1, %ebx
    jne dodaj
petlja_dalje:
    # pomeri a ulevo (dvostruka preciznost)
    shll $1, %esi
    rcll $1, %edi

    # shiftovanje u dvostrukoj preciznosti
    shrl $1, %ecx
    rcrl $1, %ebx
    jmp algoritam

# --------------

dodaj:      # r = r+a
    addl %esi, (%edx)
    adcl %edi, 4(%edx)
    jmp petlja_dalje

provera_drugi:
    cmpl $0, %ecx
    je kraj
    jmp nastavak

nula:
    movl $0, (%edx)
    movl $0, 4(%edx)
    jmp ocisti_stek

kraj:
    movl $0, %eax

ocisti_stek:
    popl %ebx
    popl %edi
    popl %esi

    movl %ebp, %esp
    popl %ebp
    ret
