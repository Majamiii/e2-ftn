# konverzija iz dekadnog u sistem sa zadatom osnovom

# treba deliti sa osnovom i zapisivati ostatak i posle flippovati

DIGITS = "0123456789ABCDEF"

def konverzija(broj, osnova):

    if broj < osnova:
        return DIGITS[broj]
    
    return konverzija(broj//osnova, osnova) +  DIGITS[broj%osnova]

n = int(input("Broj koji se konvertuje: "))
osnova = int(input("Osnova brojnog sistema: "))
print(konverzija(n, osnova))