package student_ognjen;

public class Kolokvijum extends Test {

	public Kolokvijum() {
		super();
		// TODO Auto-generated constructor stub
	}

	public Kolokvijum(String naziv, int osvojeniPoeni) {
		super(naziv, osvojeniPoeni);
		// TODO Auto-generated constructor stub
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
		String k = "----------KOLOKVIJUM:-----------";
		k += "\n naziv: " + naziv + "\n" + "osvojeni poeni: " + osvojeniPoeni + "\n";
		k += "-----------------------------------------";
		return k;
	}
	
	
}
