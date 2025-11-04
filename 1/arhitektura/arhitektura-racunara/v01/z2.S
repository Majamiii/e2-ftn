#   2. U asemblerskom jeziku implementirati množenje dva broja pomoću sabiranja 
#      a. Dva proizvoljna broja koja se množe postavljaju se na početku programa u neke od 
#      dostupnih registara opšte namene 
#      b. Konačan rezultat treba se naći u nekom od dostupnih registara opšte namene 
#      c. Ideja: ako su činioci u registrima eax i ebx, a suma će se naći u ecx, treba eax puta 
#      vrednost iz ebx dodati na ecx 
#      d. Primer: ako se množe 3 i 5, rezultat se treba dobiti ili kao 3+3+3+3+3, ili kao 5+5+5 
#      e. Optimizacija: napisati program tako da se petlja vrti minimalan broj puta; ako se 
#      množe 3 i 5, petlja treba da ima 3 iteracije bez obzira na to koji se činilac nalazi u 
#      kom registru 
#      f. Pomoć za optimizaciju: korišćenje “xchgl” instrukcije za zamenu vrednosti dva 
#      registra


.section .data
.section .text
.globl main

main:

    movl $5, %eax
    movl $3, %ebx
    movl $0, %ecx           # tu se cuva proizvod

    cmpl %ebx, %eax         # namestamo da je u eax manji broj, i to ce ujedno biti i iterator
    ja zameni
    jmp petlja              # ako je sve ok onda idemo direktno u petlju

zameni:
    xchgl %eax, %ebx

petlja:
    cmpl $0, %eax
    je kraj

    addl %ebx, %ecx
    subl $1, %eax
    jmp petlja

kraj:
    movl $1, %eax
    movl $0, %ebx
    int $0x80



