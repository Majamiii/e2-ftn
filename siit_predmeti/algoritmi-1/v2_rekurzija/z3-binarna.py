# fibonaci pomocu binarne rekurzije

def fibonaci(n):
    if n==1: return 1
    if n==0: return 0

    return fibonaci(n-1) + fibonaci(n-2)

n = int(input("Unesite broj: "))
print(n, ". broj Fibonacijevog niza je: ", fibonaci(n))