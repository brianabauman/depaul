// CSC 403 Programming assignment 2
// version 1.0
//  Complete the implementation of the SortedArrayST 
//     by completing the TO DO items
//   This is a simple variation of the example from 3.2
//
//   You may not change the other methods without permission
//      if you want to do this, your probably on the wrong track
//
//   You may add additional methods for modularity
//   You may not use other Java data structures (e.g. ArrayList, HashSet, etc)

package hw2;   // change the package if you want

import java.util.Arrays;
import javax.management.RuntimeErrorException;
import stdlib.StdOut;

public class SortedArrayST<Key extends Comparable<Key>, Value> {
	private static final int MIN_SIZE = 2;
	private Key[] keys;      // the keys array
	private Value[] vals;    // the values array
	private int N = 0;       // size of the symbol table, 
							 // may be different from the size of the arrays
	
	/**
	 * Initializes an empty symbol table.
	 */
	public SortedArrayST() {
		this(MIN_SIZE);
	}
	
	/**
	 * Initializes an empty symbol table of given size.
	 */
	@SuppressWarnings("unchecked")
	public SortedArrayST(int size) {
		keys = (Key[])(new Comparable[size]);
		vals = (Value[])(new Object[size]);
	}
	
	/**
	 * Initializes a symbol table with given sorted key-value pairs.
	 * If given keys list is not sorted in (strictly) increasing order,
	 * then the input is discarded and an empty symbol table is initialized.
	 */
	public SortedArrayST(Key[] keys, Value[] vals) {
		this(keys.length < MIN_SIZE ? MIN_SIZE : keys.length);
		N = (keys.length == vals.length ? keys.length : 0);
		int i;
		for (i = 1; i < N && keys[i].compareTo(keys[i - 1]) > 0; i++);
		if (i < N) { // input is not sorted
			System.err.println("SortedArrayST(Key[], Value[]) constructor error:");
			System.err.println("Given keys array of size " + N + " was not sorted!");
			System.err.println("Initializing an empty symbol table!");
			N = 0;
		} else {
			for (i = 0; i < N; i++) {
				this.keys[i] = keys[i];
				this.vals[i] = vals[i];
			}
		}
	}
	
	/**
	 * Returns the keys array of this symbol table.
	 */
	public Comparable<Key>[] keysArray() {
		return keys;
	}
	
	/**
	 * Returns the values array of this symbol table.
	 */
	public Object[] valsArray() {
		return vals;
	}
	
	
	/**
	 * Returns the number of keys in this symbol table.
	 */
	public int size() {
		return N;
	}
	
	/**
	 * Returns whether the given key is contained in this symbol table at index r.
	 */
	private boolean checkFor(Key key, int r) {
		return (r >= 0 && r < N && key.equals(keys[r]));
	}
	
	/**
	 * Returns the value associated with the given key in this symbol table.
	 */
	public Value get(Key key) {
		int r = rank(key);
		if (checkFor(key, r)) return vals[r];
		else return null;
	}
	
	/**
	 * Inserts the specified key-value pair into the symbol table, overwriting the old 
	 * value with the new value if the symbol table already contains the specified key.
	 * Deletes the specified key (and its associated value) from this symbol table
	 * if the specified value is null.
	 */
	public void put(Key key, Value val) {
		int r = rank(key);
		if (!checkFor(key, r)) {
			shiftRight(r);
			keys[r] = key;
		} 
		
		vals[r] = val;
	}
	
	/**
	 * Removes the specified key and its associated value from this symbol table     
	 * (if the key is in this symbol table).    
	 */
	public void delete(Key key) {
		int r = rank(key);
		if (checkFor(key, r)) {
			shiftLeft(r);
		}
	}
	
	public boolean contains(Key key) {
		return ( this.get(key)!= null);
	}
	
