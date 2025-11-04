# Student: miami lovich

#   Unesite namirnice: 
#   Jaja: P-26 C-2 F-22,Hleb: P-18 C-100 F-7,Meso: P-90 C-0 F-20,Kikiriki: P-13 
#   C-10 F-25,Pirinac: P-5 C-56 F-1
#   Ukupno kalorija: 1955
#   Protein: 152g
#   Ugljeni-hidrati: 168g
#   Masti: 75g
#   Izlazni kod: 0

.section .data
    poruka_unos: .ascii "Unesite namirnice:\n"
    unos_l = . - poruka_unos
    poruka_greska: .ascii "Pogresna oznaka makro-nutrijenta.\n"
    greska_l = . - poruka_greska
    poruka_kalorije: .ascii "Ukupno kalorija: "
    kalorije_l = . - poruka_kalorije
    poruka_p: .ascii "Protein: "
    protein_l = . - poruka_p
    poruka_c: .ascii "Ugljenih-hidrati: "
    carbo_l = . - poruka_c
    poruka_f: .ascii "Masti: "
    fats_l = . - poruka_f

    #   korisnicki_unos: .ascii "Jaja: P-26 C-2 F-22,Hleb: P-18 C-100 F-7,Meso: P-90 C-0 F-20,Kikiriki: P-13 C-10 F-25,Pirinac: P-5 C-56 F-1\n"
    korisnicki_unos: .fill MAX_LEN,1,42
    proba_str: .fill 100,1,42
    proba_int: .long 1407

    proteini: .long 0
    masti: .long 0
    kalorije: .long 0
    hidrati: .long 0

    proteini_ispis: .fill 100,1,42
    masti_ispis: .fill 100,1,42
    hidrati_ispis: .fill 100,1,42
    kalorije_ispis: .fill 100,1,42

    str: .ascii "333\n"

    MAX_LEN = 1000
.section .text
.globl main

main:
    movl $4, %eax
    movl $1, %ebx
    movl $poruka_unos, %ecx
    movl $unos_l, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    leal korisnicki_unos, %ecx
    movl $MAX_LEN, %edx
    int $0x80

do_dvotacke:
    movb (%ecx), %dl
    cmpb $':', %dl
    je parsiraj_string
    cmpb $'\n', %dl
    je uspesan_kraj
    cmpb $'\0', %dl
    je uspesan_kraj
    incl %ecx
    jmp do_dvotacke

parsiraj_string:
    addl $2, %ecx   # za razmak i za dvotacku
    movb (%ecx), %dl

    cmpb $'P', %dl
    jne pogresan_unos

    addl $2, %ecx
    pushl %ecx
    call str_to_int
    addl $4, %esp

    addl %eax, proteini     # broj proteina

    movl $4, %ebx
    mull %ebx
    addl %eax, kalorije

    addl $1, %ecx
    movb (%ecx), %dl

    cmpb $'C', %dl
    jne pogresan_unos

    addl $2, %ecx
    pushl %ecx
    call str_to_int
    addl $4, %esp

    addl %eax, hidrati     # broj masti

    movl $4, %ebx
    mull %ebx
    addl %eax, kalorije

    
    addl $1, %ecx
    movb (%ecx), %dl

    cmpb $'F', %dl
    jne pogresan_unos

    addl $2, %ecx
    pushl %ecx
    call str_to_int
    addl $4, %esp

    addl %eax, masti     # broj masti

    movl $9, %ebx
    mull %ebx
    addl %eax, kalorije

    # sve smo uneli sto treba
    movb (%ecx), %dl
    cmpb $',', %dl
    je do_dvotacke
    cmpb $'\n', %dl
    je ispis_kalorija

    jmp uspesan_kraj        # mada trebalo bi da nikad ne dodje do ovog

ispis_kalorija:
    #   poruka_kalorije: .ascii "Ukupno kalorija: "
    #   kalorije_l = . - poruka_kalorije
    movl $4, %eax
    movl $1, %ebx
    leal poruka_kalorije, %ecx
    movl $kalorije_l, %edx
    int $0x80

    leal kalorije_ispis, %ecx
    movl kalorije, %eax
    pushl %eax  # broj
    pushl %ecx
    call int_to_str
    addl $8, %esp

    movl %eax, %edx         # br slova
    movl $kalorije_ispis, %ecx
    movl $4, %eax
    movl $1, %ebx
    int $0x80



    # sada ide ispis ostalih nutrijenata

    movl $4, %eax
    movl $1, %ebx
    leal poruka_p, %ecx
    movl $protein_l, %edx
    int $0x80

    leal proteini_ispis, %ecx
    movl proteini, %eax
    pushl %eax  # broj
    pushl %ecx
    call int_to_str
    addl $8, %esp
    movl %eax, %edx         # br slova

    decl %ecx
    movb $'g', (%ecx)
    incl %edx
    incl %ecx
    movb $'\n', (%ecx)

    movl $proteini_ispis, %ecx
    movl $4, %eax
    movl $1, %ebx
    int $0x80

    # hidrati

    movl $4, %eax
    movl $1, %ebx
    leal poruka_c, %ecx
    movl $carbo_l, %edx
    int $0x80

    leal hidrati_ispis, %ecx
    movl hidrati, %eax
    pushl %eax  # broj
    pushl %ecx
    call int_to_str
    addl $8, %esp
    movl %eax, %edx         # br slova

    decl %ecx
    movb $'g', (%ecx)
    incl %edx
    incl %ecx
    movb $'\n', (%ecx)

    movl $hidrati_ispis, %ecx
    movl $4, %eax
    movl $1, %ebx
    int $0x80

    # masti

    movl $4, %eax
    movl $1, %ebx
    leal poruka_f, %ecx
    movl $fats_l, %edx
    int $0x80

    leal masti_ispis, %ecx
    movl masti, %eax
    pushl %eax  # broj
    pushl %ecx
    call int_to_str
    addl $8, %esp
    movl %eax, %edx         # br slova

    decl %ecx
    movb $'g', (%ecx)

    movl $masti_ispis, %ecx
    movl $4, %eax
    movl $1, %ebx
    int $0x80



    jmp uspesan_kraj
/*
    movl $0, %ecx
    leal str, %ecx

    pushl %ecx
    call str_to_int
    addl $4, %esp

    movl $2, %ebx
    mull %ebx

    leal proba_str, %ecx
    pushl %eax  # broj
    pushl %ecx
    call int_to_str
    addl $8, %esp

    movl %eax, %edx         # br slova
    movl $proba_str, %ecx
    movl $4, %eax
    movl $1, %ebx
    int $0x80
*/
pogresan_unos:


    #   poruka_greska: .ascii "Pogresna oznaka makro-nutrijenta.\n"
    #   greska_l = . - poruka_greska
# dodati za adekvatan ispis
    movl $4, %eax
    movl $1, %ebx
    leal poruka_greska, %ecx
    movl $greska_l, %edx
    int $0x80
    jmp kraj

neuspesan_kraj:
    movl $1, %ebx
    jmp kraj

uspesan_kraj:
    movl $0, %ebx

kraj:
    movl $1, %eax
    int $0x80


int_to_str:
    pushl %ebp
    movl %esp, %ebp

    movl $10, %ebx
    movl 8(%ebp), %ecx      # tu upisujemo
    movl 12(%ebp), %eax     # tu se nalazi broj

    pushl %esi      # brojac slova
    movl $1, %esi

    xorl %edx, %edx

petlja_to_str:
    cmpl $0, %eax
    je obrni

    divl %ebx
    addl $'0', %edx
    movb %dl, (%ecx)
    incl %ecx
    incl %esi

    xorl %edx, %edx

    jmp petlja_to_str

obrni:
    movb $'\n', (%ecx)
    movl 8(%ebp), %ebx
    decl %ecx

nastavi_obrni:
    cmpl %ebx, %ecx
    jle kraj_to_str

    movb (%ebx), %dh
    movb (%ecx), %dl
    movb %dl, (%ebx)
    movb %dh, (%ecx)

    incl %ebx
    decl %ecx

    jmp nastavi_obrni

kraj_to_str:
    movl 8(%ebp), %ecx
    addl %esi, %ecx     # sad on pokazuje na poslednji - pa da tako i ostane
    movl %esi, %eax         # brojac slova se vraca
    popl %esi
    movl %ebp, %esp
    popl %ebp
    ret


str_to_int:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi

    movl $10, %ebx
    movl 8(%ebp), %ecx  # adresa stringa

    xorl %eax, %eax

petlja_to_int:
    xorl %edx, %edx
    movb (%ecx), %dl

    cmpb $'0', %dl
    jl kraj_to_int
    cmpb $'9', %dl
    jg kraj_to_int

    xorl %edx, %edx
    mull %ebx

    movb (%ecx), %dl

    subb $'0', %dl
    addl %edx, %eax

    incl %ecx

    jmp petlja_to_int

kraj_to_int:
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret