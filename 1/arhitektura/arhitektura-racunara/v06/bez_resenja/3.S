#   Potprogram koji prebrojava jedinice, odnosno nule, u 64-bitnom broju

.section .text
.globl jedinice

#   int jedinice(long long n);

jedinice:
    pushl %ebp
    movl %esp, %ebp
    pushl %esi
    pushl %edi
    pushl %ebx

    movl $0, %ebx
    movl 8(%ebp), %esi      # low deo broja
    movl 12(%ebp), %edi      # high deo broja

    # 32-bitna maska sa nulama jedinicama do poslednjeg - hex - 8 cifara kod kojih je poslednja 1
    movl $0x00000001, %ecx

petlja_low:
    movl %esi, %eax          # vracamo uvek u eax prvobitni broj, jer se kasnije tamo nalazi rezultat anda
    andl %ecx, %eax
    cmpl %ecx, %eax

    je jeste
    jmp dalje

jeste:
    incl %ebx

dalje:
    shll %ecx
    jnc petlja_low

    movl $0x00000001, %ecx

petlja_high:
    movl %edi, %eax
    andl %ecx, %eax
    cmpl %ecx, %eax

    je jeste_h
    jmp dalje_h

jeste_h:
    incl %ebx

dalje_h:
    shll %ecx
    jnc petlja_high

    jmp dobro

dobro:
    movl %ebx, %eax

ocisti_stek:
    popl %ebx
    popl %edi
    popl %esi
    movl %ebp, %esp
    popl %ebp
    ret



