
#define ZERO(x) sub x, x, x
.data
45 // a, adresa 0
123 // b, adresa 1
.text
Begin: // program racuna a * b
ZERO(R0) // postavlja R0 na nulu
ld R1, R0 // R1 - vrednost sa adrese 0
inc R0, R0
ld R2, R0 // R2 - vrednost sa adrese 1
dec R0, R0
// Stanje: R0: 0, R1: a, R2: b
Loop:
add R0, R0, R1
dec R2, R2
jmpnz Loop
End:
jmp End// rezultat je u R0