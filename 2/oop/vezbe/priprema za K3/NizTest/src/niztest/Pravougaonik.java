package figura;

import figura.Pravougaonik;

public class Pravougaonik {
	private double a;
	private double b;
	public Pravougaonik(double a, double b) {
		super();
		this.a = a;
		this.b = b;
	}
	
	public Pravougaonik(Pravougaonik p) {
		a=p.a;
		b=p.b;
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
	
	public double obim() {
		return 2*(a+b);
	}
	public double povrsina() {
		return a*b;
	}

	@Override
	public String toString() {
		return "pravougaonik [a=" + a + ", b=" + b + "]";
	}

}
