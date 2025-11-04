#   Napisati potprogram u asemblerskom jeziku koji proverava paritet za 15-bitnu vrednost:

#       a. int CheckParity(unsigned short int* vrednost)

#       b. Potprogram prima 16-bitni parametar kod koga je najviši bit već postavljen na bit
#           pariteta

#       c. Potprogram vraća 1 ukoliko je bit pariteta dobro postavljen, a 0 ukoliko nije


# int CheckParity(unsigned short int* vrednost);

.section .text
.globl CheckParity

CheckParity:
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    pushl %edi
    pushl %ebx
    
    pushl %ecx
    pushl %edx

    movl $0, %eax
    movl $0, %ebx
    movl $0, %ecx
    movl $0, %edx
    movl $0, %esi
    movl $0, %edi
    movl $0, %ebx

    # spremanje registara za koriscenje
    mov $0x8000, %cx  # 1000..000
    mov $0, %bx       # u ebx ce se brojati jedinice
    mov $0, %ax       # tu ce se gledati paritet, a posle uporedjivati sa njihovim

    movl 8(%ebp), %eax  # tu je nas broj
    movl (%eax), %ebx
    mov %bx, %ax
    and $0x7fff, %ax  # ostaje nam nas broj bez prve cifre
    and 8(%ebp), %cx  # tu ostaje samo njihova prva cifra
    rol %cx

    # sad je u cx pretpostavljena prva cifra, a u ax je nas broj.
    # nas broj rotiramo udesno i sabiramo carry (u bx), prekinemo kad je nas broj jednak nuli

    movl $0, %ebx

br_jedinice:
    shr %ax
    jc dodaj
nastavi:
    cmp $0, %ax
    je prebrojano
    jmp br_jedinice

dodaj:
    incl %ebx
    jmp nastavi

prebrojano:
# sad se u ebx nalazi broj jedinica koje ima broj
# videcemo da li je to paran broj ako da shiftujemo udesno i ako ima carry onda je neparan i smestamo 1 u eax

    shr %ebx
    jc neparan

# ako nije skocio onda je paran
    mov $0, %dx
    jmp uporedi

neparan:
    mov $1, %dx       # u edx se nalazi 1 ako je neparan i 0 ako je paran

uporedi:
    cmp %dx, %cx
    jne nisu_isti

    # ako nije skocio, brojevi su isti i vracamo vrednost 1

    movl $1, %eax
    jmp ocisti_stek

nisu_isti:
    movl $0, %eax

ocisti_stek:
    popl %edx
    popl %ecx

    popl %ebx
    popl %edi
    popl %esi

    movl %ebp, %esp
    popl %ebp
    ret
