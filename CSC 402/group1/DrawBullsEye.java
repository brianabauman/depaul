package group1;
import stdlib.*;
// Author: Brian Bauman

public class DrawBullsEye {

	public static void main(String[] args) {
		StdDraw.setPenColor(StdDraw.GREEN);
		StdDraw.filledCircle(0.5, 0.5, 0.5);
		StdDraw.setPenColor(StdDraw.BLUE);
		StdDraw.filledCircle(0.5, 0.5, 0.375);
		StdDraw.setPenColor(StdDraw.RED);
		StdDraw.filledCircle(0.5, 0.5, 0.25);
		StdDraw.setPenColor(StdDraw.YELLOW);
		StdDraw.filledCircle(0.5,  0.5,  0.125);
	}

}
