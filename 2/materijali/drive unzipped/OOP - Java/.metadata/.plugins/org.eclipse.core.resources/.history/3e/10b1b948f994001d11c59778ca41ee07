package priprema;

import java.util.ArrayList;
import java.util.Scanner;

public class Predmet implements IPredemt {

	private String naziv;
	private ArrayList<Test> testovi;

	public Predmet() {
		naziv = "";
		testovi = new ArrayList<Test>();
	}

	public Predmet(String naziv) {
		super();
		this.naziv = naziv;
		this.testovi = new ArrayList<Test>();
	}

	@Override
	public boolean polozio() {
		for (Test t : testovi) {
			if (!t.polozio() || t.getOsvojeniPoeni() <= 55) {
				return false;
			}
		}
		return true;
	}

	@Override
	public int izracunajPoene() {
		int suma = 0;
		for (Test t : testovi) {
			suma += t.getOsvojeniPoeni();
		}
		return suma;
	}

	public String getNaziv() {
		return naziv;
	}

	@Override
	public boolean dodajTest(Test t) {
		for (Test test : testovi) {
			if (test.getNaziv().equals(t.getNaziv())) {
				Scanner in = new Scanner(System.in);
				String noviNaziv = in.nextLine();
				in.close();
				t.setNaziv(noviNaziv);
				for (Test pom : testovi) {
					if (pom.getNaziv().equals(t.getNaziv())) {
						return false;
					}
				}
				return testovi.add(t);
			}
		}
		return testovi.add(t);
	}

	@Override
	public String toString() {
		String ret = "************* Predmet **************\n";
		ret += "Naziv: " + naziv + "\n";
		if(testovi.size()==0) {
			ret+="Lista testova je prazna\n";
			ret += "************************************\n";
			return ret;
		}
		ret += "Testovi: \n";
		for (int i=0; i<testovi.size(); i++) {
			Test t = testovi.get(i);
			ret += t;
			if(i!=testovi.size()-1)
				ret += "\n";
		}
		ret += "************************************\n";
		return ret;
	}

}
