package hw3;
/**
 * Version 1.0
 * 
 * Your homework is to complete the methods marked ToDoX.
 * You must not change the declaration of any method.
 */


/**
 *  The B(inary)S(earch)T(ree) class represents a symbol table of
 *  generic key-value pairs.  It supports put, get, and delete methods.
 *  
 *  the book's recursive versions of get and put have been renamed 
 *  rGet  and rPut 
 *  to facilitate testing of your non-recursive versions
 *  
 */
public class BST403<Key extends Comparable<Key>, Value> {
	private Node root;             // root of BST

	private class Node {
		private Key key;           // sorted by key
		private Value val;         // associated data
		private Node left, right;  // left and right subtrees
		
		public Node(Key key, Value val) {
			this.key = key;
			this.val = val;
		}
		
		/**
		 * Appends the preorder string representation of the sub-tree to the given StringBuilder.
		 */
		public void buildString(StringBuilder s) {
			s.append(left == null ? '[' : '(');
			s.append(key + "," + val);
			s.append(right == null ? ']' : ')');
			if (left != null) left.buildString(s);
			if (right != null) right.buildString(s);
		}
	}
	/**
	 * Returns the preorder string representation of the BST.
	 */
	public String toString() {
		StringBuilder s = new StringBuilder();
		root.buildString(s);
		return s.toString();
	}
	
	/**
	 * Initializes an empty symbol table.
	 */
	public BST403() {
	}
	
	/* 
	 * return the size of the tree
	 */
	public int size() {	
		if (root == null) return 0;
		else return size(root.left) + size(root.right) + 1;
	}
	
	private int size(Node x) {
		if (x == null) return 0;
		else return size(x.left) + size(x.right) + 1;
	}
	
	/**
	 * Returns the value associated with the given key.
	 * Returns null if the key is not in the table
	 * 
	 * ToDo 1   write a non-recursive implementation of get
	 * 
	 */
	public Value get(Key key) {		
		Node current = root;
		while (current != null) {
			int cmp = key.compareTo(current.key);
			if (cmp == 0) return current.val;
			else if (cmp < 0) current = current.left;
			else current = current.right;			
		}
		
		return null;
	}
	
	/**
	 * Inserts the specified key-value pair into the symbol table, overwriting the old 
	 * value with the new value if the symbol table already contains the specified key.
	 * 
	 * ToDo 2   write a non-recursive implementation of put
	 * 
	 * 
	 */
	public void put(Key key, Value val) {
		Node current = root;
		while (current != null) {
			int cmp = key.compareTo(current.key);
			if (cmp == 0) {
				current.val = val;
				return;
			} else if (cmp < 0) {
				if (current.left == null) {
					current.left = new Node(key, val);
					return;
				} else current = current.left;
			} else {
				if (current.right == null) {
					current.right = new Node(key, val);
					return;
				} else current = current.right;			
			}
		}
	}
	
	/**
	 * deletes the key (&value) from the table if the key is present
	 * using the the dual of the Hibbard approach from the text. That is, 
	 * for the two-child scenario, delete the node by replacing it 
	 * with it's predecessor (instead of its successor)
	 * 
	 * ToDo 3:  implement a version of delete meeting the above spec
	 * 
	 */
	public void delete(Key key) {
		root = delete(root, key);
	}
	
	private Node delete(Node x, Key key) {
		if (x == null) return null;
		int cmp = key.compareTo(x.key);
		if (cmp < 0) x.left = delete(x.left, key);
		else if (cmp > 0) x.right = delete(x.right, key);
		else {
			if (x.right == null) return x.left;
			if (x.left == null) return x.right;		
			Node t = x;
			x = max(t.left);
			x.left = deleteMax(t.left);
			x.right = t.right;			
		}	
		
		return x;
	}
	
	private Node max(Node x) {
		if (x == null) return null;
		else if (x.right == null) return x;
		else return max(x.right);
	}
	
	private Node deleteMax(Node x) {
		if (x.right == null) return x.left;
		x.right = deleteMax(x.right);
		return x;
	}
	
	/*
	 * equals determines if two BST403s are exactly the same:
	 * same key-value pairs, same structure
	 * recursion might be a good choice
	 * 
	 * NOT ToDo , but maybe think about how you would do it.
	 * 
	
	public boolean equals(BST403<Key,Value> x) {
		return false;  
	}
	*/

	/**
	 * Returns the number of leaf nodes in the tree
	 * 
	 * ToDo 4
	 */
	public int numLeaves() {
		if (root == null) return 0;
		else return numLeaves(root);
	}
	
	private int numLeaves(Node x) {
		if (x.left == null && x.right == null) return 1;
		else if (x.left == null) return numLeaves(x.right);
		else if (x.right == null) return numLeaves(x.left);
		else return numLeaves(x.left) + numLeaves(x.right);
	}
	
	/**
	 * Returns the length of the shortest path from root to a null node.
	 * 
	 * ToDo 5
	 */
	public int lenShortestPathToNull() {
		return lenShortestPathToNull(root);
	}
	
	private int lenShortestPathToNull(Node x) {
		if (x.left == null || x.right == null) return 0;
		else return 1 + Math.min(lenShortestPathToNull(x.left), lenShortestPathToNull(x.right));
	}
	
	/**
	 * Verifies that 'this' is a valid binary search tree
	 * useful to verify that your version of delete works correctly
	 * ToDo 6
	 */
	public boolean isValidBST() {
		return isValidBST(root);
	}
	
	private boolean isValidBST(Node x) {
		if (x.left == null && x.right == null) return true;
		else if (x.left == null) return (x.key.compareTo(x.right.key) < 0 && isValidBST(x.right));
		else if (x.right == null) return (x.key.compareTo(x.left.key) > 0 && isValidBST(x.left));
		else return (x.key.compareTo(x.left.key) > 0 &&
                     x.key.compareTo(x.right.key) < 0 &&
                     isValidBST(x.left) &&
                     isValidBST(x.right));
	}
	
	/*****************************************************
	 * 
	 * Utility functions 
	 */
	
	
	public Value rGet(Key key) {
		return rGet(root, key);
	}
	private Value rGet(Node x, Key key) {
		if (x == null) return null;
		int cmp = key.compareTo(x.key);
		if      (cmp < 0) return rGet(x.left, key);
		else if (cmp > 0) return rGet(x.right, key);
		else              return x.val;
	}
	
	public void rPut(Key key, Value val) {
		if (key == null) throw new NullPointerException("first argument to put() is null");
		root = rPut(root, key, val);
	}
	
	private Node rPut(Node x, Key key, Value val) {
		if (x == null) return new Node(key, val);
		int cmp = key.compareTo(x.key);
		if      (cmp < 0) x.left  = rPut(x.left,  key, val);
		else if (cmp > 0) x.right = rPut(x.right, key, val);
		else              x.val   = val;
		return x;
	}

}