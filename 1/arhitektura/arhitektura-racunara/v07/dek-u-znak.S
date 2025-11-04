#   uzastopnim deljenjem ulazne vrednosti osnovom odredišnog brojnog sistema i
#   pretvaranjem ostatka svakog deljenja u znakovni ekvivalent (tj. odgovarajuću cifru)

.section .data
    dec_br_max = 10
    dec_br: .fill dec_br_max,1,42
.section .text
.globl main

main:
    movl $1234567, %eax
    leal dec_br, %edi
    movl $10, %ebx                  # baza
    # dakle glavna fora je da delimo br sa 10 i ostatak smestamo u nas string
petlja:
    xorl %edx, %edx         # anuliramo ga jer je za divl par edx:eax
    divl %ebx
    # i taj broj se sad nalazi u dl
    addb $'0', %dl
    movb %dl, (%edi)
    incl %edi

    cmpl $0, %eax
    jne petlja

    movb $0, (%edi)
    incl %edi
    movb $'\n', (%edi)
    decl %edi
    decl %edi
    leal dec_br, %esi

    movl $1, %ebx

    # esi pokazuje na prvi karakter, a edi na poslednji
    # sve to treba switchovati

    # JAE = JGE ALI JAE JE ZA NEOZNACENE

switch:
    cmpl %esi, %edi
    jle ispis

    addl $2, %ebx

    movb (%esi), %dl
    movb (%edi), %dh
    movb %dl, (%edi)
    movb %dh, (%esi)

    decl %edi
    incl %esi
    jmp switch

ispis:
    

    movl %ebx, %edx
    incl %edx
    movl $4, %eax
    movl $1, %ebx
    leal dec_br, %ecx
    int $0x80

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80   