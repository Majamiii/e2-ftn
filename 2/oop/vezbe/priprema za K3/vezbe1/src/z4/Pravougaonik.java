package z4;

public class Pravougaonik extends GeometrijskaFigura {
	
	protected double a,b;

	@Override
	public String toString() {
		return "Pravougaonik [a=" + a + ", b=" + b + ", getObim()=" + getObim() + ", getPovrsina()=" + getPovrsina()
				+ "]";
	}

	public double getA() {
		return a;
	}

	public void setA(double a) {
		this.a = a;
	}

	public double getB() {
		return b;
	}

	public void setB(double b) {
		this.b = b;
	}

	public Pravougaonik(double a, double b) {
		super();
		this.a = a;
		this.b = b;
	}
	

	public Pravougaonik() {
		super();
		this.a = 1;
		this.b = 1;
	}


	@Override
	public double getObim() {
		// TODO Auto-generated method stub
		return 2*(a+b);
	}

	@Override
	public double getPovrsina() {
		// TODO Auto-generated method stub
		return a*b;
	}

}
