#   Napraviti potprogram int palindrom(char *str) koji proverava da li je string palindrom.
#   Ako jeste, vratiti 1, u suprotnom vratiti 0.


#   int palindrom(char *str);

.section .text
.globl palindrom

palindrom:
    pushl %ebp
    movl %esp, %ebp

    # oslobadjamo ova 3 registra za koriscenje
    pushl %esi
    pushl %edi
    pushl %ebx

    movl 8(%ebp), %esi      # u ESI se nalazi adresa naseg stringa

    movl $0, %edi           # u edi je brojac za karaktere, koji ce se posle vracati do 0
    movl $0, %ebx           # u ebx idemo od prvog do poslednjeg
    
duzina:
    movb (%esi, %edi, 1), %al

    cmpb $0, %al
    je provera1
    incl %edi
    jmp duzina

provera1:
    decl %edi
provera:
    movb (%esi, %edi, 1), %al
    movb (%esi, %ebx, 1), %cl
    
    cmpb %al, %cl
    jne greska_ili_nije
    decl %edi
    incl %ebx

    cmpl %edi, %ebx
    jg jeste_kraj

    jmp provera

greska_ili_nije:
    movl $0, %eax
    jmp ocist_stek

jeste_kraj:
    movl $1, %eax

ocist_stek:
    popl %ebx
    popl %edi
    popl %esi

    movl %ebp, %esp
    popl %ebp
    ret


