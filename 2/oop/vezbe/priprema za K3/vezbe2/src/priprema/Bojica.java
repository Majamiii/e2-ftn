package priprema;

public class Bojica implements IzracunavanjeCene {
	private String serijskiBroj;
	private double cena;
	private String boja;
	private String tip;
	public Bojica(String serijskiBroj, double cena, String boja, String tip) {
		super();
		this.serijskiBroj = serijskiBroj;
		this.cena = cena;
		this.boja = boja;
		this.tip = tip;
	}
	
	
	public Bojica(Bojica b) {
		super();
		this.serijskiBroj = b.serijskiBroj;
		this.cena = b.cena;
		this.boja = b.boja;
		this.tip = b.tip;
	}
	
	public String getSerijskiBroj() {
		return serijskiBroj;
	}

	public double getCena() {
		return cena;
	}
	
	public boolean akcijskaCena(double akcijska) {
		if (akcijska <= 0) {
			System.out.println("Neuspesan pokusaj smanjivanja cene!");
			return false;
		}
		
		cena *= (100-akcijska)*0.01;
		System.out.println("Cena je snizena za " + akcijska + "%.");
		return true;
	}



	@Override
	public String toString() {
		return "Bojica [serijskiBroj=" + serijskiBroj + ", cena=" + cena + ", boja=" + boja + ", tip=" + tip + "]";
	}
	
	
	

}
