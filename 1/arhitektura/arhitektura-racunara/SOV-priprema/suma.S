# unos max 30 karaktera, svaka 2 broja su odvojena tacno jednim razmakom
# br moye biti oktalan - minimum 2 cifre, pocinju sa 0, konvertuju se sa brojnom osnovom 8
# moze biti i dec - 1 cifra

# izbrojati koliko ih ima u dec, koliko ih ima u okt i izracunati sumu svih
# sve ispisati ako nema greske

# greske, tj kodovi:
# 0 ako je sve ok
# 1 ako ima char koji nije br u ulaynom
# 2 ako je doslo do prekoracenja prilikom konveryuje iz str u int
# 3 prekoracenje prilikom sume


# Unesite izraz: 1 2 3 + + 999999999999999999999999999 +
# Doslo je do prekoracenja prilikom konverzije nekog od operanada!


# Unesite izraz: 999999999 999999999 999999999 999999999 999999999 999999999 + + + + +
# Doslo je do prekoracenja prilikom sabiranja!



# dodatak na zadatak koji se trazio na klk: stavila sam da moze koliko god treba razmaka.
# ovo se moze izbaciti ako se zakomentarise linija 87


.section .data
    MAX_EL = 30

    unos_str: .ascii "Unesite string: \0"
    unos_l = . - unos_str

    err_1: .ascii "\nUnesen je karakter koji nije broj!\n"
    err_1_l = . - err_1

    err_2: .ascii "Doslo je do prekoracenja prilikom konverzije nekog od operanada!\n"
    err_2_l=.- err_2

    err_3: .ascii "Doslo je do prekoracenja prilikom sabiranja!\n"
    err_3_l=.-err_3

    broj: .long 7

    print_s: .ascii "\nSuma elemenata niza je: "
    s_l = . - print_s
    print_o: .ascii "Broj oktalnih elemenata u nizu: "
    o_l = . - print_o
    print_d: .ascii "Broj decimalnih elemenata u nizu: "
    d_l = . - print_d

    str_suma: .fill 100,1,42
    str_dec: .fill 100,1,42
    str_okt: .fill 100,1,42

    decimalni: .long 0
    oktalni: .long 0
    suma: .long 0

    string: .ascii "0 00     01 1 2 014 14 \n\0"
    # string: .ascii "999999999 999999999 999999999 999999999 999999999 999999999"    # prekoracenje sabiranje
    # string: .ascii "0 1 03 m 999999999999999999999999999 7"   # prekoracenje prilikom konverzije
    # string: .ascii "0 1 03 m 999999999999999999999999999 7"     # Ima karakter koji nije broj

    # 0 00 01 1 2 014 14
    # suma treba da bude 30
    # br oktalnih 3
    # br dec 4
.section .text
.globl main

main:
    leal unos_str, %ecx
    movl $unos_l, %edx
    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp

    leal string, %ecx

karakter:
    movb (%ecx), %dl
    cmpb $'\n', %dl
    je ispisi
    cmpb $' ', %dl
    je razmak
    cmpb $'0', %dl
    jb greska_1
    cmpb $'9', %dl
    ja greska_1

    movb (%ecx), %dl
    cmpb $'0', %dl
    jne nadjen_decimalni

    #   ako se nastavlja znaci da je oktalni
    movb (%ecx), %dl
    cmpb $'0', %dl
    jne greska_1

    pushl %ecx
    movl $8, %ebx
    pushl %ebx
    call str_to_int
    addl $8, %esp

    addl $1, oktalni

    jmp provera_greske

nadjen_decimalni:
    # ulazna adresa broja koji se konvertuje, baza sistema. izlaz je kod greske, tj ebx. u eax ce ostati konvertovana vrednost.
    pushl %ecx
    movl $10, %ebx
    pushl %ebx
    call str_to_int
    addl $8, %esp

    addl $1, decimalni

provera_greske:
    cmpl $2, %ebx
    je greska_2
    cmpl $3, %ebx
    je greska_3

nastavi:
    addl %eax, suma
    incl %ecx
    jmp karakter

razmak:
    incl %ecx
    jmp karakter


greska_1:
    leal err_1, %ecx
    movl $err_1_l, %edx
    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp

    movl $1, %eax
    movl $1, %ebx
    int $0x80


greska_2:
    leal err_2, %ecx
    movl $err_2_l, %edx
    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp

    movl $1, %eax
    movl $2, %ebx
    int $0x80

greska_3:
    leal err_3, %ecx
    movl $err_3_l, %edx
    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp

    movl $1, %eax
    movl $3, %ebx
    int $0x80



