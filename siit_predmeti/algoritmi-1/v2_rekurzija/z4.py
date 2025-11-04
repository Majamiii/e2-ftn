# rekurzivna replikacija - funkcija
# 2 parametra: prvi je koji broj, a drugi koliko puta

# npr: replicate(5,3)
# output: [5,5,5]

def replicate(broj, ponavljanje):
    if ponavljanje==0: return []

    return [broj] + replicate(broj, ponavljanje-1)

arr = []
arr = replicate(9,4)
print(arr)