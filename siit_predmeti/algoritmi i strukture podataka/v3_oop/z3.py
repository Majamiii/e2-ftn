# svaki korisnik: korisnicko ime, lozinka, ime, prezime, uloga(kozmeticar,klijent, recepcionar,menadzer)

# za klijente: telefon, email adresa, pol

# kozmeticar: spisak bjuti tretmana koje nudi

# menadzer: spisak zaposlenih kojima je nadredjen

class Korisnik:
    def __init__(self,username,ime,prezime,lozinka,uloga):
        self._username = username
        self._ime = ime
        self._prezime = prezime
        self._lozinka = lozinka
        self._uloga = uloga

    @property
    def username(self):
        return self._username
    @username.setter
    def username(self, username):
        self._username = username
    
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
    def prezime(self,prezime):
        self._prezime = prezime

    @property
    def lozinka(self):
        return self._lozinka
    @lozinka.setter
    def lozinka(self,lozinka):
        self._lozinka = lozinka

class RegistrovaniKlijent(Korisnik):
    
    def __init__(self,username,ime,prezime,lozinka,telefon,email,pol):
        super(RegistrovaniKlijent,self).__init__(username,ime,prezime,lozinka)
        self._telefon = telefon
        self._email = email
        self._pol = pol

    @property
    def telefon(self):
        return self._telefon
    @telefon.setter
    def telefon(self, telefon):
        self._ime = telefon

    @property
    def email(self):
        return self._email
    @email.setter
    def email(self,email):
        self._email = email

    @property
    def pol(self):
        return self._pol
    @pol.setter
    def pol(self, pol):
        self._pol = pol

class Kozmeticar(Korisnik):
    def __init__(self,username,ime,prezime,lozinka,tretmani):
        super(Kozmeticar,self).__init__(username,ime,prezime,lozinka)
        self._tretmani = tretmani
    
    @property
    def tretmani(self):
        return self._tretmani
    @tretmani.setter
    def tretmani(self,tretman):
        self._tretmani = tretman

class Recepcioner(Korisnik):
    def __init__(self,username,ime,prezime,lozinka):
        super(Recepcioner,self).__init__(username,ime,prezime,lozinka)

class Menadzer(Korisnik):
    def __init__(self,username,ime,prezime,lozinka, lista_zaposlenih):
        super(Recepcioner,self).__init__(username,ime,prezime,lozinka)

        if lista_zaposlenih is None:
            lista_zaposlenih = []
        self._lista_zaposlenih = lista_zaposlenih

    @property
    def lista_zaposlenih(self):
        return self._lista_zaposlenih
    @lista_zaposlenih.setter
    def lista_zaposlenih(self,lista_zaposlenih):
        self._lista_zaposlenih = lista_zaposlenih
