package bojice_klk;


public class Bojica implements IzracunavanjeCene {
	private String serijskiBroj;
	private double cena;
	private String boja;
	private String tip;
	
	public Bojica(Bojica b) {
		super();
		serijskiBroj = b.serijskiBroj;
		cena = b.cena;
		boja = b.boja;
		tip = b.tip;
	}
	
	public Bojica(String serijskiBroj, double cena, String boja, String tip) {
		super();
		this.serijskiBroj = serijskiBroj;
		this.cena = cena;
		this.boja = boja;
		this.tip = tip;
	}

	@Override
	public boolean akcijskaCena(double popust) {
		if(popust <= 0 || popust > 99) {
			System.out.println("Neuspesan pokusaj smanjivanja cene!");
		} else {
			cena -= cena * popust/100;
			System.out.println("Cena je snizena za: " + popust + "% \n");
			return true;
		}
		return false;
	}

	@Override
	public String toString() {
		String retValue = "";
		
		retValue += "\n   Serijski broj: " + serijskiBroj;
		retValue += "\n   Boja:          " + boja;
		retValue += "\n   Tip:           " + tip;
 		retValue += "\n   Cena:          " + cena;
		
		return retValue;
	}

	public String getSerijskiBroj() {
		return serijskiBroj;
	}



	public double getCena() {
		return cena;
	}

	

}
