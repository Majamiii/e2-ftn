# pronalazenje max sa rekurzijom ali na njihov nacin


def max_rekurzija(niz, maks):
    if len(niz) == 1:
        return niz[0]

    a = max_rekurzija(niz[1:], maks)

    if a>niz[0]: return a

    return niz[0]

niz = [1,2,3,9,5,4]
print(max_rekurzija(niz, niz[0]))