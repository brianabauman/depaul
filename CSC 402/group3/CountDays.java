package group3;
// Author: Brian Bauman

import stdlib.*;

public class CountDays {

	public static void main(String[] args) {
		
		StdOut.print("Please enter a starting date: ");
		Group3Date startingDate = new Group3Date(StdIn.readLine());
		StdOut.print("Please enter an ending date: ");
		Group3Date endingDate = new Group3Date(StdIn.readLine());
		
		int count = startingDate.countDaysUntil(endingDate);
		StdOut.print("There are ");
		StdOut.print(count);
		StdOut.println(" days between these dates.");
	}
}
