# 2.  U asemblerskom jeziku, rezervisati jednu 32-bitnu reč iu memoriji  dati joj proizvoljnu 
#     vrednost. Nakon toga, njena četiri bajta redom smestiti u registre ah, al, bh, bl, tako da 
#     najniži bajt bude u ah, a najviši u bl

.section .data
    rec: .long 0xabcd5678    # 78 56 cd ab
.section .text
.globl main

main:
    movl rec, %ecx

    mov rec, %ah    
    mov rec+1, %al
    mov rec+2, %bh
    mov rec+3, %bl


kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80