# samo ja malo vezbam

using LinearAlgebra
using Statistics

A = round.(rand(5,5)*100)
display(A)
print("\n")
M=reverse(A); display(M)        # reverse obrce u odnosu na centar rekla bih

display(reverse(M, dims=1))     # dims 1 obrce redosled redova tj vrsta

display(reverse(M, dims=2))     # obrne redosled kolona

print("\n")
display(M)
display(triu(M,2))              # od tog reda koji smo stavili sve iznad ostavi isto, sve ispod stavi na 0
# upper znaci ostaje nam samo upper

display(tril(M,2))          # od istog reda ide granica kao triu samo suprotno gde idu 0 a gde 1

print("\n",mean(M), "\n\n")
print(sum(M) / length(M), "\n\n\n")

X = [ 1 2 3; 4 5 6; 7 8 9]
display(X)
display(diag(X))
display(diag(reverse(X, dims=2)))       # sporedna

display(X[begin:2:end, :])

print("\n")

print("\n.^ : \n")
display(X[( X .> 5 ) .^ (X .< 8)])
print("\n.& : \n")
display(X[( X .> 5 ) .& (X .< 8)])

M = [0 0 0 ; 1 0 1 ; 0 0 0]
v = X[convert.(Bool, M)]        # ostaje samo maska omfg
display(v)

print("\n\nmaksimum\n")
display(maximum(X))
print("\nmax vrste\n")          # vrsta sacinjena od najvecih elemenata u svakoj koloni
# bukv kao "optimalna" vrsta, recimo
display(maximum(X, dims=1))

X[1,1]=100000
print("\nmax vrste\n")
display(maximum(X, dims=1))

print("\nmin kolone\n")
display(minimum(X, dims=2))



#   -------------

X = [ 1 2 3; 4 5 6; 7 8 9]
display(X)
display(diag(X))
display(diag(reverse(reverse(X, dims=1))))       # sporedna na funky nacin
# reverse po bilo kojoj dimenziji ce dati iste te elemente ali drugim redosledom