ispisi:
    movl suma, %eax
    leal str_suma, %ecx
    pushl %eax
    pushl %ecx
    call int_to_str
    addl $8, %esp

    movl %eax, %esi

    # konvertovali smo broj u string i sad se
    # br karaktera nalazi u eax, a sam string u
    # adresi odredjenoj registrom ecx

    # ispisujemo u oktalnom obliku tako da to nije problem

    leal print_s, %ecx
    movl $s_l, %edx

    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp


    movl %esi, %edx
    leal str_suma, %ecx

    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp
 

    # oktalni

    movl oktalni, %eax
    leal str_okt, %ecx
    pushl %eax
    pushl %ecx
    call int_to_str
    addl $8, %esp

    movl %eax, %esi
    
    
    leal print_o, %ecx
    movl $o_l, %edx

    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp
    
    movl %esi,%edx
    leal str_okt, %ecx

    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp  


    
    # sad decimalni

    movl decimalni, %eax
    leal str_dec, %ecx
    pushl %eax
    pushl %ecx
    call int_to_str
    addl $8, %esp

    movl %eax, %esi
    
    
    leal print_d, %ecx
    movl $d_l, %edx

    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp
    
    
    movl %esi, %edx
    leal str_dec, %ecx

    pushl %ecx
    pushl %edx
    call ispis
    addl $8, %esp 


    # kraj

    movl $1, %eax
    movl $0, %ebx
    int $0x80
    # kraj






ispis:
    pushl %ebp
    movl %esp, %ebp

    pushl %eax
    pushl %ebx
    pushl %edx
    pushl %ecx

    # prvo ce se pushovati vrednost pa onda br slova

    movl 8(%ebp), %edx
    movl 12(%ebp), %ecx
 
    movl $4, %eax
    movl $1, %ebx
    int $0x80

    popl %ecx
    popl %edx
    popl %ebx
    popl %eax

    movl %ebp, %esp
    popl %ebp
    ret



str_to_int:         # ulazna adresa broj koji se konvertuje, baza sistema. dakle suprotnim redom uzimamo ovde u pp. izlaz je kod greske, tj ebx. u eax ce ostati konvertovana vrednost.
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    pushl %edi

    # treba od svakog br oduzeti bajt nule i dodati ga u eax ili na loc gde vec treba da bude taj broj
    # i onda eax pomnoziti bazom sistema i tako u krug
    movl 8(%ebp), %esi  # baza sistema
    movl 12(%ebp), %ecx # tu krece string koji konvertujemo

    xorl %edx, %edx
    xorl %eax, %eax
    xorl %ebx, %ebx

    movl suma, %edi

petlja_tint:
    movb (%ecx), %bl
    cmpb $' ',%bl
    je gotovo_tint
    cmpb $'\n', %bl
    je gotovo_tint
    mull %esi

    subb $'0', %bl
    addl %ebx, %eax
    incl %ecx

    addl %eax, %edi
    jc greska_sab_prekoracenje

    cmpl $0, %edx
    jne greska_prekoracenje_konverzija
    xorl %edx, %edx

    jmp petlja_tint

greska_sab_prekoracenje:
    movl $3, %ebx
    movl $0, %eax
    jmp ocisti_stek_tint

greska_prekoracenje_konverzija:
    movl $2, %ebx
    movl $0, %eax
    jmp ocisti_stek_tint

gotovo_tint:
    movl $0, %ebx

ocisti_stek_tint:    
    popl %edi
    popl %esi

    movl %ebp, %esp
    popl %ebp
    ret




    
int_to_str:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

# prvo je pushovan broj, pa onda adresa za ispis

    movl 8(%ebp), %ecx      # adresa
    movl 12(%ebp), %eax     # broj

    movl $0, %edi           # brojac

    movl $10, %esi          # baza
    xorl %ebx, %ebx

petlja_to_str:
    xorl %edx, %edx

    cmpl $0, %eax
    je obrni_priprema

    divl %esi

    addb $'0', %dl
    movb %dl, (%ecx)

    incl %edi
    incl %ecx
    jmp petlja_to_str

obrni_priprema:
    movb $'\n', (%ecx)
    decl %ecx
    movl 8(%ebp), %ebx

obrni:
    movb (%ebx), %dl
    movb (%ecx), %dh
    movb %dh, (%ebx)
    movb %dl, (%ecx)

    decl %ecx
    incl %ebx

    cmpl %ebx, %ecx
    jg obrni

# izlaz treba da bude u eax i to broj karaktera
# a sam string se smesta u adresu navedenu u argumentu
ocisti_stek:
    incl %edi
    movl %edi, %eax

    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret