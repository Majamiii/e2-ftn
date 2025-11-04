#   Napisati potprogram u asemblerskom jeziku koji implementira deljenje oduzimanjem i
#   pomeranjem:
#   
#       a. C program za ovaj zadatak u dvostrukoj preciznosti, kao i potpis funkcije, dosupni su
#           u .c fajlu u direktorijumu z6_deljenje
#       
#       b. Objašnjenje logike, kao i deo rešenja, dostupni su u praktikumu u glavi 7.4.

#   int deli_bin(unsigned long long a, unsigned long long b,
#              unsigned long long *r);

.section .text
.globl deli_bin

deli_bin:
    pushl %ebp
    movl %esp, %ebp
    pushl %esi
    pushl %edi
    pushl %ebx

# inicijalizacija registara i spremanje za koriscenje

    movl 24(%ebp), %ebx     # ebx = ostatak
    movl $0, (%ebx)         # kolicnik
    movl $0, 4(%ebx)        # visi deo kol

    #   movl 8(%ebp), %esi      # nizi deo prvog
    #   movl 12(%ebp), %edi     # visi deo prvog

    #   movl 16(%ebp), %ebx     # nizi deo drugog
    #   movl 20(%ebp), %ecx     # visi deo drugog

    movl $0, %esi           # nizi deo ostatka
    movl $0, %edi           # visi deo ostatka

    # maska
    movl $0, %eax                  # nizi deo maske
    movl $0x80000000, %edx        # visi deo maske

petlja:
    cmpl  $0, %edx
    jne dalje
    cmpl $0, %eax
    je ocisti_stek
dalje:
    # shl ostatak u dvostrukoj preciznosti
    shll $1, %esi
    rcll $1, %edi
/*
if (maska & a) //kopiranje bita iz a
                ost |= 1; //u ostatak
*/
    testl %eax, 8(%ebp)
    jne dalje_drugi
    testl %edx, 12(%ebp)
    jne dalje_drugi
    orl $1, %esi
    #   movl $0, %edi

dalje_drugi:
/*if (ost >= b) { //ako se b sadrži u tekućem ost
                ost -= b; //oduzmi b od tekućeg ostatka
                kol |= maska;//postavi 1 u količnik
            }
*/
    cmpl 20(%ebp), %edi
    jl dalje_treci
    cmpl 16(%ebp), %esi
    jl dalje_treci
    # ako je ostatak veci od delioca, oduzmi b od rest
    subl 16(%ebp), %esi
    sbbl 20(%ebp), %edi    # borrow

    # kol or maska

    orl %edx, 4(%ebx)
    orl %eax, (%ebx)

#    movl $0, %edi

dalje_treci:
    #   shr maska i onda vracanje na petlju
    shrl $1, %edx
    rcrl $1, %eax
    jmp petlja

ocisti_stek:
    popl %ebx
    popl %edi
    popl %esi
    movl %ebp, %esp
    popl %ebp
    ret


/*

    unsigned int kol,ost,a,b,maska;
    kol = 0;
    ost = 0;
    a = 53;
    b = 5;
    maska = 0x80000000; //početna maska
        while (maska) { //dok se ne obrade svi biti
            ost <<= 1;
            if (maska & a) //kopiranje bita iz a
                ost |= 1; //u ostatak
            if (ost >= b) { //ako se b sadrži u tekućem ost
                ost -= b; //oduzmi b od tekućeg ostatka
                kol |= maska;//postavi 1 u količnik
            }
            maska >>= 1;
    }


*/