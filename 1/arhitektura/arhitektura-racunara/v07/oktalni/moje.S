#   uzastopnim deljenjem ulazne vrednosti osnovom odredišnog brojnog sistema i
#   pretvaranjem ostatka svakog deljenja u znakovni ekvivalent (tj. odgovarajuću cifru)

#   unsigned int inter_to_oct_str(unsigned int broj, char* str, int duzina)

.section .text
.globl inter_to_oct_str

inter_to_oct_str:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %eax
    movl 12(%ebp), %edi
    movl $8, %ebx                  # baza
    # dakle glavna fora je da delimo br sa 10 i ostatak smestamo u nas string

    movl $0, %esi
petlja:
    xorl %edx, %edx         # anuliramo ga jer je za divl par edx:eax
    divl %ebx
    # i taj broj se sad nalazi u dl
    addb $'0', %dl
    movb %dl, (%edi)
    incl %edi

    incl %esi       # brojac znakova

    cmpl $0, %eax
    jne petlja

    # --------------   gotova petlja  ----------------

    movb $0, (%edi)
    decl %edi
    incl %esi
    movl %esi, %ebx

    cmpl 16(%ebp), %esi
    jle dalje

    jmp neuspesno

dalje:
    movl 12(%ebp), %esi

    # esi pokazuje na prvi karakter, a edi na poslednji
    # sve to treba switchovati

    # JAE = JGE ALI JAE JE ZA NEOZNACENE

switch:
    cmpl %esi, %edi
    jle sve_ok

    movb (%esi), %dl
    movb (%edi), %dh
    movb %dl, (%edi)
    movb %dh, (%esi)

    decl %edi
    incl %esi
    jmp switch

neuspesno:  
    movl $1, %eax
    jmp kraj

sve_ok:
    movl $0, %eax

kraj:
    popl %edi
    popl %esi
    popl %ebx

    movl %ebp, %esp
    popl %ebp
    ret