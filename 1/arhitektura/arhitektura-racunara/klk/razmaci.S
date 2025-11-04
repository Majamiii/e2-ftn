# ukloniti razmake na pocetku i na kraju stringa

.section .data
    s: .ascii "   neki tekst      \0"
.section .text
.globl main

main:
    movl $s, %eax           # u registru eax se nalazi adresa stringa s

dodji_do_kraja:
    cmpl $0, 1(%eax)
    je kraj_razmaci                 # ako je tamo 0 tj kraj stringa onda je kraj
    incl %eax
    jmp dodji_do_kraja

kraj_razmaci:
    movl (%eax),%ebx
    cmpb $' ', (%eax)
    jne nazad_kraj
    decl %eax
    jmp kraj_razmaci

nazad_kraj:
    movl $0,1(%eax)

# sad smo obrisali sve razmake sa kraja!

    movl $s, %eax
    movl %eax, %ecx            # promenljivi pokazivac

pocetak_r:
    cmpb $' ', 1(%ecx)
    jne brisi_p
    incl %ecx
    jmp pocetak_r

brisi_p:                # ebx - brojac razmaka. ecx mesto koje treba da pomerimo. eax mesto na koje treba da pomerimo.
    movb 1(%ecx), %bl
    movb %bl, (%eax)
    incl %eax
    incl %ecx
    cmpl $0, 1(%ecx)
    jne brisi_p
    movl $0, (%eax)

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80