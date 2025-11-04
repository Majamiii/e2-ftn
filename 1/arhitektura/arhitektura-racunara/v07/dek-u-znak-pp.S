#   uzastopnim deljenjem ulazne vrednosti osnovom odredišnog brojnog sistema i
#   pretvaranjem ostatka svakog deljenja u znakovni ekvivalent (tj. odgovarajuću cifru)

.section .data
.section .text
.globl znak

znak:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi


    movl 8(%ebp), %eax
    movl 12(%ebp), %edi
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

    movl 12(%ebp), %esi

    movl $1, %ebx

    # esi pokazuje na prvi karakter, a edi na poslednji
    # sve to treba switchovati

    # JAE = JGE ALI JAE JE ZA NEOZNACENE

switch:
    cmpl %esi, %edi
    jle sve_ok

    addl $2, %ebx

    movb (%esi), %dl
    movb (%edi), %dh
    movb %dl, (%edi)
    movb %dh, (%esi)

    decl %edi
    incl %esi
    jmp switch

sve_ok:
    movl $1, %eax

kraj:
    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret