package skolskiPriborJava;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;

public class Pernica {
	
	private HashMap<String, Bojica> bojice;
	private int raspolozivoMesta = 5;
	
	public Pernica() {
		super();
		bojice = new HashMap<String, Bojica>();
	}
	
	public boolean dodaj(Bojica b) {
		if(bojice.containsKey(b.getSerijskiBroj()))
			return false;
		
		if(bojice.size() < raspolozivoMesta) {
			bojice.put(b.getSerijskiBroj(), b);
			return true;
		}
		
		return false;
	}
	
	public int prebroj(double cena) {
		int brojac = 0;
		
		for(Bojica b : bojice.values())
			if(b.getCena() > cena)
				brojac++;
		
		return brojac;
	}
	
	public ArrayList<Bojica> pretraziPoTipu(String tip) {
		ArrayList<Bojica> listaBojica = new ArrayList<Bojica>();
		
		for(Bojica b : bojice.values())
			if(b.getTip().equals(tip))
				listaBojica.add(b);
		
		return listaBojica;
	}
	
	@Override
	public String toString() {
		if(bojice.size() == 0)
			return "\nPernica je prazna!";
		
		String s = "\nU pernici se nalaze sledece bojice:\n";
		for(Bojica b : bojice.values())
			s += b + "\n";
		
		return s;
	}
	
	private static ArrayList<Bojica> ucitaj(String p) {
		ArrayList<Bojica> bojice = new ArrayList<Bojica>();
		BufferedReader reader = null;
		String linija = null;
		String[] delovi = null;
		
		try {
			reader = new BufferedReader(new FileReader(p));
			while ((linija = reader.readLine()) != null) {
				delovi = linija.split("#");
				String sb = delovi[0];
				delovi = delovi[1].split("\\*");
				bojice.add(new Bojica(sb, Double.parseDouble(delovi[0]), delovi[1], delovi[2]));
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
		
		return bojice;
	}
	
	public static void main(String[] args) {
		ArrayList<Bojica> bojiceIzFajla = ucitaj("bojice.txt");
		Bojica bb = new Bojica(bojiceIzFajla.get(0));
		
		System.out.println(bb);
		bb.akcijskaCena(7);
		System.out.println(bb);
		
		Pernica p = new Pernica();
		
		System.out.println(p);
		
		for(Bojica bojica : bojiceIzFajla)
			if(p.dodaj(bojica))
				System.out.println("Uspesno dodata bojica sa serijskim brojem " + bojica.getSerijskiBroj() + ".");
			else
				System.out.println("Neuspelo dodavanje bojice sa serijskim brojem " + bojica.getSerijskiBroj() + ".");
		
		System.out.println(p);
		
		System.out.println("Broj bojica sa cenom vecom od zadate: " + p.prebroj(50.5));
		
		System.out.println("Drvene bojice: ");
		ArrayList<Bojica> drveneBojice = p.pretraziPoTipu("drvena");
		for(Bojica bojica : drveneBojice)
			System.out.println(bojica);
	}
}
