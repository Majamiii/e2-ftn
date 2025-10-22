# prikazati apsolutne putanje svih datoteka na zadanoj putanji u direktorijumskom stablu
# koristiti moduo os

import os

def find(path):
    # bazni slucaj - dosli smo do fajla
    if not os.path.isdir(path):
        print(path)
        return
    
    files = os.listdir(path)

    for filename in files:
        find(os.path.join(path, filename))


putanja = input("Unesi putanju: ")
find(putanja)