	/**
	 * Shifts the keys (and values) at indices r and above to the right by one
	 * The key and value at position r do not change.
	 * This function must resize the keys,vals arrays as needed
	 * 
	 */
	private void shiftRight(int r) {
		
		if (N > 0 && r > N - 1) return;
		
		Key[] oldKeys = this.keys;
		Value[] oldVals = this.vals;
		
		this.keys = (Key[])(new Comparable[oldKeys.length + 1]);
		this.vals = (Value[])(new Object[oldVals.length + 1]);
		
		for (int i = 0; i < oldKeys.length; i++) {
			if (i < r) {
				this.keys[i] = oldKeys[i];
				this.vals[i] = oldVals[i];
			} else {
				this.keys[i+1] = oldKeys[i];
				this.vals[i+1] = oldVals[i];
			}
		}
		
		N++;
		
		return;
	}
	
	/**
	 * Shifts the keys (and values) at indices x > r to the left by one
	 * in effect removing the key and value at index r 
	 */
	private void shiftLeft(int r) {
		
		if (r > N - 1) return;
		
		Key[] oldKeys = this.keys;
		Value[] oldVals = this.vals;
		
		this.keys = (Key[])(new Comparable[oldKeys.length - 1]);
		this.vals = (Value[])(new Object[oldVals.length - 1]);
		
		for (int i = 0; i < this.keys.length; i++) {
			if (i < r) {
				this.keys[i] = oldKeys[i];
				this.vals[i] = oldVals[i];
			} else {
				this.keys[i] = oldKeys[i+1];
				this.vals[i] = oldVals[i+1];
			}
		}
		
		N--;
			
		return;	
	}
	
	/**
	 * rank returns the number of keys in this symbol table that is less than the given key. 
	 */
	public int rank(Key key) {
		//Handle an empty array
		if (this.keys.length == 0 || this.keys[this.keys.length - 1] == null) return 0;
		
		int hi = this.keys.length - 1;
		int lo = 0;
		
		while (lo <= hi) {
			int mid = hi + lo / 2;
			
			int cmp = key.compareTo(this.keys[mid]);		
			if (cmp == 0) return mid;
			else if (cmp < 0) hi = mid - 1;
			else if (cmp > 0) lo = mid + 1;
		}
		
		return lo;
	}

	/**
	 * Linear time implementation of rank
	 */
	private int linearTimeRank(Key key) {
		int r;
		for (r = 0; r < N && key.compareTo(keys[r]) > 0; r++);
		return r;
	}
	
	// Compare two ST for equality
	public boolean equals(Object x) {
		
		SortedArrayST<Key, Value> that = (SortedArrayST<Key, Value>)x;
		
		Key[] thisKeys = this.keys;
		Value[] thisValues = this.vals;
		
		Key[] thatKeys = (Key[])that.keysArray();
		Value[] thatValues = (Value[])that.valsArray();
		
		for (int i = 0; i < thisKeys.length; i++) {
			if (thisKeys[i] != null && thisValues[i] != null) {
				Key key1 = thisKeys[i];
				Value val1 = thisValues[i];
				
				if ((!that.contains(key1)) || !val1.equals(that.get(key1))) return false;
			}
		}
		
		for (int j = 0; j < thatKeys.length; j++) {
			if (thatKeys[j] != null && thatKeys[j] != null) {
				Key key1 = thatKeys[j];
				Value val1 = thatValues[j];
				
				boolean a = this.contains(key1);
				Value b = this.get(key1);
				boolean c = val1.equals(b);
				
				if ((!this.contains(key1)) || !val1.equals(this.get(key1))) return false;
			}
		}
				
		return true;
	}
	/**
	 * floor returns the largest key in the symbol table that is less than or equal to key.
	 * it returns null if there is no such key.
	 */
	public Key floor(Key key) {
		
		int hi = this.keys.length - 1;
		int lo = 0;
		
		while (lo <= hi) {
			int mid = (hi + lo) / 2;
			
			int cmp = key.compareTo(this.keys[mid]);		
			if (cmp == 0) return this.keys[mid];
			else if (cmp < 0) hi = mid - 1;
			else if (cmp > 0) lo = mid + 1;
		}
		
		if (hi < 0) return null;
		else return this.keys[hi]; 
	}
	/**
	 * countRange returns the number of keys within the range (key1, key2) (inclusive)
	 * note that keys may not be in order (key1 may be larger than key2)
	 */
	public int countRange(Key key1, Key key2) {
		Key lowKey = key1;
		Key highKey = key2;
		
		if (key2.compareTo(key1) < 0) {
			lowKey = key2;
			highKey = key1;
		}
		
		if (this.contains(highKey) && !lowKey.equals(highKey)) return rank(highKey) - rank(lowKey) + 1;
		else return rank(highKey) - rank(lowKey);
	}
	
