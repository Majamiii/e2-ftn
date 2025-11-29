package novogodisnji_paketic;

public class NovogodisnjiPaketic {

	private String opis;
	private String namenjen; //za decaka, za devojcicu
	private boolean spakovan, zasluzen, spremanZaIsporuku;
	private int minimalanUzrast;

	
	public NovogodisnjiPaketic(String opis, String namenjen, boolean spakovan, boolean zasluzen,
			boolean spremanZaIsporuku, int minimalanUzrast) {
		super();
		this.opis = opis;
		this.namenjen = namenjen;
		this.spakovan = spakovan;
		this.zasluzen = zasluzen;
		this.spremanZaIsporuku = spremanZaIsporuku;
		this.minimalanUzrast = minimalanUzrast;
	}

	public String getOpis() {
		return opis;
	}
	public void setOpis(String opis) {
		this.opis = opis;
	}
	public String getNamenjen() {
		return namenjen;
	}
	public void setNamenjen(String namenjen) {
		this.namenjen = namenjen;
	}
	public boolean isZasluzen() {
		return zasluzen;
	}
	public void setZasluzen(boolean zasluzen) {
		this.zasluzen = zasluzen;
	}
	public boolean isSpremanZaIsporuku() {
		return spremanZaIsporuku;
	}
	public void setSpremanZaIsporuku(boolean spremanZaIsporuku) {
		this.spremanZaIsporuku = spremanZaIsporuku;
	}
	public boolean isSpakovan() {
		return spakovan;
	}
	public void setSpakovan(boolean spakovan) {
		this.spakovan = spakovan;
	}
	public int getMinimalanUzrast() {
		return minimalanUzrast;
	}
	public void setMinimalanUzrast(int minimalanUzrast) {
		this.minimalanUzrast = minimalanUzrast;
	}
	

}
