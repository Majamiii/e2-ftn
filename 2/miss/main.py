#   skripta za pracenje napretka iz miss teorije

#   pri odgovaranju za tacan odg upisati bilo koji broj osim 5
#   5 - polovicno tacan odg
#   bilo sta drugo - netacno

#   output se nalazi u stats.txt (appenduje se svaki novi rez)

import sys

if __name__=="__main__":

    br_pitanja = int(input("uneti broj pitanja: "))

    n = 0
    t = False
    tacni = []
    netacni = []
    pola = []
    
    try:
        for i in range(1,br_pitanja + 1):
            s = "pitanje broj " + str(i) + ": "
            t = int(input(s))
            if t==5:
                tacni.append(0.5)
                pola.append(i)
            elif t:
                tacni.append(1)
            else:
                netacni.append(i)
    
    except KeyboardInterrupt:
        print("prekinuo se rad programa - cuvam dosadasnje rezultate")
    
    finally:
        sys.stdout = open("stats.txt", "a", encoding="utf-8")
    
        print()
        print("ukupno pitanja: " + str(len(tacni)+len(netacni)))
        print("ukupno tacnih: " + str(sum(tacni)))
        print("ukupno netacnih: " + str(len(netacni)))
        procenat = sum(tacni)/(len(tacni)+len(netacni))*100
        print("procentualno: ", str(round(procenat,2))+"%")
        print("skalirano na 15 zbog klk je: " + str(round(procenat * 0.2, 1)))
        print("netacni su: ")
        print(netacni)
        print("polovicno tacni su: ")
        print(pola)
