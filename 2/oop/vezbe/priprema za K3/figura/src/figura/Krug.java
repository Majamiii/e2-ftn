package figura;

public class Krug {
	private double r;

	public double getR() {
		return r;
	}

	public void setR(double r) {
		this.r = r;
	}

	public Krug(double r) {
		super();
		this.r = r;
	}

	
	public Krug(Krug k) {
		r=k.r;
	}
	
	public double obim() {
		return 2*r*Math.PI;
	}
	public double povrsina() {
		return r*r*Math.PI;
	}

	@Override
	public String toString() {
		return "Krug [r=" + r + "]";
	}
}
