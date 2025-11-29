package student_ognjen;

public abstract class Test {
	protected String naziv;
	protected int osvojeniPoeni;
	public Test(String naziv, int osvojeniPoeni) {
		super();
		this.naziv = naziv;
		this.osvojeniPoeni = osvojeniPoeni;
	}
	public Test() {
		super();
		this.naziv = "";
		this.osvojeniPoeni = 0;
	}
	public int getOsvojeniPoeni() {
		return osvojeniPoeni;
	}
	public void setOsvojeniPoeni(int osvojeniPoeni) {
		this.osvojeniPoeni = osvojeniPoeni;
	}
	
	public abstract boolean polozio();
	public String getNaziv() {
		return naziv;
	}
	public void setNaziv(String naziv) {
		this.naziv = naziv;
	}
	
	
	
}