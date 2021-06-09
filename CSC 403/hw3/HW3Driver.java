package hw3;  // change this

// driver/tester  program for hw3
// version 1.0

import stdlib.StdIn;
import stdlib.StdOut;

public class HW3Driver {

	public static void main(String[] args)
	{
		// comment in/out calls to focus on a given ToDo method
		sizeTests();
		numLeavesTests();
		lenShortestPathToNullTests();
		getTests();
		deleteTests();
		putTests();
	}
	public static void sizeTests() {
		sizeTest("", 0);	        // test size on an empty symbol table
		sizeTest("a",1);        // test size on a symbol table of size 1 
		sizeTest("aaaaaa", 1);  // test size on a symbol table of size 1 
		sizeTest("ababcd", 4);  // test size on a symbol table of size > 1
		sizeTest("abcde", 5);	// test size on a symbol table of size > 1 
	}
	public static void numLeavesTests() {
		testNumLeaves("",0);
		testNumLeaves("HCADMLZ",4);   // leaves are ADLZ
		testNumLeaves("ABCDEFG",1);   // leaves: G
		testNumLeaves("GFEDCBA",1);   // leaves: A
		testNumLeaves("MABC",1);      // leaves: C
		testNumLeaves("MGLJK",1);     // leaves: F
		testNumLeaves("CBADE",2);   // leaves: A, E
	}

	public static void lenShortestPathToNullTests() {
		testLenShortestPathToNull("C",0);
		testLenShortestPathToNull("CA",0);
		testLenShortestPathToNull("CAD",1);		 // complete BT with 3 nodes
		testLenShortestPathToNull("HCADMLZ",2);  // complete BT with 7 nodes
		testLenShortestPathToNull("HCADMJZGL",2);// complete BT(7) w/ two extra nodes
	}

	public static void getTests() {
		testGet("C","3","C","3");               // ST (C,3), get C.  result 3
		testGet("C","3","D","");                // ST (C,3), get D.  result null
		testGet("CBADE","32145","C","3");       // C in table
		testGet("CBADE","32145","A","1");       // A in table
		testGet("CBADE","32145","E","5");       // E in table
		testGet("HCADMLZ","1245367","A","4");   // A in table
		testGet("HCADMLZ","1245367","D","5");   // D in table
		testGet("HCADMLZ","1245367","Z","7");   // A in table
		testGet("HCADMLZ","1245367","B","");    // B not in table
		testGet("HCADMLZ","1245367","Y","");    // Y not in table
		testGet("ABCDEFG","1234567","A","1");   // A in table
		testGet("MGLJK","12345","G","2");       // G in table
		testGet("MGLJK","12345","Z","");        // Z  not in table
	}
	public static void deleteTests() {
		testDelete("CA","31","C","A","1");
		testDelete("CAD","314","D","CA","31");
		testDelete("ABCDEFG","1234567","G","ABCDEF","123456");  // straight line right
		testDelete("ABCDEFG","1234567","D","ABCEFG","123567");  // straight line right
		testDelete("GFEDCBA","7654321","A","GFEDCB","765432");  // straight line left
		testDelete("GFEDCBA","7654321","D","GFECBA","765321");  // straight line left
		testDelete("HCADMJZ","1234567", "H", "DCAMJZ","423567"); // delete root
		testDelete("HCADMJZGL","123456789", "M", "HCADLJZG","12349678"); // delete M
		testDelete("MJALBCD","1234567","J", "MDALBC","173456"); // delete J
	}
	public static void putTests() {
		testPut("CA","31","C","3","CA","31");  // put existing key-val pair, no change
		testPut("HCADMJZGL","123456789","L","9","HCADMJZGL","123456789");    // put existing key-val pair, no change
		testPut("HCADMJZGL","123456789","L","0","HCADMJZGL","123456780");    // update value  in Leaf
		testPut("HCADMJZGL","123456789","C","0","HCADMJZGL","103456789");    // update value  in middle	
		testPut("HCADMJZGL","123456789","B","0","HCABDMJZGL","1230456789");  // Add new kv in middle
		testPut("ABCEFG","123567","D","4","ABCEDFG","1235467");  // straight line right, add new kv in middle
	}

