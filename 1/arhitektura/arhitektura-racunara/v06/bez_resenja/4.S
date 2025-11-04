#       Potprogram koji postavlja proizvoljni bit podatka na 1 ili 0 (uraditi i za jednostruku i za
#       dvostruku preciznost)

#   int prebaci(long long broj, int pozicija, int vrednost);

#       (ukoliko je povratna
#       vrednost 64-bitna, smešta se u registarski par edx:eax, gde edx predstavlja viših 32 bita, a
#       eax nižih 32 bita vrednosti).

.section .text
.globl prebaci

prebaci:
    pushl %ebp
    movl %esp, %ebp

    pushl %edi
    pushl %esi
    pushl %ebx

    movl 8(%ebp), %eax      # nizi deo br je u eax
    movl 12(%ebp), %edx     # visi deo br je u edx

    #   16(%ebp) je pozicija
    #   20(%ebp) je u sta prebacujemo

    cmpl $32, 16(%ebp)      # gledamo koji deo se menja
    jg visi

    #   ako nije visi onda menjamo nizi
    decl 16(%ebp)           # npr kad je pozicija 3 onda shiftujemo za 2
    movl 16(%ebp), %ecx     # pozicija je u ecx
    
    cmpl $0, 20(%ebp)
    je nula_nizi
    
# ako nije nula onda se postavlja na 1
    movl $0x00000001, %ebx     #   1111...110    je u    ebx
    shll %ecx, %ebx

    orl %ebx, %eax              # sto je bilo 1 ostace 1, sto je bilo 0 ostace 0, ali na tom mestu ce biti 1 sigurno

    jmp ocisti_stek

nula_nizi:
    movl $0xfffffffe, %ebx     #   1111...110    je u    ebx
    shll %ecx, %ebx
    
    andl %ebx, %eax
    jmp ocisti_stek

visi:
    movl 16(%ebp), %ecx     # pozicija je u ecx
    subl $32, %ecx
    
    cmpl $0, 20(%ebp)
    je nula_visi

# ako nije nula onda se postavlja na 1
    movl $0x00000001, %ebx     #   1111...110    je u    ebx
    shll %ecx, %ebx

    orl %ebx, %edx              # sto je bilo 1 ostace 1, sto je bilo 0 ostace 0, ali na tom mestu ce biti 1 sigurno

    jmp ocisti_stek

nula_visi:
#   Na primer, ako treba najniži bit registra eax postaviti na 0, to se može postići
#   naredbom:
#   andl $0xfffffffe, %eax

    movl $0xfffffffe, %ebx     #   1111...110    je u    ebx
    shll %ecx, %ebx
    
    andl %ebx, %edx             # gde je bila 1 ostace 0, gde je bilo 0 ostace 0, ali na tom mestu ce biti 0

ocisti_stek:
    popl %ebx
    popl %esi
    popl %edi

    movl %ebp, %esp
    popl %ebp
    ret