	/*
	 *    a Utility function used by the testing framework to
	 *    build and return a symbol table from a pair of strings.
	 *    The individual characters of each string are extracted as substrings of length 1
	 *    and then stored in parallel arrays.
	 *    The parallel arrays are used as input to the SortArrayST constructor
	 *    The characters in the keyData need to be in sorted order.
	 *    
	 */
	public static SortedArrayST<String,String> from (String keyData, String valData) {
		int n = keyData.length();
		if ( n != valData.length()) throw new NullPointerException(" from: mismatch sizes");
		String[] keys = new String[n];
		String[] vals = new String[n];
		for (int i=0; i < n; i++ ) {
			keys[i] = keyData.substring(i, i+1);  // ith key is ith char-string of keyData string
			vals[i] = valData.substring(i, i+1);  // ith key is ith char-string of valData string
		}
		return new SortedArrayST<String, String>(keys,vals);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		//Testing the shiftRight function
		testShiftRight("ABCDE", "12345", 0, " ABCDE", " 12345");
		testShiftRight("ABCDE", "12345", 6, "ABCDE", "12345");
		testShiftRight("ABCDE", "12345", 3, "ABC DE", "123 45");
		
		//Testing the shiftLeft function
		testShiftLeft("ABCDE", "12345", 0, "BCDE", "2345");
		testShiftLeft("ABCDE", "12345", 6, "ABCDE", "12345");
		testShiftLeft("ABCDE", "12345", 3, "ABCE", "1235");
		
		// Testing the rank function
		testRank("A",0,"BDFK","1234");
		testRank("B",0,"BDFK","1234");
		testRank("C",1,"BDFK","1234");
		testRank("D",1,"BDFK","1234");
		testRank("K",3,"BDFK","1234");
		testRank("Z",4,"BDFK","1234");
		
		//Testing the equals function
		testEquals("ABCDE", "12345", "ABCDE", "12345", true);
		testEquals("ABCDE", "12345", "ABDEF", "12345", false);
		testEquals("ABC", "123", "ABCDE", "12345", false);
		testEquals("", "", "", "", true);
		
		//Testing the floor function
		testFloor("ABCDE", "12345", "E", "E");
		testFloor("BCDEF", "12345", "A", null);
		testFloor("ABCDZ", "12345", "E", "D");	
		
		//Testing the countRange function
		testCountRange("ABCDE", "12345", "A", "E", 5);
		testCountRange("ABCDF", "12345", "A", "E", 4);
		testCountRange("ACEGI", "12345", "B", "H", 3);
		testCountRange("ABC", "123", "D", "E", 0);
		testCountRange("", "", "A", "Z", 0);	
				
		// Testing the delete function  (actually testing your shiftLeft implementation)	
		testDelete("ABDFK","12345", "A","BDFK","2345");
		testDelete("ABDFK","12345", "B","ADFK","1345");
		testDelete("ABDFK","12345", "K","ABDF","1234");
		testDelete("", "", "A", "", ""); //Test a delete from an empty ST
		testDelete("ABCDE", "12345", "Z", "ABCDE", "12345"); //Test a delete of a key not in the ST
		
		//Testing the put function
		testPut("AEIOU","13456", "B","2", "ABEIOU","123456");
		testPut("AEIOU", "13456", "A", "2", "AEIOU", "23456"); //Test putting a key that already exits in the ST
		testPut("AEIOU", "13456", "A", null, "EIOU", "3456"); //Test putting a key with a null value	
		testPut("", "", "A", "1", "A", "1"); //Test putting into an empty list
	}
	/*
	 * Test the rank function. 
	 * build a symbol table from the input key,val strings
	 * (keyData characters must be in sorted order)
	 * then call the rank function, compare to the expected answer
	 */
	public static void testRank(String theKey, int expected, String keyData, String valData) {
		SortedArrayST<String, String> x = from(keyData,valData);
		int actual = x.rank(theKey);
		if ( actual == expected)  // test passes
			StdOut.format("rankTest: Correct  String %s Key %s rank: %d\n", keyData, theKey, actual);
		else
			StdOut.format("rankTest: *Error*  String %s Key %s rank: %d\n", keyData, theKey, actual);
			
	}
	/*
	 * Test the Put function. 
	 * build a symbol table from the input key,val strings
	 * (keyData characters must be in sorted order)
	 * then call the rank function, compare to the expected answer
	 */
	public static void testPut(String keyInData, String valInData, 
			                   String putKey, String putVal, 
			                   String keyOutData, String valOutData) {
		SortedArrayST<String, String> actual = from(keyInData,valInData);
		SortedArrayST<String, String> expected = from(keyOutData, valOutData);
		actual.put(putKey, putVal);
		
		
		if ( actual.equals(expected))  // test passes
			StdOut.format("testPut: Correct  Before %s/%s put:%s After: %s/%s\n", keyInData, valInData, putKey, keyOutData, valOutData);
		else
			StdOut.format("testPut: *Error*  Before %s/%s put:%s After: %s/%s\n", keyInData, valInData, putKey, keyOutData, valOutData);
			
	}
	/*
	 * Test the delete function. 
	 * build a symbol table from the input key,val strings
	 * (keyData characters must be in sorted order)
	 * then call the rank function, compare to the expected answer
	 */
	public static void testDelete(String keyInData, String valInData, String delKey, 
								  String keyOutData, String valOutData) {
		SortedArrayST<String, String> actual = from(keyInData,valInData);
		SortedArrayST<String, String> expected = from(keyOutData, valOutData);
				actual.delete(delKey);
		
		
				if ( actual.equals(expected))  // test passes
					StdOut.format("testDelete: Correct  Before %s delete:%s After: %s\n", keyInData, delKey, keyOutData);
				else
					StdOut.format("testDelete: *Error*  Before %s delete:%s After: %s\n", keyInData, delKey, keyOutData);
			
	}
	
