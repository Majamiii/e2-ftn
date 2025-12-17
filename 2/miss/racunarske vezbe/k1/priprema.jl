#   Napisati funkciju koja kao ulazne parametre prima kvadratnu matricu A i skalar S, a kao povratne vrednosti vraća:
#   a)  Vektor V, koji se sastoji od svih negativnih trocifrenih elemenata iz neparnih kolona matrice A.
#   b)  Skalar P, koji govori koliki procenat elemenata sa glavne dijagonale matrice A je deljiv sa skalarom S.

using LinearAlgebra, Statistics

function funkcija(A,s)

    nep_kol = A[:, 1:2:end]
    v = nep_kol[ (nep_kol .<= -100 ) .& (nep_kol .> - 1000)]

    ostaci = diag(A) .% s
    deljivi = ostaci[ostaci .== 0]

    p = length(deljivi) / length(A)

    return v, round(p, digits=2)        # moze i samo p ali ovako je lepse :3
end

M = [ -522 -400 500 ; 4 -1 -333 ; 123 100000 0 ]
display(funkcija(M,2))