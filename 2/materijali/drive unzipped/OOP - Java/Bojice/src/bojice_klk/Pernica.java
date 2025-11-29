package bojice_klk;

import java.util.HashMap;

public class Pernica {
	
	private HashMap <String, Bojica> bojica;
	private int raspolozivaMesta = 5;
	
	public Pernica() {
		super();
		bojica = new HashMap<String, Bojica>();
	}
	
	public boolean dodaj(Bojica b) {
		if(bojica.containsKey(b.getSerijskiBroj()))
			return false;
		
		if(bojica.size() < raspolozivaMesta) {
			bojica.put(b.getSerijskiBroj(), b);
			return true;
		}
		
		return false;
	}	
	
	public int prebroj(double granica) {
		int ret = 0;
		for(Bojica b : bojica.values()) {
			if (b.getCena() > granica) 
				ret++;
		}
		return ret;
	}
	@Override
	public String toString() {
		if(bojica.size() == 0)
			return "\nPernica je prazna!";
		
		String s = "\nU pernici se nalaze sledece bojice:\n";
		for(Bojica b : bojica.values())
			s += b + "\n";
		
		return s;
	}
	
	public static void main(String[] args) {
		Bojica b1 = new Bojica("123abc", 23.9, "drvena", "zelena");
		Bojica b2 = new Bojica("456mnk", 57.4, "vostana", "plava");
		Bojica b3 = new Bojica("789edf", 45.6, "drvena", "zuta");
		Bojica b4 = new Bojica("035sdv", 68.3, "vostana", "bela");
		Bojica b = new Bojica(b1);
		
		System.out.println(b);
		b.akcijskaCena(7);
		System.out.println(b);
		
		Pernica p = new Pernica();
		
		p.dodaj(b1);
		p.dodaj(b2);
		p.dodaj(b3);
		p.dodaj(b4);
		System.out.println(p.toString());
	
		System.out.println("broj bojica sa cenom vecom od zadate: " + p.prebroj(50.5));
	}
	
	
}
