using LinearAlgebra, Statistics
A = [1 4 -2 9 6; -1 0 0 3 7; 99 3 -3 4 7; 5 -6 0 -8 3; 1 2 3 4 5]

s = mean(A[end, :])

gd = diag(A)

gd[gd .>= 0]

B = A[:,2:2:end]

A[rem.(A, 9) .== 0]