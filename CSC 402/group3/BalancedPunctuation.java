package group3;
// Author: Brian Bauman

import stdlib.*;

public class BalancedPunctuation {

	public static void main(String[] args) {
		
		StdOut.print("Please enter a string: ");
		String input = StdIn.readLine();
		Stack<Character> thisStack = new Stack<Character>();
		
		for (int i = 0; i < input.length(); i++) {
			Character thisChar = input.charAt(i);
			
			if (thisChar == '{' ||
				thisChar == '[' ||
				thisChar == '(') {
				thisStack.push(thisChar);
			}
			else if (thisChar == '}' ||
					thisChar == ']' ||
					thisChar == ')') {
				if (thisStack.isEmpty()) throw new RuntimeException("Unbalanced string!");
				Character poppedChar = thisStack.pop();
				if (thisChar == '}' && poppedChar != '{' ||
					thisChar == ']' && poppedChar != '[' ||
					thisChar == ')' && poppedChar != '(') {
					throw new RuntimeException("Unbalanced string!");
				}

			}
		}
		
		StdOut.println("Your string is balanced!");
	}
}
