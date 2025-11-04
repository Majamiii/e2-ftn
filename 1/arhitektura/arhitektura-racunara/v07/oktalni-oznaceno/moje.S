#   oktalna konverzija - OZNACENI BROJEVI
#   razlika: ukoliko je prvi char 1, onda na prvo mesto stavljamo znak za -
#   ako ne onda nista

# ako je minus onda ce nam i kod obrtanja %esi biti na jednom vise
# tj u registru ecx ce biti 0 ako je pozitivan i 1 ako je negativan i onda cemo to da dodamo na esi

#   and 8000 0000
#   unsigned int inter_to_oct_str(int broj, char* str, int duzina)

.section .text
.globl inter_to_oct_str

inter_to_oct_str:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 8(%ebp), %eax      # koji broj
    movl 12(%ebp), %edi     # gde smestamo adr
    movl $8, %ebx                  # baza
    # dakle glavna fora je da delimo br sa 10 i ostatak smestamo u nas string

znak:
    movl $0x80000000, %ecx
    andl %ecx, %eax

    jz pozitivan
    #   jmp pozitivan

    movb $'-', (%edi)
    incl %edi
    movl $1, %ecx
    movl $0, %esi

    movl 8(%ebp), %eax
    subl 8(%ebp), %eax
    subl 8(%ebp), %eax

    # od nekog negativnog broja 2 puta oduzimamo isti taj broj kako bismo dobili abs vrednost tog broja

    jmp petlja

pozitivan:
    movl 8(%ebp), %eax
    movl $0, %ecx
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

    addl %ecx, %esi         # dodaje 1 ako je negativan i ne dodaje nista ako je pozitivan
    cmpl 16(%ebp), %esi
    jle dalje

    jmp neuspesno

dalje:
    movl 12(%ebp), %esi
    addl %ecx, %esi

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