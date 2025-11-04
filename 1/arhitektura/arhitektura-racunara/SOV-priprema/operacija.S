#       Priprema SOV:
#       Napisati asemblerski program koji predstavlja kalkulator logičkih operacija za 8-bitne brojve. 
#       Korisnik u program unosi jedan string maksimalne dužine 100 karaktera koji sadrži logički izraz oblika:
#       
#       operandi operacijal operand2 operacija2 operand3
#       
#       gde su operandi 8-bitne neoznačene vrednosti, a operacije jedan od binarnih logičkih operacija iz 
#       skupa [“^","<",">”] (isključivo ili, rotacija ulevo, rotacija udesno). 
#       Podrazumevati da će minimalno biti unesena dva operanda i jedna operacija između njih, dok se iza 
#       toga može nalaziti proizvoljan broj dodatnh operacija i oprantada. Smatrati da će se izmedu nizova 
#       znakova koji čine operande i operacije nalaziti tačno jedan razmak i da će broj takvih nizova znakova 
#       uvek biti neparan. Takođe, smatrati da se na početku i na kraju stringa neće unositi razmaci.
#       
#       Operandi se mogu zadati u dekadnom (npr. 123) ili heksadecimalnom (npr. 0x1f) obliku ("x" za heksadecimalni zapis može biti malo ili veliko slovo).
#       
#       Računanje logičkog izraza ide s leva u desno, bez prioriteta operacija. 
#       Ukoliko prilikom računanja izraza nije bilo greške, rezultat treba ispisati u oktalnom brojnom sistemu. 
#       Ako se desi greška prilikom rada programa, prekinuti njegovo izvršavanje i ispisati poruku o grešci. 
#       
#       Ako se desi greška kod prepoznavanja operanda, ispisati string err1. 
#       Ako se desi greska kod prepoznavanja operacije, ispisati string err2. 
#       Izlazni kod programa treba da bude 0 ako greške nije bilo, a 1 ako jeste.
#       
#       Primeri korišćenja:
#       
#       Unseite logicki izraz: 0xff < 36 0x6A > 11
#       Rezultat: 262
#       
#       Unseite logicki izraz: 123 A 3f
#       Greska kod operanda.
#       
#       Za kompletno odraden zadatak se dobija 30 poena.
#       Bodovanje zadataka će u velikoj meri zavisiti od procenta uspešnih testova.
#       Napomena: ukoliko testovi koji ne treba da izazovu grešku ne prolaze, testovi koji treba da izazovu grešku se ne uzimaju kao validni.
#       Pored testova koji su unapred dati (automatizovano testiranje sa ./testiraj.sh zad.S), prilikom pregledanja rešenje će se testirati sa 
#       još dodatnih testova, te je potrebno testirati i sa drugim ulazima. Napomena: testiraj. sh ima smisla pokretati tek kada je zadatak završen.


.section .data
    operand: .byte 0
    rezultat: .byte 0

    # unos: .ascii "Unesite logicki izraz: \0"
    # unos_l = . - unos

    err1: .ascii "Greska kod operanda.\n"
    err1_l = . - err1
    err2: .ascii "Greska kod operacije.\n"
    err2_l = . - err2

    rez_tekst: .ascii "Rezultat: \0"
    rez_tekst_l = . - rez_tekst

    decimalni: .ascii "0xff * 1\n"

    ispis: .fill 50,1,42



.section .text
.globl main

main:
    # ispis teksta "rezultat:"
    movl $4, %eax
    movl $1, %ebx
    leal rez_tekst, %ecx
    movl $rez_tekst_l, %edx
    int $0x80

    # inicijalno stavljanje prvog operanda u rezultat

    pushl $decimalni
    call str_to_int
    addl $4, %esp

    cmpl $1, %ebx
    je greska_operand

    movb %al, rezultat

nova_operacija:
    movb (%ecx), %bl
    cmpb $'^', %bl
    je ksoruj
    cmpb $'<', %bl
    je rot_l
    cmpb $'>', %bl
    je rot_d
    cmpb $'\n', %bl
    je ispisi
    incl %ecx
    cmpb $' ', %bl
    je nova_operacija
    jne greska_operacija

ksoruj:
    addl $2, %ecx

    pushl %ecx
    call str_to_int
    addl $4, %esp

    cmpl $1, %ebx
    je greska_operand

    # u al se nalazi operand
    movb rezultat, %bl
    xorb %al, %bl
    movb %bl, rezultat
    jmp nova_operacija


rot_l:
    addl $2, %ecx

    pushl %ecx
    call str_to_int
    addl $4, %esp
    
    cmpl $1, %ebx
    je greska_operand

    movl %ecx, %esi

    # u al se nalazi operand
    movb %al, %cl
    movb rezultat, %bl
    rolb %cl, %bl
    movb %bl, rezultat

    movl %esi, %ecx
    jmp nova_operacija

