package group5;
//Author: Brian Bauman

import java.util.ArrayList;
import java.util.Stack;

import stdlib.StdIn;
import stdlib.StdOut;

public class ParseXML {

	public static void main(String[] args) {
		StdOut.print("Enter the file path of the XML to be parsed: ");
		String filePath = StdIn.readLine();
		
		StdIn.fromFile(filePath);
		String[] tokenStrings = StdIn.readAllStrings();
		
		ArrayList<XMLToken> tokens = new ArrayList<XMLToken>();
				
		for (String tokenString : tokenStrings) {
			XMLToken token = new XMLToken(tokenString);
			tokens.add(token);
		}
		
		Stack<String> tagNames = new Stack<String>();
		for (XMLToken token : tokens) {
			if (token.isOpeningTag()) {
				StdOut.println(token.toString());
				
				tagNames.push(token.tagName());
			} else if (token.isClosingTag()) {
				StdOut.println(token.toString());
				
				if (tagNames.empty()) {
					StdOut.println("The closing tag " + token.toString() + " has no matching opening tag.");
					System.exit(0);
				}
				
				if (!token.tagName().equals(tagNames.pop())) {
					StdOut.println("The closing tag " + token.toString() + " does not match the previous opening tag.");
					System.exit(0);
				}
			} else if (token.isSelfClosingTag()) {
				StdOut.println(token.toString());
				
			} else {
				
				if (!token.isData()) {
					StdOut.println("Malformed XML. Token: " + token.toString());
					System.exit(0);
				}
				
				StdOut.println(token.toString());
			}
		}
		
		if (!tagNames.empty()) {
			StdOut.print("There are opening tags with no mathing closing tags: ");
			
			while (!tagNames.empty()) {
				if (tagNames.size() == 1) StdOut.println(tagNames.pop() + ". ");
				else StdOut.print(tagNames.pop() + ", ");
			}
			
			System.exit(0);
		}
	} 
}
