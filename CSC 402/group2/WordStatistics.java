package group2;
// Author: Brian Bauman

import stdlib.*;
import java.util.Arrays;

public class WordStatistics {

	public static void main(String[] args) {
		String filePath = StdIn.readLine();
		
		StdIn.fromFile(filePath);
		String[] words = StdIn.readAllStrings();
		
		int[] wordLengths = new int[words.length];
		for (int i = 0; i < words.length; i++) {
			wordLengths[i] = words[i].length();
		}
		
		double average = computeAverage(wordLengths);
		double median = computeMedian(wordLengths);
		
		StdOut.println("The average word length is " + average);
		StdOut.println("The median word length is " + median);
	}
	
	public static double computeAverage(int[] inpNumbers) {
		int sum = 0;
		
		for (int number: inpNumbers) {
			sum += number;
		}
		
		return (double) sum / inpNumbers.length;
	}
	
	public static double computeMedian(int[] inpNumbers) {
		Arrays.sort(inpNumbers);
		
		if (inpNumbers.length % 2 == 0) {
			return ((double) inpNumbers[inpNumbers.length / 2] + inpNumbers[(inpNumbers.length / 2) - 1]) / 2;
		} else {
			return inpNumbers[(inpNumbers.length - 1) / 2];	
		}
	}

}
