# 5. U asemblerskom jeziku implementirati deljenje dva broja pomoću oduzimanja, uz čuvanje ostatka
#     a. Dva proizvoljna broja koja se množe postavljaju se na početku programa u neke od dostupnih registara opšte namene
#     b. Konačan rezultat treba se naći u nekom od dostupnih registara opšte namene
#     c. Ideja: ako treba A podeliti sa B, potrebno je A umanjivati za B sve dok B ne postane veće od A; rezultat deljenja jednak je 
#        broju izvršenih oduzimanja, a vrednost A po prestanku oduzimanja jednaka je traženom ostatku

.section .data
.section .text
.globl main

main:
# 16/3 = 5(1)
    movl $16, %eax
    movl $3, %ebx
    movl $0, %ecx   # iterator, tu ce biti rezultat deljenja

    cmpl %eax, %ebx
    jle deljenje
    jmp kraj

deljenje:
    subl %ebx, %eax
    addl $1, %ecx

    cmpl %eax, %ebx
    jle deljenje

    jmp kraj

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80