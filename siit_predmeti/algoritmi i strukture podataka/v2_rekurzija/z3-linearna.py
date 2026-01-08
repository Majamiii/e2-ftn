# fibonaci pomocu linearne rekurzije

def fibonaci(n,a=0,b=1):

    if n==1: return 1

    return a+fibonaci(n-1,b,a+b)

n = int(input("Unesite broj: "))
print(n, ". broj Fibonacijevog niza je: ", fibonaci(n))