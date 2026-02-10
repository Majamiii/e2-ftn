package niztest;

public class NizTest {

	public static void main(String[] args) {

		int niz[] = new int[5];
		niz[0]=4;
		niz[1]=6;
		niz[2]=7;
		
		for(int i=0;i<niz.length;i++) {
			System.out.println("Element na poziciji " + i + " je " + niz[i]);
		}
		System.out.println("\n");
		int niz2[] = {2,4,6,9,10};
		
		for(int i=0;i<niz.length;i++) {
			System.out.println("Element na poziciji " + i + " je " + niz2[i]);
		}
		
		Pravougaonik pravougaonici[] = new Pravougaonik[5];
	
		pravougaonici[0] = new Pravougaonik(3,5);
		
		

	}

}
