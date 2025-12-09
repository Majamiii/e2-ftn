using LinearAlgebra

function zadatak(A, s)
    B = A[:, 1:2:end];
    v= B[(B.<-99) .^ (B.> -1000)]

    d = diag(A) .% s;
    m = d[ d .== 0] / length(A)
    p = length(m)

    return v,p
end

A = round.(2000 * (rand(5,5) .- 0.5));
display(A)
print();
display(zadatak(A, 3));

#   Napisati funkciju koja kao ulazne parametre prima kvadratnu matricu A i skalar S, a kao povratne vrednosti vraća:
#   a)  Vektor V, koji se sastoji od svih negativnih trocifrenih elemenata iz neparnih kolona matrice A.
#   b)  Skalar P, koji govori koliki procenat elemenata sa glavne dijagonale matrice A je deljiv sa skalarom S.