rot_d:
    addl $2, %ecx

    pushl %ecx
    call str_to_int
    addl $4, %esp
    
    cmpl $1, %ebx
    je greska_operand

    movl %ecx, %esi

    # u al se nalazi operand
    movb %al, %cl
    movb rezultat, %bl
    rorb %cl, %bl
    movb %bl, rezultat

    movl %esi, %ecx
    jmp nova_operacija

ispisi:
    # konverzija rezultata iz inta u string
    xorl %eax, %eax
    movb rezultat, %al
    leal ispis, %ecx
    # prvo se pushuje broj pa onda adresa za ispis
    pushl %eax
    pushl %ecx
    call int_to_str
    addl $8, %esp

    # ispis rezultata
    movl %eax,%edx
    movl $4, %eax
    movl $1, %ebx
    leal ispis, %ecx
    int $0x80

    jmp kraj

greska_operand:
    movl $4, %eax
    movl $1, %ebx
    leal err1, %ecx
    movl $err1_l, %edx
    int $0x80
    jmp kraj_greska

greska_operacija:
    movl $4, %eax
    movl $1, %ebx
    leal err2, %ecx
    movl $err2_l, %edx
    int $0x80

kraj_greska:
    movl $1, %eax
    movl $1, %ebx
    int $0x80

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80


pp:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret


str_to_int:
    # jedini ulaz je adresa stringa
    # izlaz je u ebx - kod greske, ako je ima
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    pushl %edi

    movl $0, %eax
    movl 8(%ebp), %ecx
    xorl %edx, %edx
    movl $10, %esi
    movl $0, %ebx

    movb (%ecx), %bl
    cmpb $'0', %bl
    je proveri_heksa

petlja_toi:
    movb (%ecx), %bl
    cmpb $' ', %bl
    je stek_toi
    cmpb $'\n', %bl
    je stek_toi
    cmpb $'0', %bl
    jb greska_operand_pp
    cmpb $'9', %bl
    ja greska_operand_pp

    mull %esi

    subb $'0', %bl
    addl %ebx, %eax

    incl %ecx

    movl $0, %ebx
    jmp petlja_toi

proveri_heksa:
    incl %ecx
    movb (%ecx), %bl
    cmpb $'x', %bl          # treba dodati da moze i veliko slovo
    jne petlja_toi

    movl $16, %esi
    incl %ecx

heksa_konverzija:
    movb (%ecx), %bl
    cmpb $' ', %bl
    je stek_toi
    cmpb $'\n', %bl
    je stek_toi
    cmpb $'0', %bl
    jb greska_operand_pp
    cmpb $'9', %bl
    jbe heksa_decimalni
    cmpb $'A', %bl
    jb greska_operand_pp
    cmpb $'Z', %bl
    jbe heksa_cifra_veliko
    cmpb $'a', %bl
    jb greska_operand_pp
    cmpb $'z', %bl
    jbe heksa_cifra_malo
    jmp greska_operand_pp

heksa_decimalni:
    mull %esi

    subb $'0', %bl
    addl %ebx, %eax

    incl %ecx

    movl $0, %ebx
    jmp heksa_konverzija

heksa_cifra_veliko:
    mull %esi

    subb $'A', %bl
    addl %ebx, %eax
    addl $10, %eax

    incl %ecx

    movl $0, %ebx
    jmp heksa_konverzija

heksa_cifra_malo:
    mull %esi

    subb $'a', %bl
    addl %ebx, %eax
    addl $10, %eax

    incl %ecx

    movl $0, %ebx
    jmp heksa_konverzija

greska_operand_pp:
    movl $1, %ebx

stek_toi:
    popl %edi
    popl %esi

    movl %ebp, %esp
    popl %ebp
    ret



int_to_str:
#   prvo se pushuje broj pa onda adresa za ispis
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    xorl %eax, %eax

    movl 8(%ebp), %ecx
    movb 12(%ebp), %al

    xorl %edx, %edx
    xorl %ebx, %ebx
    movl $8, %esi
    movl $0, %edi       # brojac

petlja_tos:
    cmpb $0, %al
    je obrni_priprema

    xorl %edx, %edx
    divl %esi
    addb $'0', %dl
    movb %dl, (%ecx)

    incl %edi
    incl %ecx
    jmp petlja_tos

obrni_priprema:
    movl 8(%ebp), %ebx
    incl %edi
    movb $'\n', (%ecx)
    decl %ecx

obrni:
    movb (%ebx), %dl
    movb (%ecx), %dh
    movb %dh, (%ebx)
    movb %dl, (%ecx)

    decl %ecx
    incl %ebx

    cmpl %ebx, %ecx
    ja obrni

stek_tos:
    movl %edi, %eax

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret