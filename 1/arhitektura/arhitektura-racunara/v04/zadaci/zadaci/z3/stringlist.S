.section .data
    str_unos:   .ascii "Unesite string:\0"
    unos_len = . - str_unos
    str_ispis:  .ascii "\nObrnuti redosled:\n\0"
    ispis_len = . - str_ispis
    str_len = 21    # dužina jednog stringa (20 znakova + Enter)
    str_num = 10    # broj stringova
    str_lens: .fill str_num,4,0
    strings: .fill str_len*str_num,1,42
.section .text
.globl main

#    adr_elementa = strings + indeks * str_len

main:
    movl $0, %esi       # brojac

unos:
    movl $4, %eax
    movl $1, %ebx
    leal str_unos, %ecx
    movl $unos_len, %edx
    int $0x80
    # ispisali smo ono Unesi string:

    movl $0, %ebx
    movl $str_len, %ecx
    movl %esi, %eax
    mull %ecx
    movl %eax, %edx
    leal strings, %ecx
    addl %edx, %ecx
    #   addl $strings, %ecx
    movl $3, %eax
    movl $str_len, %edx
    int $0x80

    #   duzinu unetog stringa treba sacuvati na str_lens, duzina je 4 a indeks preko esi
    movl $str_lens, %ebx
    movl %eax, (%ebx, %esi, 4)


    incl %esi
    cmpl $str_num, %esi
    jne unos
    #   jmp kraj

    movl $str_num, %edi
    decl %edi
ispis:
    movl $4, %eax
    movl $1, %ebx
    leal str_ispis, %ecx
    movl $ispis_len, %edx
    int $0x80
    # ispisali smo ono Obrnuti redosled:

redosled:
    movl $1, %ebx
    movl $str_len, %ecx
    movl %edi, %eax
    mull %ecx
    movl %eax, %edx
    leal strings, %ecx
    addl %edx, %ecx
    #   addl $strings, %ecx
    movl $4, %eax
    #   movl $str_len, %edx

    movl $str_lens, %esi
    movl (%esi, %edi, 4), %edx

    int $0x80


    decl %edi
    cmpl $0, %edi
    jge redosled

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80
