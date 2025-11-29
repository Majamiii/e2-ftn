package student_ognjen;

import java.util.ArrayList;
import java.util.Scanner;

public class Predmet implements InterfacePredmet {

	private String naziv;
	private ArrayList<Test> testovi;
	
	
	public Predmet() {
		super();
		this.naziv = "";
		this.testovi = new ArrayList<Test>();
	}
	
	public Predmet(String naziv) {
		super();
		this.naziv = naziv;
		this.testovi =  new ArrayList<Test>();
	}

	@Override
	public boolean DodajTest(Test t) {
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

	public boolean polozio() {
		for (Test t : testovi) {
			if(t.polozio() == true || t.getOsvojeniPoeni() <= 55 ) {
				return false;
			}
		}
		return true;
	}

	@Override
	public String toString() {
		String ret = "***** Predmet *******";
		ret += "Naziv: " + naziv + "\n Testovi: ";
		
		if (testovi.size() == 0) {
			ret += "\t Lista testova je prazna";
			ret += "************************* \n";
			return ret;
		}
		
		for (int i=0; i<testovi.size(); i++) {
			
			do { 
				Test t = testovi.get(i);
				ret += t;
			} while (i != testovi.size()-1);
			
			ret += "\n" + "*******************";
		}
		
		return ret;
	}

	
	public String getNaziv() {
		return naziv;
	}

	public void setNaziv(String naziv) {
		this.naziv = naziv;
	}

	public ArrayList<Test> getTestovi() {
		return testovi;
	}

	public void setTestovi(ArrayList<Test> testovi) {
		this.testovi = testovi;
	}

	@Override
	public int izracunajPoene() {
		// TODO Auto-generated method stub
		return 0;
	}
	
}
