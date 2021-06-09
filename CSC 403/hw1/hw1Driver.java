/* CSC 403
 * 
 * Your name goes here
 * 
 * Get help from anyone?  put that here
 * 
 * Homework 1 Driver 
 * 
 * Instructions:  using sizeTest  as a template, create additional functions to test
 *                the member functions in your LinkedListST implementation.
 *                AND
 *                create a reasonable set of test cases for each; 
 *                call your testing functions from main
 *                
 */
package hw1;

import stdlib.StdIn;
import stdlib.StdOut;

public class hw1Driver {

		public static void main(String[] args)
		{		
			// the simple testing code from the textbook pg 370
			// you may delete/comment this out if you wish
			LinkedListST<String, Integer> st = new LinkedListST<>();
			StdIn.fromFile("data/tinyST.txt");
			for (int i = 0; !StdIn.isEmpty(); i++)
			{
				String key = StdIn.readString();
				st.put(key, i);
			}
			for (String s : st.keys())
				StdOut.println(s + " " + st.get(s));
			
			//size() tests
			sizeTest("",0);	// test size on an empty ST (symbol table)
			sizeTest("abcde",5);	// test size on a non-empty ST
			sizeTest("Brian Bauman", 8); // test size on an array with repeated keys
			
			//secondMaxKey() tests
			secondMaxKeyTest("", null); //test secondMaxKey on an empty ST
			secondMaxKeyTest("a", null); //test secondMaxKey on a ST with only one value
			secondMaxKeyTest("abcde", "d"); //test secondMaxKey on a non-empty ST
			secondMaxKeyTest("aaabbbccc", "b"); //test secondMaxKey on a ST with repeated keys 
			
			//rank() tests
			rankTest("", "a", 0); //test rank on an empty ST
			rankTest("a", "a", 0); //test rank on a ST containing only the relevant value
			rankTest("abcde", "e", 4); //test rank on a non-empty ST
			rankTest("abcde", "z", 5); //test rank when the ST does not include the specified key
			rankTest("abcde", null, 0); //test rank when a null key is passed
			
			//floor() tests
			floorTest("", "a", null); //test floor on an empty ST
			floorTest("abcde", "f", "e"); //test floor on a non-empty ST
			floorTest("bcdef", "a", null); //test floor when all keys are greater than the specified key
			floorTest("abcde", "a", "a"); //test floor when the specified key exists in the ST
			
			//inverse() tests
			inverseTest("", "", "", ""); //test inverse on an empty ST
			inverseTest("abcde", "01234", "01234", "abcde"); //test inverse on a non-empty ST
			inverseTest("aaabbbccc", "012345678", "258", "abc"); //test inverse on a ST with repeated keys			
		}

		// size() testing function.
		// param vals: all substrings of length 1 are added to the ST
		// param answer: the correct value of the ST for the given input
		public static void sizeTest(String vals, int answer) {
			
			//Create and populate the table from the input string vals
			LinkedListST<String,Integer> aList = new LinkedListST<String,Integer>();
			for (int i=0; i < vals.length(); i++) {
				aList.put(vals.substring(i, i+1),i);
			}
			
			//Call the size function
			int result = aList.size();
			
			//Report result
			if (result == answer)  // test passes
				StdOut.format("sizeTest: Correct  String %s Answer: %d\n", vals, result);
			else
				StdOut.format("sizeTest: *Error*  String %s Answer: %d\n", vals, result);
		}
		
		// secondMaxKey() testing function
		// param vals: all substrings of length 1 are added to the ST
		// param answer: the correct value of the ST for the given input
		public static void secondMaxKeyTest(String vals, String answer) {
			
			//Create and populate the table from the input string vals
			LinkedListST<String,Integer> aList = new LinkedListST<String,Integer>();
			for (int i=0; i < vals.length(); i++) {
				aList.put(vals.substring(i, i+1),i);
			}
			
			//Call the secondMaxKey function
			String result = aList.secondMaxKey();
			
			//Report result
			if ((result == null && answer == null) || result.equals(answer))  // test passes
				StdOut.format("secondMaxKeyTest: Correct  String %s Answer: %s\n", vals, result);
			else
				StdOut.format("secondMaxKeyTest: *Error*  String %s Answer: %s\n", vals, result);
		}
		
		// rank() testing function
		// param vals: all substrings of length 1 are added to the ST
		// param key: the key whose rank to gather
		// param answer: the correct value of the rank for the given input
		public static void rankTest(String vals, String key, int answer) {
			
			//Create and populate the table from the input string vals
			LinkedListST<String,Integer> aList = new LinkedListST<String,Integer>();
			for (int i=0; i < vals.length(); i++) {
				aList.put(vals.substring(i, i+1),i);
			}
			
			//Call the rank function
			int result = aList.rank(key);
			
			//Report result
			if (result == answer)  // test passes
				StdOut.format("rankTest: Correct  String %s, Key: %s, Answer: %d\n", vals, key, result);
			else
				StdOut.format("rankTest: *Error*  String %s, Key: %s, Answer: %d\n", vals, key, result);
		}
		
		// floor() testing function
		// param vals: all substrings of length 1 are added to the ST
		// param key: the key whose floor to gather
		// param answer: the correct value of the floor for the given input
		public static void floorTest(String vals, String key, String answer) {
			
			//Create and populate the table from the input string vals
			LinkedListST<String,Integer> aList = new LinkedListST<String,Integer>();
			for (int i=0; i < vals.length(); i++) {
				aList.put(vals.substring(i, i+1),i);
			}
			
			//Call the rank function
			String result = aList.floor(key);
			
			//Report result
			if ((result == null && answer == null) || result.equals(answer))  // test passes
				StdOut.format("floorTest: Correct  String %s, Key: %s, Answer: %s\n", vals, key, result);
			else
				StdOut.format("floorTest: *Error*  String %s, Key: %s, Answer: %s\n", vals, key, result);
		}

		// inverse() testing function
		// param keys: the keys of the original ST
		// param vals: the values of the original ST
		// param answerKeys: the keys of the resulting ST
		// param answerVals: the values of the resulting ST
		public static void inverseTest(String keys, String vals, String answerKeys, String answerVals) {
			
			//Validate input
			if (keys.length() != vals.length()) throw new RuntimeException("Input mismatch.");
			
			LinkedListST<String,String> aList = new LinkedListST<String,String>();
			for (int i=0; i < vals.length(); i++) {
				aList.put(keys.substring(i,  i+1), vals.substring(i, i+1));
			}
			
			//Call the inverse function
			LinkedListST<String, String> invertedList = aList.inverse();
			
			String resultKeys = "";
			String resultVals = "";
			for (String key : invertedList.keys()) {
				resultKeys += key;
				resultVals += invertedList.get(key);
			}
			
			//Report result
			if (resultKeys.equals(answerKeys) && resultVals.equals(answerVals))  // test passes
				StdOut.format("inverseTest: Correct  Keys: %s, Vals: %s, Answer keys: %s, Answer vals: %s\n", keys, vals, resultKeys, resultVals);
			else
				StdOut.format("inverseTest: *Error*  Keys: %s, Vals: %s, Answer keys: %s, Answer vals: %s\n", keys, vals, resultKeys, resultVals);
		}
		
}
