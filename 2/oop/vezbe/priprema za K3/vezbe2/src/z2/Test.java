package z2;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		CDDisk cdd = new CDDisk();
		CDDisk cdd2 = new CDDisk(1, "mix","ex yu bendovi");
		CDDisk cdd3 = new CDDisk(4, "evrovizija 2021", "razni");
		System.out.println(cdd);
		System.out.println(cdd2);

		System.out.println(cdd2.getIzvodjac());
		
		XCDStorage lista = new XCDStorage();
		lista.dodaj(cdd3);
		System.out.println(lista);
		
		lista.dodaj(cdd2);
		lista.dodaj(cdd);
		System.out.println(lista);
		
		lista.ukloni(-1);
		System.out.println(lista);
		

		System.out.println(lista.pronadji(4));
		lista.isprazni();
		System.out.println(lista);
		

		System.out.println("-----------------------");
		

		XCDStorageMap mapa = new XCDStorageMap();
		mapa.dodaj(cdd3);
		System.out.println(mapa);
		
		mapa.dodaj(cdd2);
		mapa.dodaj(cdd);
		System.out.println(mapa);
		
		mapa.ukloni(-1);
		System.out.println(mapa);
		

		System.out.println(mapa.pronadji(4));
		mapa.isprazni();
		System.out.println(mapa);
	}

}
