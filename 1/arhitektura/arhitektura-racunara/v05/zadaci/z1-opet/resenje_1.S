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


#       Napomena: skriptu za testiranje možete pokrenuti tako što joj samo prosledite svoj potprgoram,
#       odnosno .S fajl (ne treba prosleđivati .c fajl) – ./testiraj.sh moje_resenje.S. Ukoliko dobijete grešku
#       koja kaže da nemate privilegije za izvršenje skripte, otvorite terminal u folderu gde je skripta za
#       testiranje i unesite komandu:
#       chmod +x testiraj.sh


.section .text
.globl fibonaci

#   int fibonaci(int n, unsigned int* rez);

fibonaci:
    pushl %ebp              #   čuvanje zatečenog FP-a
    movl %esp, %ebp         #   postavljanje novog FP-a
    #   subl $8, %esp           # prostor za lokalnu promenljivu

    pushl %ebx              # cuvanje vr registara ebx, esi, edi kako bi
    pushl %esi              # bili slobodni za koriscenje
    pushl %edi

    movl 8(%ebp), %eax       # u eax se nalazi n
    movl 12(%ebp), %ecx      # u ecx se nalazi adresa za rezultat

    cmpl $0, %eax
    jle greska

    movl $1, %edx           # inicijalizacija
    movl $1, %ebx
    jmp petlja


petlja:
# eax je poput provere za brojac, edx je za vrednost, pa cemo to kasnije sve staviti na adresu ecx

    addl %ebx, %edx

    xchgl %ebx, %edx
    decl %eax

    cmpl $2, %eax
    jle nastavi

    addl %ebx, %edx
    jc greska
    subl %ebx, %edx

nastavi:
    cmpl $1, %eax
    jne petlja

    movl %edx, (%ecx)
    movl $0, %eax

    jmp kraj

greska:
    movl $1, %eax

kraj:
    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp         #   brisanje lokalne promenljive
    popl %ebp               # vraćanje prethodnog FP-a
    ret

    