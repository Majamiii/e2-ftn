# naci max el niza rekurzivnih putem

# bazni slucaj: kraj liste
# sve do tad pozivaj funkciju za sl idx

def max_rekurzivno(arr, maks, i):

    if int(arr[i])>maks:
        maks = int(arr[i])

    if i == len(niz)-1:
        return maks
    
    return max_rekurzivno(arr, maks, i+1)


niz = [4,3,2,1,9,0,2]
print(max_rekurzivno(niz, niz[0], 0))