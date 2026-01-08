# platforma sa 3 stuba: a,b i c
# ima n stubova na platformi a koji su sortirani i treba ih prebaciti na platformu c

# ne smeju veci diskovi da se stavljaju na manje

# ideja: svi osim poslednjeg se rasporede na ostale i onda taj najveci mozemo da stavimo na odredisni

def hanoi(n,a,b,c):
    if n==0: return

    hanoi(n-1,a,c,b)
    print("sa ", a, " na ", c)
    hanoi(n-1,b,a,c)

n = int(input("Broj diskova: "))
hanoi(n, "a", "b", "c")