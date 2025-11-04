# U asemblerskom programu implementirati oduzimanje dve promenljive dvostruke 
# preciznosti 
#     a. Uraditi zadatak i za označene i za neoznačene brojeve 
#     b. Koristiti kao pomoć primer sabiranja u dvostrukoj preciznosti sa slajdova sa drugog 
# termina vežbi 
#     c. Za oduzimanje sa pozajmicom koristiti sbb instrukciju 
#     d. Obratiti pažnju na to pri oduzimanju kojih delova (viših ili nižih) može doći do greške 
# u prekoračenju 

.section .data
    a: .long 0x12345670, 0x00001000
    b: .long 0x12345670, 0x00003000

    greska: .byte 0
.section .text
.globl main

main:
    movl a, %eax        # niza 4 od a - eax
    movl a+4, %ecx      # visa 4 od a - ecx
    movl b, %ebx        # niza 4 od b - ebx
    movl b+4, %edx      # visa 4 od b - edx

    subl %ebx, %eax
    sbbl %edx, %ecx

    jnc kraj
    jmp err

err:
    movl greska, %eax
    movl greska, %ebx

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80