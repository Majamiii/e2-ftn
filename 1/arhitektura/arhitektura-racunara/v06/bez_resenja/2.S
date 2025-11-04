#   Napisati potprogram u asemblerskom jeziku koji proverava paritet za niz 15-bitnih vrednosti:
#   
#       a. int CheckParityArray(unsigned short int* niz, int n)
#   
#       b. Potprogram prima niz 16-bitnih elemenata kod kojih je najviši bit već postavljen na
#           bit pariteta
#   
#       c. Potprogram treba da poziva potprogram iz prethodnog zadatka da proveri paritet
#           svakog od elemenata (pročitati stavku e kod 4. zadatka u spisku zadataka za koje
#           postoje dostupna rešenja)
#           
#       d. Potprogram vraća broj elemenata niza kod kojih je bit pariteta pogrešno postavljen



.section .text
.globl CheckParityArray

CheckParityArray:
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    pushl %edi
    pushl %ebx


    movl 8(%ebp), %ebx      # adresa na kojoj se nalazi niz i njegovi elementi -> EBX
    movl 12(%ebp), %ecx     # broj elemenata niza
    movl %ecx, %edi

    movl $4, %eax
    mull %ecx
    movl %eax, %ecx
    #   subl $4, %ecx

    movl $0, %edx           # indeks elementa

elementi:
    movl %ebx, %esi      # adresa elemen
    addl %edx, %ebx
    #   subl $4, %esp
    pushl %esi
    call CheckParity
    addl $4, %esp
    #   movl %eax, -4(%ebp)     # lokalna promenljiva
    subl %eax, %edi         # edi je nas brojac

    addl $4, %edx
    cmpl %edx, %ecx
    jne elementi

    movl %edi, %eax

ocisti_stek:

    popl %ebx
    popl %edi
    popl %esi

    movl %ebp, %esp
    popl %ebp
    ret