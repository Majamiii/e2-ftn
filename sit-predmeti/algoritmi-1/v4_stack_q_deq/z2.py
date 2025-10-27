# konverzija pomocu steka

from stack import LimitedStack

CIFRE = "0123456789ABCDEF"

if __name__ == "__main__":

    n = int(input("Broj koji se konvertuje: "))
    b = int(input("Osnova za konverziju (izmedju 1 i 16): "))

    converted = ""

    s = LimitedStack()

    while (n>0):
        s.push(CIFRE[n%b], 100)
        n //= b

    while (not s.is_empty()):
        converted += s.pop()

    print(converted)