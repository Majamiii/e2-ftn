
#define ZERO(x) sub x, x, x
.data
45 // a, adresa 0
123 // b, adresa 1

.text
Begin: // program racuna a * b
ZERO(R0) // postavlja R0 na nulu
ld R1, R0 // R1 - sa lokacije a:
inc R3, R0
ld R2, R3 // R2 - sa lokacije b:
// Stanje: R0: 0, R1: a, R2: b, R3: 1
Loop:
// R2 neparno?, tj. da li je poslednji bit 1?
and R4, R2, R3
jmpz NoAdd // ako nije, onda preskoci sabiranje
add R0, R0, R1
NoAdd:
add R1, R1, R1 // R1 <- 2*R1
shr R2, R2
jmpnz Loop
End:
jmp End // rezultat je u R0