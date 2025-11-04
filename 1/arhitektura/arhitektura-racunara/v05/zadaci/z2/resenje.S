#       Napisati potprogram u asemblerskom jeziku kojim se računa n-ti element Fibonačijevog niza
#       korišćenjem rekurzivnog algoritma. (Detaljnije o rekurzivnom Fibonačijevom algoritmu
#       možete naći na sledećem linku:
#       https://medium.com/launch-school/recursive-fibonnaci-method-explained-d82215c5498e
#       
#       Osnovna ideja jeste da se n-ti element niza računa po formuli:
#       F(n) = F(n-1) + F(n-2), za n > 2 ukoliko se niz indeksira počev od 1, a F(1) = F(2) = 1
#       
#       a. Zaglavlje funkcije (potprograma) dato je u glavni.c fajlu u Z2 folderu

#       b. Potprogram rezultate vraća obrnuto od zadatka 1 – pronađeni n-ti element vraća se
#           kao povratna vrednost potprograma, dok se greška vraća preko parametra prenetog
#           po adresi
#       
#       c. Pomoć – postoje tri važne celine u ovom potprogramu:
#           i. Postavljanje uslova izlaska iz rekurzije – treba ga postaviti na vrhu, kako bi se
#               rekurzija na vreme prekinula; uslov se ogleda u proveri da li je trenutno n >
#               2, i da li treba ulaziti u dalju rekurziju
#           ii. Poziv potprograma za F(n-1)
#           iii. Poziv potprograma za F(n-2) i sabiranje rezultata sa rezultatom poziva F(n-1)
#       
#       d. Napomena: rešenje dostupno na ACS-u ne sadrži kod koji uzima u obzir grešku, pa
#           ga treba proširiti kako bi odgovarao priloženom .c fajlu
#       
#       
#       Napomena: skriptu za testiranje možete pokrenuti tako što joj samo prosledite svoj potprgoram,
#       odnosno .S fajl (ne treba prosleđivati .c fajl) – ./testiraj.sh moje_resenje.S. Ukoliko dobijete grešku
#       koja kaže da nemate privilegije za izvršenje skripte, otvorite terminal u folderu gde je skripta za
#       testiranje i unesite komandu:
#       chmod +x testiraj.sh


#       F(n) = F(n-1) + F(n-2), za n > 2


.section .text
.globl fibonaci

fibonaci:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %eax
    movl 12(%ebp), %ebx

    pushl %ebx
    pushl %eax
    call rekurzija

    addl $8, %esp

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret

rekurzija:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %eax
    movl 12(%ebp), %ebx

    movl $0, %edx

    cmpl $2, %eax
    jle vracaj

    call rekurzija
    addl %eax, %edx
    decl %eax
    call rekurzija
    addl %eax, %edx
    xchgl %eax, %edx

    movl %edx, (%ebx)
    
    
    jmp k_funkc

vracaj:
    movl $1, (%ebx)

k_funkc:
    movl $0, %eax

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret

    