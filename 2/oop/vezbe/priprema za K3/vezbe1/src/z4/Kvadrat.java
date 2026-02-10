package z4;

public class Kvadrat extends Pravougaonik {

	public Kvadrat() {
		super(1,1);
		// TODO Auto-generated constructor stub
	}

	public Kvadrat(double a) {
		super(a, a);
		// TODO Auto-generated constructor stub
	}
	
	public void setA(double a) {
		this.a=a;
		this.b=a;
	}
	public void setB(double a) {
		super.setA(a);
		super.setB(a);
	}

	@Override
	public String toString() {
		return "Kvadrat [a=" + a + ", getObim()=" + getObim() + ", getPovrsina()=" + getPovrsina() + "]";
	}
	

}
