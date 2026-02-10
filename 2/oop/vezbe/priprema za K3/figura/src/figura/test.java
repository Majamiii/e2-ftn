package figura;

public class test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Pravougaonik p = new Pravougaonik(3,4);
		
		System.out.println(p.toString());
		
		p.setA(10);
		System.out.println(p.toString());
		
		Krug k=new Krug(2);
		System.out.println(k.toString());
	}

}