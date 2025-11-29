package student_ognjen;


public class main {

	public static void main(String[] args) {
		main m = new main();
		m.testirajKolokvijum();
		m.testirajPredmet();
	}
	
	
	@SuppressWarnings("unused")
	private void testirajKolokvijum() {
		Kolokvijum k = new Kolokvijum();
		Kolokvijum k1 = new Kolokvijum("OOP - T12", 20);
		System.out.println(k1.getNaziv());
		System.out.println(k1.getOsvojeniPoeni());
		System.out.println(k1);
		if(k1.polozio() == true) {
			System.out.println("Polozen kolokvijum !! \n");
		} 
		else {
			System.out.println("Nije polozen kolokvijum  (__ ): __) ");
		} 						
	}
	
	@SuppressWarnings("unused")
	private void testirajPredmet() {
		System.out.println("------------TESTIRANJE KLASE PREDMET----------------");
		Predmet p  = new Predmet();
		Predmet p2 = new Predmet("ObjektNo orj. programiranje");
		Kolokvijum k1 = new Kolokvijum("k1", 20);
		
		if (p2.DodajTest(k1)) {
			System.out.println("Uspesno dodat");
		} else {
			System.out.println("Predmet nije uspesno dodat :(  ");
		}
		
		System.out.println(p2.getNaziv());
		System.out.println("Ukupno poena: " + p2.izracunajPoene());
		
		if(p2.polozio()) {
			System.out.println("predmet je polozen");		
		} else {
			System.out.println("predmet nije polozen");
		}
		System.out.println(p2);
	}
	
	@SuppressWarnings("unused")
	private void testirajStudenta() {
		System.out.println("----------testiranje klase student---------");
		Student s = new Student("ee182/2012", "Markovic");
		Student s1 = new Student();
		
		System.out.println(s.formirajEMailAdresu());
		System.out.println(s.trajanjeStudija());
		System.out.println(s);
	}
	
}