	/* from
	 * builds a BST using the author's version of put
	 */
	public static BST403<String, String> from(String keys, String vals) {
		if ( keys.length() != vals.length()) 
			throw new IllegalArgumentException("array sizes do not match");

		BST403<String,String> abst = new BST403<String, String>();
		for (int i=0; i < keys.length(); i++) {
			abst.rPut(keys.substring(i, i+1),vals.substring(i,i+1));
		}
		return abst;
	}
	/******************************************* testing functions *******************************/
	//  test size function.
	// param vals: all substrings of length 1 are added to the ST
	// param answer:  the correct value of the ST for the input:vals
	public static void sizeTest( String keys,  int answer ) {

		// create and populate the table from the input string vals
		BST403<String,String> aTree = from(keys,keys);

		//  do the test
		int result = aTree.size();
		//report result
		if ( result == answer)  // test passes
			StdOut.format("sizeTest: Correct  String [ %s ] Answer: %d\n", keys,result);
		else
			StdOut.format("sizeTest: *Error*  String [ %s ] Answer: %d\n", keys,result);
	}

	public static void testNumLeaves( String keys, int answer ) {

		// create and populate the table from the input string 
		BST403<String,String> aTree = from(keys,keys);
		//  do the test
		int result = aTree.numLeaves();

		if ( result == answer)  // test passes
			StdOut.format("testNumLeaves: Correct   Keys: [ %s ]   Answer: %d\n", keys, answer);
		else
			StdOut.format("testNumLeaves: *Error*   Keys: [ %s ]   Answer: %d\n", keys, answer);
	}

	public static void testLenShortestPathToNull( String keys, int answer ) {

		// create and populate the table from the input string 
		BST403<String,String> aTree = from(keys,keys);
		//  do the test
		int result = aTree.lenShortestPathToNull();

		if ( result == answer)  // test passes
			StdOut.format("test lenShortestPathToNull: Correct   Keys: [ %s ]   Answer: %d\n", keys, answer);
		else
			StdOut.format("test lenShortestPathToNull: *Error*   Keys: [ %s ]   Answer: %d\n", keys, answer);
	}



	public static void testGet( String keys, String vals, String key, String answer ) {

		// create and populate the table from the input string 
		BST403<String,String> aTree = from(keys,vals);
		//  do the test
		String result = aTree.get(key);
		if ( (answer.equals("") && result == null) || (answer.equals(result)))  // test passes
			StdOut.format("testGet: Correct  Keys:[ %s ]  Vals:[%s] Get:%s Answer: %s\n", 
					keys, vals, key, answer);
		else
			StdOut.format("testGet: *Error*  Keys:[ %s ]  Vals:[%s] Get:%s Answer: %s\n", 
					keys, vals, key, answer);
	}
	public static void testDelete( String keys, String vals, String key, String exKeys, String exVals ) {

		// create and populate the table from the input string 
		BST403<String,String> testTree = from(keys,vals);
		BST403<String,String> expectedTree = from(exKeys,exVals);
		//  do the test
		testTree.delete(key);
		String actual = testTree.toString();
		String expected = expectedTree.toString();
		if ( actual.equals(expected) && testTree.isValidBST()) // test passes
			StdOut.format("testDelete: Correct  Keys:[ %s ]  Vals:[%s] \n   Delete:%s Result: %s\n", 
					keys, vals, key, actual);
		else
			StdOut.format("testDelete: *Error*  Keys:[ %s ]  Vals:[%s] \n   Delete:%s Result: %s\n",  
					keys, vals, key, actual);
	}

	// keys, vals   are the data for the starting ST
	// pKey, pVal   is the key-value pair to insert
	// exKeys, exVals are the data for the expected ST after the put
	//    this does not test for inserting a null value
	public static void testPut( String keys, String vals, String pKey, 
			String pVal,String exKeys, String exVals ) {

		// create and populate the table from the input string 
		BST403<String,String> testTree = from(keys,vals);
		BST403<String,String> expectedTree = from(exKeys,exVals);
		
		//  do the test
		testTree.put(pKey,pVal);
		
		String actual = testTree.toString();
		String expected = expectedTree.toString();
		if ( actual.equals(expected) ) // test passes
			StdOut.format("testPut: Correct Keys:[%s] Vals:[%s] \n      Put:(%s,%s) Result: %s\n", 
					keys, vals, pKey, pVal, actual);
		else
			StdOut.format("testPut: *Error*  Keys:[%s] Vals:[%s] \n     Put:(%s,%s) Result: %s\n",  
					keys, vals, pKey, pVal, actual);
	}
}
