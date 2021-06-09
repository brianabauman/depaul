package pa2;

import java.io.File;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Stack;

public class ConvexHull {

	private static class Point {
		int x;
		int y;
		
		public Point() { }
	}
	
	private static Point lowestPoint = new Point();
	
	public static void main(String[] args) {
		
		try {
				
			//Gather the location of the test file
			Scanner reader = new Scanner(System.in);
			System.out.print("Enter the path of the file relative to the current directory: ");
			File file = new File(reader.nextLine());
			reader.close();
					
			//Gather all of the points in the input file
			LinkedList<Point> pointList = new LinkedList<Point>();
			reader = new Scanner(file);
			while (reader.hasNextLine()) {
				
				String data = reader.nextLine();
				if (!data.isEmpty()) {
					
					String[] coordinates = data.split(" ");
					if (coordinates.length < 2) 
					{
						reader.close();
						throw new Exception("Bad coordinates encountered: " + data + ".");
					}

					Point thisPoint = new Point();
					thisPoint.x = Integer.parseInt(coordinates[0]);
					thisPoint.y = Integer.parseInt(coordinates[1]);
					
					pointList.add(thisPoint);
				}
			}
			Point[] points = pointList.toArray(new Point[pointList.size()]);
			reader.close();		
			
			//Choose a starting point based on the y-coordinate
			lowestPoint = points[0];
			for (Point p : points) {
				if ((p.y < lowestPoint.y) ||
					(p.y == lowestPoint.y && p.x < lowestPoint.x)) {
					lowestPoint = p;
				}
			}			
			System.out.println("The lowest point is (" + lowestPoint.x + ", " + lowestPoint.y + ").");
			
			//Sort the points with respect to the polar angle they make with lowestPoint and the x-axis
			points = mergeSort(points);

			//Collect a list of points on the convex hull
			Stack<Point> convexHull = new Stack<Point>();
			convexHull.push(points[0]);
			convexHull.push(points[1]);
			
			//Parse the points to determine the convex hull
			for (int i = 2; i < points.length; i++) {

				Point end = points[i];
				Point pivot = convexHull.pop();
				Point start = convexHull.pop();
				
				while (convexHull.size() > 2) {
					if (isLeftTurn(start, pivot, end)) {
						convexHull.push(start);
						convexHull.push(pivot);
						convexHull.push(end);
					} else {
						pivot = start;
						start = convexHull.pop();
					}
				}
			}
			
			//Print the convex hull
			System.out.println("The convex hull is: ");
			while (!convexHull.isEmpty()) {
				Point next = convexHull.pop();
				System.out.println("(" + next.x + ", " + next.y + ")");
			}
			
		} catch (Exception ex) {
			System.out.println(ex.toString());
			System.exit(1);
		}
	}
	
	private static Point[] mergeSort(Point[] points) {
		if (points.length >= 2) {
			int middle = points.length / 2;

			//Split the array into subarrays
			Point[] left = new Point[middle + 1];
			for (int i = 0; i < middle + 1; i++)
				left[i] = points[i];

			Point[] right = new Point[points.length - middle - 1];
			for (int i = middle + 1; i < points.length; i++)
				right[i] = points[i];
			
			//Call the algorithm recursively
			mergeSort(left);
			mergeSort(right);
			
			//Merge the two halves
			merge(left, right, points);
		}
		
		return points;
	}
	
	private static Point[] merge(Point[] left, Point[] right, Point[] points) {	
		int l = 0;
		int r = 0;
		
		for (int i = 0; i < points.length; i++) {
			if (r >= right.length || (l < left.length && polarAngle(lowestPoint, left[l]) < polarAngle(lowestPoint, right[r]))) {
				points[i] = left[l];
				l++;
			} else {
				points[i] = right[r];
				r++;
			}
		}
		
		return points;
	}
	
	private static double polarAngle(Point reference, Point point) {
		return Math.atan2(point.y - reference.y, point.x - reference.x);
	}
	
	private static boolean isLeftTurn(Point start, Point turn, Point end) {
		double crossProduct = ((turn.x - start.x) * (end.y - start.y)) - ((turn.y - start.y) * (end.x - start.x));
		if (crossProduct >= 0) return true;
		else return false;
	}
}
