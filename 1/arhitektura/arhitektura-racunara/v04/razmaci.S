.section .data
    s: .ascii " abcd \0"
.section .text
.globl main

main:
    movl $s, %eax           # početna adresa stringa u %eax
kraj_s:                     #   određivanje kraja stringa
    cmpb $0, (%eax)         #   da li se na tekućoj poziciji nalazi NUL?
    je razmaci
    incl %eax               #   ako ne, uvećaj %eax
    jmp kraj_s
razmaci:                    #   određivanje broja razmaka koje treba izbaciti
    cmpb $' ', -1(%eax)     #   da li se na poziciji ispred tekuće nalazi
                            #   znak različit od razmaka?
    jne izbaci
    decl %eax               #   ako ne, umanji %eax
    jmp razmaci
izbaci:
    movb $0, (%eax)         #   upisivanje NUL znaka iza poslednjeg znaka
                #   koji je različit od razmaka
    movl $s, %eax
    movl $0, %ebx
pocetak:
    cmpb $' ', (%eax)
    jne indent
    incl %eax
    addl $1, %ebx
    jmp pocetak
indent:
    movl %eax, %ecx
    subl %ebx, %eax
nastavak:
    movb (%ecx), %dl
    movb %dl, (%eax)

    cmpb $0, %dl`
    je kraj

    incl %ecx
    incl %eax
    jmp nastavak
kraj:
    movb $0, %dl
    movb %dl, (%eax)
    movl $1, %eax
    movl $0, %ebx
    int $0x80


#       Adresiranje -1(%eax) znači da se posmatra lokacija sa adresom koja je za 1 manja od
#   vrednosti %eax registra (kod stringova, jedan element niza zauzima 1 bajt)