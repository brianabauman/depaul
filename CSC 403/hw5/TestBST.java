/*
 * Sample timing-data collection program
 * --used in class to explore some of the issues
 * you might consider in designing your testing program.
 * 
 */

package hw5;

import algs31.BinarySearchST;
import stdlib.In;
import stdlib.StdOut;
import stdlib.Stopwatch;

public class TestBST {

	public static void main(String[] args) {
		//you will need some data to put in your STs.
		// you might be able to use these.  OR
		//      you can find some other data source
		
		//int minlen = 2; String file = "data/tinyTale.txt";
		//int minlen = 6; String file = "data/tale.txt";
		int minlen = 8; String file = "data/leipzig1M.txt";
		
		StdOut.println ("BST"); 
		
		// collect timing on building a BinarySearchST 
		testBinarySearchSTBuild(minlen, file);  // collect timing on building 
		
	}
	
	private static void testBinarySearchSTBuild (int minlen, String file) {
		
		// In order to factor out the I/O costs, 
		// I 'read-in' the data into an auxiliary ST 
		// ( this elimates any duplicates and guarantees that every
		//  'put' adds a new value to the table ) 
		//   other iterable collections could be made to work  

		BinarySearchST<String, Integer> st = new BinarySearchST<>();

		In in = new In (file);
		
		while (!in.isEmpty()) {
			String key = in.readString();
			if (key.length() < minlen) continue;
			if (st.contains(key)) { st.put(key, st.get(key) + 1); }
			else                  { st.put(key, 1); }
		}
		
		// its useful to know how many unique values are available 
		StdOut.println("table size: " + st.size());  


	    // do the experiment for varying sizes of N
		int reps = 10;   // to account for a potential coarse-grained timer
					     // might be worth playing with to see how many reps
					     // are needed to ensure precision

		for (int N=1024; N < 300000; N*=2) {
			Stopwatch sw = new Stopwatch();
			for (int r = 1; r <= reps; r++) {   // create and populate the table
				BinarySearchST<String, Integer> test = new BinarySearchST<>();
				// fill from st 
				int count = 1;				    // kludgy code to ensure exactly 
				for ( String key: st.keys()) {  // N values are added from the
					test.put(key, 0);           // large data set
					if (count++ == N) break;
				}
			}
			StdOut.format("%.4f\n",sw.elapsedTime ()/reps);
		}


	}
}
