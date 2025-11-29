package student_ognjen;

import java.util.HashMap;

public class Student {
	private String prezime, indeks;
	private HashMap<String, Predmet> predmeti;
	public Student(String prezime, String indeks) {
		super();
		this.prezime = prezime;
		this.indeks = indeks;
		this.predmeti = new HashMap<String, Predmet>();
	}
	
	public Student() {
		super();
		this.prezime = "";
		this.indeks = "";
		this.predmeti = new HashMap<String, Predmet>();
	}
	
	public boolean dodajPredmet(Predmet p) {
		if(predmeti.containsKey(p.getNaziv())) {
			return false;
		}
		
		if(predmeti.size() < 10) {
			predmeti.put(p.getNaziv(), p);
			return true;
		}
		
		return false;
		
	}
	public String formirajEMailAdresu() {
		String email = indeks.substring(0,2);
		email += "." + prezime + ".";
		email += indeks.substring(2, indeks.length());
		email += "@uns.ac.rs";
		email = email.replace('/', '-');
		
		return email;
	}
	
	public int trajanjeStudija() {
		try {
			String godinaUpisa = indeks.substring(indeks.length()-4);
			int godinaUpisa1 = Integer.parseInt(godinaUpisa);
			return 2022 - godinaUpisa1;
	
		} catch (NumberFormatException e) {
			System.out.println("pogresan format godine....");
			return -1;
		}
	}

	@Override
	public String toString() {
		String ret = "";
		
		ret += "IME: " + prezime + "\n";
		ret += "BROJ INDEKSA" + indeks + "\n";
		ret += "Godine studiranja: " + trajanjeStudija() + "\n";
		
		if(predmeti.size() == 0) {
			ret += "Trenutno nema predmeta koje je " + indeks + " polozio";
		}
		
		for(Predmet p : predmeti.values()) {
			ret += p;
			ret += "\n";
		}
		
		return ret;
	}

	
}
