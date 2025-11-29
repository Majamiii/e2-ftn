using LinearAlgebra
A = [1 4 -2 9 6; -1 0 0 3 7;99 3 -3 4 7; 5 -6 0 -8 3; 1 2 3 4 5]

p = A[3]
p = A[3,1]

M = zeros(size(A))

M[3,1]=1
p3 = A[convert.(Bool,M)]

# primer 4
vrsta1 = A[1, :]

# primer 5
kolona5 = A[:, 5]

# primer 6
nep_vrste = A[1:2:end, :]

# primer 7
pozitivni = A[A .> 0]

# primer 8
el_opseg = A[(A .>- -5) .^ (A .< 5)]

# primer 9
max_el = maximum(A)
min_el = minimum(A)