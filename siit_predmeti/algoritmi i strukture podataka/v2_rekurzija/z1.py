# rekurzija

# suma prvih n prirodnih brojeva

# ideja: S(n) = n + S(n-1)

def suma(n):
    if n==1 : return 1
    return (n + suma(n-1))

n = int(input())
print(suma(n))