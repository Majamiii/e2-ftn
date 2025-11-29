package priprema;

public class Main {

	public static void main(String[] args) {
		Main m = new Main();
		m.testirajKolokvijum();
		m.testirajPredmet();
		m.testirajStudenta();
	}

	private void testirajKolokvijum() {
		Kolokvijum k = new Kolokvijum();
		Kolokvijum k1 = new Kolokvijum("K1", 20);
		System.out.println(k1.getNaziv());
		System.out.println(k1.getOsvojeniPoeni());
		System.out.println(k1);
		if(k1.polozio())
			System.out.println("Polozen kolokvijum k1");
		else
			System.out.println("Nije polozen kolokvijum k1");
	}
	
	private void testirajPredmet() {
		System.out.println("------------ Testiranje klase predmet ------------");
		Predmet p = new Predmet();
		Predmet p2 = new Predmet("OOP");
		Kolokvijum k1 = new Kolokvijum("K1", 20);
		if(p2.dodajTest(k1))
			System.out.println("Uspesno dodat test");
		else
			System.out.println("Nije uspesno dodat test");
		System.out.println(p2.getNaziv());
		System.out.println("ukupno poena: "+p2.izracunajPoene());
		if(p2.polozio())
			System.out.println("Predmet je polozen");
		else
			System.out.println("Predmet nije polozen");
		System.out.println(p2);
	}
	
	private void testirajStudenta() {
		System.out.println("------------ Testiranje klase student ------------");
		Student s = new Student("ra20/2015", "Prezimenic");
		Student s1 = new Student();
		System.out.println(s.formiarajEMailAdresu());
		System.out.println(s.trajanjeStudija());
		System.out.println(s);
	}
}
