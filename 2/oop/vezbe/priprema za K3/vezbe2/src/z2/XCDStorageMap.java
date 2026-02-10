package z2;

import java.util.HashMap;

public class XCDStorageMap {

	private HashMap<Integer, CDDisk> diskovi;
	
	public XCDStorageMap() {
		this.diskovi = new HashMap<>();
	}
	
	public CDDisk dodaj(CDDisk disk) {
		if (diskovi.containsKey(disk.getId())) {
			return null;
		}
		return diskovi.put(disk.getId(), disk);
	}
	
	public CDDisk ukloni(int id) {
		if (diskovi.containsKey(id)) {
			return diskovi.remove(id);
		}
		return null;
	}
	
	public CDDisk pronadji(int id) {
		if (diskovi.containsKey(id)) {
			return diskovi.get(id);
		}
		return null;
	}
	
	public void isprazni() {
		diskovi.clear();
	}

	@Override
	public String toString() {
		String retVal = "\nDiskovi: ";
		
		for(CDDisk d: diskovi.values()) {
			retVal += d + "\n";
		}
		
		return retVal;
	}
	
}