	/*
	 * Test the shiftRight function. 
	 * build a symbol table from the input key,val strings
	 * (keyData characters must be in sorted order)
	 * then call the shiftRight function, compare to the expected answer
	 */
	public static void testShiftRight(String keyInData, String valInData, int index, 
								     String keyOutData, String valOutData) {
		SortedArrayST<String, String> actual = from(keyInData,valInData);
		actual.shiftRight(index);
		
		Comparable<String>[] actualKeysArray = actual.keysArray();
		Object[] actualValsArray = actual.valsArray();		
		String actualKeys = "";
		String actualVals = "";
				
		for (int i = 0; i < actual.size(); i++) {
			if (actualKeysArray[i] == null) actualKeys += " ";
			else actualKeys += actualKeysArray[i];
			if (actualValsArray[i] == null) actualVals += " ";
			else actualVals += actualValsArray[i];
		}
				
		if ( actualKeys.equals(keyOutData) && actualVals.equals(valOutData))  // test passes
			StdOut.format("testShiftRight: Correct  Before %s/%s shiftIndex:%d After: %s/%s\n", keyInData, valInData, index, actualKeys, actualVals);
		else
			StdOut.format("testShiftRight: *Error*  Before %s/%s shiftIndex:%d After: %s/%s\n", keyInData, valInData, index, actualKeys, actualVals);			
	}
	
