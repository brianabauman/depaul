package group2;
// Author: Brian Bauman

import stdlib.*;

public class Distribution {

	public static void main(String[] args) {
		
		String dataFileName = "data/normaldistribution.txt";
		StdIn.fromFile(dataFileName);
		
		double[] numbers = StdIn.readAllDoubles();
		
		double mean = computeMean(numbers);
		double standardDeviation = computeStandardDeviation(numbers);
		double p1SD = computePercentage(numbers, 1);
		double p2SD = computePercentage(numbers, 2);
		double p3SD = computePercentage(numbers, 3);
		
		StdOut.println("Statistics on the file " + dataFileName);
		StdOut.println("The mean is " + mean);
		StdOut.println("The standard deviation is " + standardDeviation);
		StdOut.println("Percentage of values 1 SD away from mean: " + p1SD);
		StdOut.println("Percentage of values 1 SD away from mean: " + p2SD);
		StdOut.println("Percentage of values 1 SD away from mean: " + p3SD);
	
	}
	
	public static double computeMean(double[] inpNumbers) {
		double sum = 0;
		
		for (double number: inpNumbers) {
			sum += number;
		}
		
		return sum / inpNumbers.length;
	}
	
	public static double computeStandardDeviation(double[] inpNumbers) {
		double sum = 0;	
		double average = computeMean(inpNumbers);	
		
		for (double number: inpNumbers) {
			sum += Math.pow(average - number, 2);
		}
		
		return Math.sqrt(sum / inpNumbers.length);
	}
	
	public static double computePercentage(double[] inpNumbers, int inpStandardDeviations) {
		double mean = computeMean(inpNumbers);
		double standardDeviation = computeStandardDeviation(inpNumbers);
		
		double lowerBound = mean - (inpStandardDeviations * standardDeviation);
		double upperBound = mean + (inpStandardDeviations * standardDeviation);
		
		int count = 0;
		
		for (double number: inpNumbers) {
			if (number > lowerBound && number < upperBound) {
				count++;
			}
		}
		
		return (double) count / inpNumbers.length * 100;	
	}

}
