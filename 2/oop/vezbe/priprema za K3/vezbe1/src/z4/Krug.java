package z4;

public class Krug extends GeometrijskaFigura {
	
	private double r;

	public Krug() {
		super();
		// TODO Auto-generated constructor stub
		this.r=1;
	}

	public Krug(double r) {
		super();
		this.r = r;
	}
	
	public double getR() {
		return r;
	}
	
	public void setR(double r) {
		this.r=r;
	}

	@Override
	public double getObim() {
		// TODO Auto-generated method stub
		return 2*r*Math.PI;
	}

	@Override
	public double getPovrsina() {
		// TODO Auto-generated method stub
		return r*r*Math.PI;
	}

	@Override
	public String toString() {
		return "Krug [r=" + r + ", getObim()=" + getObim() + ", getPovrsina()=" + getPovrsina() + "]";
	}
	
}
