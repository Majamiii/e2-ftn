package vezbanje3;

import java.util.Scanner;

public class strings_vezba {

	public static void main(String[] args) {
		String original, reverse = "";
	    Scanner in = new Scanner(System.in);
		System.out.println("Enter a string to reverse");
		
		original = in.nextLine();
	    in.close();
	 
	    int length = original.length();
	 
	    for ( int i = length - 1 ; i >= 0 ; i-- )
	    	reverse = reverse + original.charAt(i);
	    
	    
	    System.out.println(original.replaceAll("\\s+",""));
	    System.out.println(reverse.replaceAll("\\s+",""));
	    Boolean b = (original.equalsIgnoreCase(reverse));
	    System.out.println("Converted to Bool: " + b);
	    if (b)
	    	System.out.println("uneti izraz je palondom");
	    else
	    	System.out.println("nije palindrom jbgy");
	}

}
