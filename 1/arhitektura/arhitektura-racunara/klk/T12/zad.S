#   autor: Maja Milović INDEX ra69-2024

#   Napisati asemblerski program koji prvo ispisuje poruku input_msg, a nakon toga sa standardnog ulaza učitava
#   string od najviše 30 karaktera, koji se sastoji od malih slova engleskog alfabeta a-z, a završava se karakterom za
#   novi red. Zadatak je simulirati pokvarenu tastaturu, koja svaki put kada se pritisne karakter ‘i’ obrne sve do tada
#   napisane karaktere.  
#   
#   NAPOMENA:  Uneti string će uvek sadržati samo mala slova engleskog alfabeta i nikada neće počinjati
#   karakterom ‘i’. Izlaz ne sme da sadrži karakter ‘i’ jer on samo obrće do tada uneti input, a ne upisuje se u izlaz.
#   
#   Primeri:
#   Unesite string: arhitektura
#   Izlaz: rhatektura   -> moj (maja) komentar: zar ne treba hratektura???

#   Unesite string: arhitekturai
#   Izlaz: arutketarh





# --------------------------------------------------- #
#                                                     #
# previse sam zakomplikovala logiku - NE RADI!!!!!!!! #
#                                                     #
# --------------------------------------------------- #




.section .data
    input_msg: .ascii "Unesite string: \0"
    l_prvi = . - input_msg
    output_msg: .ascii "Izlaz: \0"
    max_len = 30
    str: .ascii "arhimg\0"
    duzina = . - str
    #   str: .fill max_len,1,42
.section .text
.globl main

main:
    movl $4, %eax
    movl $1, %ebx
    leal input_msg, %ecx
    movl $l_prvi, %edx
    int $0x80

    # input stringa
    #   movl $3, %eax
    #   movl $0, %ebx
    #   leal str, %ecx
    #   movl $max_len, %edx
    #   int $0x80

    # sad se u eax nalazi duzina naseg stringa
    # a on sam je u adresi str

    movl $duzina, %eax

    movl $0, %ebx
    movl $str, %ecx

petlja:
    cmpb $'i', (%ecx)
    je obrni_priprema
    incl %ecx
    incl %ebx
    #   movl %ebx, %esi         # esi ce da nam kaze da sve treba da obrnemo duplo manje puta nego sto ima slova do 'i'
    cmpl %eax, %ebx
    jne petlja
    je ispis

obrni_priprema:
    movl %ebx, %edi
    movl %ebx, %esi
    # subl $1, %esi
obrni:
    cmpl $1, %esi
    jle nastavi
    subl $2, %esi
    
    #   decl %ecx
    subl %ebx, %ecx
    decl %ebx
    movb (%ecx), %dl
    movb (%ecx, %ebx, 1), %dh
    movb %dh, (%ecx)
    addl %ebx, %ecx
    movb %dl, (%ecx)
    jmp obrni
    

nastavi:
    # edi sad pokazuje na 'i', a mi i hocemo da izbacimo
    addl %ebx, %ecx
    #   decl %ecx
    movl $0, %ebx
shift:
    #   movl $1, %ebx
    # movl %edi, %ebx     # ebx sad pokazuje na mesto gde je i
    incl %edi           # edi pokazuje na sledece
    movb 1(%ecx), %dh        # sledeci karakter je u dh
    movb %dh, (%ecx)

    #   movl %edi, %ebx
    incl %ebx

    cmpb $0, %dh
    je kraj_shifta

    addl $1, %ecx
    jmp shift

kraj_shifta:
    decl %ecx
    subl %ebx, %ecx
    subl %ebx, %edi
    movl %edi, %ebx
    decl %eax       # smanjimo duzinu stringa za 1
    jmp petlja

    # movl %edi, %ebx
    # addl $1, %ebx
    # addl %ebx, %ecx
    # jmp petlja

ispis:
    movl %eax, %edx
    movl $4, %eax
    movl $1, %ebx
    leal str, %ecx
    #   movl $max_len, %edx
    int $0x80



zavrsetak:
    movl $1, %eax
    movl $0, %ebx
    int $0x80