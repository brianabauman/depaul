package group1;
import stdlib.*;
// Author: Brian Bauman

public class FindGCD {

	public static void main(String[] args) {
		StdOut.print("Enter a positive integer: ");
		int a = Integer.parseInt(StdIn.readLine());
		StdOut.print("Enter a second positive integer: ");
		int b = Integer.parseInt(StdIn.readLine());
		StdOut.printf("The greatest common divisor is %,d.", euclid(a, b));
	}
	
	public static long euclid(int a, int b) {
		if (b == 0) {
			return a;
		}
		return euclid(b, a%b);
	}

}