	/*
	 * Test the shiftLeft function. 
	 * build a symbol table from the input key,val strings
	 * (keyData characters must be in sorted order)
	 * then call the shiftLeft function, compare to the expected answer
	 */
	public static void testShiftLeft(String keyInData, String valInData, int index, 
								    String keyOutData, String valOutData) {
		SortedArrayST<String, String> actual = from(keyInData,valInData);
		actual.shiftLeft(index);
		
		Comparable<String>[] actualKeysArray = actual.keysArray();
		Object[] actualValsArray = actual.valsArray();		
		String actualKeys = "";
		String actualVals = "";
				
		for (int i = 0; i < actual.size(); i++) {
			if (actualKeysArray[i] == null) actualKeys += " ";
			else actualKeys += actualKeysArray[i];
			if (actualValsArray[i] == null) actualVals += " ";
			else actualVals += actualValsArray[i];
		}
				
		if ( actualKeys.equals(keyOutData) && actualVals.equals(valOutData))  // test passes
			StdOut.format("testShiftLeft: Correct  Before %s/%s shiftIndex:%d After: %s/%s\n", keyInData, valInData, index, actualKeys, actualVals);
		else
			StdOut.format("testShiftLeft: *Error*  Before %s/%s shiftIndex:%d After: %s/%s\n", keyInData, valInData, index, actualKeys, actualVals);			
	}
	
	/*
	 * Test the equals function. 
	 * build a symbol table from the input key,val strings
	 * (keyData characters must be in sorted order)
	 * then call the equals function, compare to the expected answer
	 */
	public static void testEquals(String keyInData1, String valInData1, 
		                          String keyInData2, String valInData2, boolean equalInd) {
		SortedArrayST<String, String> array1 = from(keyInData1, valInData1);
		SortedArrayST<String, String> array2 = from(keyInData2, valInData2);

		if (array1.equals(array2) == equalInd)  // test passes
			StdOut.format("testEquals: Correct  Array1 %s/%s Array2: %s/%s Equals:%b \n", keyInData1, valInData1, keyInData2, valInData2, equalInd);
		else
			StdOut.format("testEquals: *Error*  Array1 %s/%s Array2: %s/%s Equals:%b \n", keyInData1, valInData1, keyInData2, valInData2, equalInd);
	}

	/*
	 * Test the floor function. 
	 * build a symbol table from the input key,val strings
	 * (keyData characters must be in sorted order)
	 * then call the floor function, compare to the expected answer
	 */
	public static void testFloor(String keyInData, String valInData, String key, String floorIn) {	
		SortedArrayST<String, String> array = from(keyInData, valInData);
		String floorKey = array.floor(key);
		if (floorIn == null) floorIn = "null";
		if (floorKey == null) floorKey = "null";
		
		if (floorKey.equals(floorIn))  // test passes
			StdOut.format("testFloor: Correct  Array %s/%s Key %s Floor:%s \n", keyInData, valInData, key, floorIn);
		else 
			StdOut.format("testFloor: *Error*  Array %s/%s Key %s Floor:%s \n", keyInData, valInData, key, floorIn);
	}
	
	/*
	 * Test the countRange function. 
	 * build a symbol table from the input key,val strings
	 * (keyData characters must be in sorted order)
	 * then call the countRange function, compare to the expected answer
	 */
	public static void testCountRange(String keyInData, String valInData, String key1, String key2, int inpCount) {	
		SortedArrayST<String, String> array = from(keyInData, valInData);
		int count = array.countRange(key1, key2);
		
		if (count == inpCount)  // test passes
			StdOut.format("testCountRange: Correct  Array %s/%s Key1 %s Key2 %s Count:%d\n", keyInData, valInData, key1, key2, inpCount);
		else 
			StdOut.format("testCountRange: *Error*  Array %s/%s Key1 %s Key2 %s Count:%d\n", keyInData, valInData, key1, key2, inpCount);
	}
}
