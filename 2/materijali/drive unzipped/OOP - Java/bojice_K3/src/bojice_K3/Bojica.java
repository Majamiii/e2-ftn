package bojice_K3;

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
		this.boja = b.boja;
		this.cena = b.cena;
		this.tip = b.tip;
	}

	@Override
	public boolean akcijskaCena(double akcija) {	
		if(akcija <= 0) {
			System.out.println("Pogresno unesena cena");
			return false;
		} else {
			cena -= cena * (akcija/100); 
			System.out.printf("Cena je smanjena za %d %%", cena);
			return true;
		}
	}

	@Override
	public String toString() {
		System.out.printf("Bojice su %s boje, kostaju: %dRSD, i sB je %s", boja, cena, serijskiBroj);
		return super.toString();
	}
	
 	public void setSerijskiBroj(String serijskiBroj) {
		this.serijskiBroj = serijskiBroj;
	}
	public void setCena(double cena) {
		this.cena = cena;
	}
	public void setBoja(String boja) {
		this.boja = boja;
	}
	public void setTip(String tip) {
		this.tip = tip;
	}
	public String getBoja() {
		return boja;
	}
	public String getSerijskiBroj() {
		return serijskiBroj;
	}
	public String getTip() {
		return tip;
	}
	public double getCena() {
		return cena;
	}
	
}
