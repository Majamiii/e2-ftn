package priprema;

public class Kolokvijum extends Test {

	public Kolokvijum() {
		super();
	}

	public Kolokvijum(String naziv, int osvojeniPoeni) {
		super(naziv, osvojeniPoeni);
	}

	@Override
	public boolean polozio() {
		if (osvojeniPoeni > 12) {
			return true;
		}
		return false;
	}

	@Override
	public String toString() {
		String k = "--------- KOLOKVIJUM -----------\n";
		k += "naziv: " + naziv + "\n";
		k += "Osvojeno poena: " + osvojeniPoeni + "\n";
		k += "--------------------------------\n";
		return k;
	}

}
