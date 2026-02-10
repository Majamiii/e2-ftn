package z4;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Krug k1=new Krug();
		
		GeometrijskaFigura gf1 = new Krug();
		
		System.out.println(gf1.getObim());
		System.out.println(k1);
		
		Pravougaonik p = new Pravougaonik();
		Kvadrat k = new Kvadrat();
		
		System.out.println(k);
		System.out.println("--------");
		
		ispisiGeometrijskuFiguru(k1);	
		ispisiGeometrijskuFiguru(p);	
		ispisiGeometrijskuFiguru(k);

	}
	
	public static void ispisiGeometrijskuFiguru(GeometrijskaFigura gf) {
		System.out.println(gf);
	}

}
