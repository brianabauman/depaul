package group3;
// Author: Brian Bauman

import stdlib.*;
import java.text.NumberFormat;
import java.util.Locale;

public class LetterFrequencies {

	public static void main(String[] args) {
		
		StdOut.print("Please enter the pathname or URL of the book file: ");
		StdIn.fromFile(StdIn.readLine());
		
		int[] letterFrequencies = new int[26];
		
		while (StdIn.hasNextChar()) {
			char thisChar = StdIn.readChar();
			
			if (thisChar >= 97 && 
				thisChar <= 122) {
				letterFrequencies[thisChar - 97] += 1;
			}
		}
		
		StdOut.println("Letter frequencies in data/tale.txt");
		for (char i = 0; i < 26; i++) {			
			String thisChar = ((Character)(char)(i + 97)).toString();
			int count = letterFrequencies[i];
			
			NumberFormat numberFormat = NumberFormat.getNumberInstance(Locale.US);
			String formattedCount = numberFormat.format(count);
			
			StdOut.printf("%-1s %10s %n", thisChar, formattedCount);
		}
	}
}
