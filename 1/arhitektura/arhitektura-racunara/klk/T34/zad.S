# autor: Imenko Prezimić INDEX ra1234-2023
# int prebrojNajviseUzastopnih(unsigned long long* vrednost)

.section .text
.globl prebrojNajviseUzastopnih

prebrojNajviseUzastopnih:
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    pushl %edi
    pushl %ebx

    # inicijalizacija i pripremanje za koriscenje
    movl 8(%ebp), %eax

    movl $1, %edx

    movl 4(%eax), %ebx       # u ebx je gornji deo
    movl (%eax), %ecx      # u ecx je donji deo

    movl $0, %eax           # tu je max brojac - zgodno i jer se po eax prenosti povratna vrednost
    movl $0, %edx           # tu je temp brojac
    movl $0, %esi           # tu nam je brojac koliko puta smo se shiftovali

petlja:
    #   sve cemo da shiftujemo udesno i proveravamo da li je carry 0 ili ne
    #   ako jeste onda dodajemo 1 u edx
    #   ako nije onda proveravamo da li je veca vrednost u eax ili edx. cilj je da u eax bude max
    #   ako je nas broj jednak nuli onda prebacujemo ebx u ecx i nastavljamo postupak
    shrl %ecx
    jnc nula        # ako nema carryja znaci da je taj broj bio nula! a ako ga je bilo znaci da smo stigli do jedinice
    # ako je 1
    movl $1, %edi
    cmpl %edx, %eax
    jl novi_max
    movl $0, %edx

dalje:
    incl %esi
    cmpl $32, %esi
    je visi_deo

    cmpl $64, %esi
    je ocisti_stek
    jmp petlja

nula:
    movl $0, %edi           # tu cu videti u dibageru da li je u pravu sto je tamo 0 ili ne
    incl %edx
    cmpl %edx, %eax
    jge dalje

novi_max:
    movl %edx, %eax
    cmpl $0, %edi
    je dalje
    movl $0, %edx
    jmp dalje

visi_deo:
    movl %ebx, %ecx
    jmp petlja

ocisti_stek:
    popl %ebx
    popl %edi
    popl %esi

    movl %ebp, %esp
    popl %ebp
    ret