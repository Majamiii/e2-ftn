package priprema;

import java.util.HashMap;

public class Pernica {
	private HashMap<String, Bojica> bojice;
	private int raspolozivoMesta=5;
	
	public Pernica() {
		this.bojice = new HashMap<>();
	}
	
	public boolean dodaj(Bojica boja) {
		if(bojice.containsKey(boja.getSerijskiBroj())) {
			return false;
		}
		if(this.raspolozivoMesta>0) {
			bojice.put(boja.getSerijskiBroj(), boja);
			this.raspolozivoMesta -= 1;
			return true;
		}
		return false;
	}
	
	public int prebroj(double granicnaCena) {
		int brojac=0;
		for (Bojica b: bojice.values()) {
			if (b.getCena() > granicnaCena) {
				brojac += 1;
			}
		}
		return brojac;
	}

	@Override
	public String toString() {
		
		String retVal = "";
		
		if(bojice.size() <= 0) {
			System.out.println("Pernica je prazna.\n");
			return retVal;
		}
		
		retVal += "Pernica: \n";
		for (Bojica b: bojice.values()) {
			retVal += b+"\n";
		}
		
		return retVal;
	}
	
	
	

	public static void main(String[] args) {

		Bojica olovka = new Bojica("001", 50, "crvena", "drvena");
		Bojica flomaster = new Bojica("002", 300, "plava", "flom");
		Bojica vodena = new Bojica("003", 2000, "zuta", "vodena");
		System.out.println(olovka);
		

		System.out.println("cena flomastera: " + flomaster.getCena());
		System.out.println("serijski br flomastera: " + flomaster.getSerijskiBroj());
		
		olovka.akcijskaCena(30);
		olovka.akcijskaCena(-3);
		
		Pernica p = new Pernica();
		p.dodaj(flomaster);
		System.out.println(p);
		p.dodaj(vodena);
		p.dodaj(olovka);

		System.out.println(p.prebroj(1700));
		System.out.println(p.prebroj(200));
		System.out.println(p.prebroj(5));

		System.out.println(p);
		
	}
	
	
	
}
