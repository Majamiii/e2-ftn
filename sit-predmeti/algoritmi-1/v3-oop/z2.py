class Student:
    def __init__(self,ime,prezime):
        self._ime = ime
        self._prezime = prezime
        self._zbir = 0
        self._ocene = []

    @property
    def ime(self):
        return self._ime
    @ime.setter
    def ime(self, ime):
        self._ime = ime

    @property
    def prezime(self):
        return self._prezime
    @prezime.setter
    def prezime(self, prezime):
        self._prezime = prezime

    def upisi_ocenu(self, ocena):
        self._zbir += ocena
        self._ocene.append(ocena)

    def ponisti_ocenu(self,ocena):
        ok = False
        for i in range(len(self._ocene)):
            if ocena==self._ocene[i]:
                self._ocene.pop(i)
                ok = True
                break
        if ok == False:
            raise ValueError("Nema ocene koja treba da se ponisti")
        self._zbir -= ocena

    @property
    def prosek(self):
        return self._zbir/len(self._ocene)
    

if __name__ == "__main__":
    student = Student("Maja", "Milovic")
    student.upisi_ocenu(3)
    print(student.prosek)
    student.upisi_ocenu(4)
    print(student.prosek)
    student.ponisti_ocenu(3)
    print(student.prosek)
    