package priprema;

public abstract class Test {
	protected String naziv;
	protected int osvojeniPoeni;
	
	public Test() {
		super();
		this.naziv = "";
		this.osvojeniPoeni = 0;
	}
	
	public Test(String naziv, int osvojeniPoeni) {
		super();
		this.naziv = naziv;
		this.osvojeniPoeni = osvojeniPoeni;
	}
	
	public abstract boolean polozio();
	
	
	public String getNaziv() {
		return naziv;
	}
	public void setNaziv(String naziv) {
		this.naziv = naziv;
	}
	public int getOsvojeniPoeni() {
		return osvojeniPoeni;
	}
	public void setOsvojeniPoeni(int osvojeniPoeni) {
		this.osvojeniPoeni = osvojeniPoeni;
	}
	
	
}
