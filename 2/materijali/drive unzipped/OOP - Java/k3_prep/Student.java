package priprema;

import java.util.HashMap;

public class Student {
	private String indeks;
	private String prezime;
	private HashMap<String, Predmet> predmeti;

	public Student() {
		super();
		this.indeks = "";
		this.prezime = "";
		this.predmeti = new HashMap<String, Predmet>();
	}

	public Student(String indeks, String prezime) {
		super();
		this.indeks = indeks;
		this.prezime = prezime;
		this.predmeti = new HashMap<String, Predmet>();
	}

	public boolean dodajStudenta(Predmet p) {
		if (predmeti.containsKey(p.getNaziv()))
			return false;
		if (predmeti.size() < 10) {
			predmeti.put(p.getNaziv(), p);
			return true;
		}
		return false;
	}

	public String formiarajEMailAdresu() {
		String adresa = indeks.substring(0, 2);
		adresa += "." + prezime + ".";
		adresa += indeks.substring(2, indeks.length());
		adresa += "@uns.ac.rs";
		adresa = adresa.replace('/', '-');
		return adresa;
	}

	public boolean polozioGodinu() {
		for (Predmet p : predmeti.values()) {
			if (!p.polozio())
				return false;
		}
		predmeti.clear();
		return true;
	}

	public int trajanjeStudija() {
		try {
			int godine = Integer.parseInt(indeks.substring(indeks.length() - 4, indeks.length()));
			return 2022 - godine;
		} catch (NumberFormatException e) {
			System.out.println("Pogresan format godine.");
			return -1;
		}
	}

	@Override
	public String toString() {
		String s = "Student: \n";
		s += "Indeks: " + indeks + "\n";
		s += "Prezime: " + prezime + "\n";
		s += "Godine studieranja: " + trajanjeStudija() + "\n";
		if (predmeti.size() == 0) {
			s += "Trenutno nema predmeta";
			return s;
		}
		for (Predmet p : predmeti.values()) {
			s += p;
			s += "\n";
		}
		return s;
	}

}
