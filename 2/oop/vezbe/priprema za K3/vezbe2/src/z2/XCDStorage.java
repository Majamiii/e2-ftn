package z2;

import java.util.ArrayList;

public class XCDStorage {

	
	private ArrayList<CDDisk> diskovi;
	
	XCDStorage(){
		this.diskovi = new ArrayList<>();
	}
	
	public boolean dodaj(CDDisk disk) {
		for (CDDisk d: diskovi) {
			if (d.getId() == disk.getId()) {
				return false;
			}
		}
		return diskovi.add(disk);
	}
	
	public CDDisk ukloni(int id) {
		
		for (int i=0; i<diskovi.size();i++) {
			if(diskovi.get(i).getId() == id) {
				return diskovi.remove(i);
			}
		}
		return null;		
	}
	
	public CDDisk pronadji(int id) {
		
		for (int i=0; i<diskovi.size();i++) {
			if(diskovi.get(i).getId() == id) {
				return diskovi.get(i);
			}
		}
		return null;		
	}
	
	public void isprazni() {
		diskovi.clear();
	}

	@Override
	public String toString() {
		String retVal = "\nDiskovi: ";
		
		for(CDDisk d: diskovi) {
			retVal += d + "\n";
		}
		
		return retVal;
	}
	
	
	
	
}
