package hw6;  // change this if you want
import stdlib.*;

//  Version 1.0 
//
//This is basically exercise 4.1.16 from the text
//   see the exercise for definitions and hints
//
//  The provided structure follows the design pattern illustrated
//  by the examples in 4.1
//
// you're free to add instance variables and other methods
// you'll probably want to add in code to support bfs or dfs; 
//     feel free to grab and adapt these from the text and/or algs41
//  you might find queue or stack to be useful, if so I'd suggest you use
//  the versions from algs13
//
//  you shouldn't need (or use) anything else, ask me if not sure

// please document your code to explain your approach
// If I can't follow what you're doing, you will get reduced (or no) credit


import algs41.Graph;
import algs41.GraphGenerator;
import algs13.Queue;
import algs13.Stack;

public class CSC403HW6 {
	int[] eccentricity;  // the eccentricity of each vertex
	int diameter;        // the diameter of the graph
	int radius;	         // the radius of the graph
	boolean [] isAcenter;       // the set of all 
	boolean[] marked; // new instance variable to support bfs method
	int count; // new instance variable to support bfs method
	int[] edgeTo; // new instance variable to support bfs method

	// Constructor can be linear in G.V() * G.E()
	public CSC403HW6(Graph G) {

		this.eccentricity = new int[G.V()];
		int diameter = Integer.MIN_VALUE;
		int radius = Integer.MAX_VALUE;

		// If G.V()==0, then these are the correct values.
		// If G is not connected, you should throw a new IllegalArgumentException()
		// I suggest that you first get it to work for a connected graph
		// This will require that you traverse the graph starting from some node (say 0)
		// You can then adjust your code so that it throws an exception in the case that all nodes are not visited
		this.edgeTo = new int[G.V()];
		this.marked = new boolean[G.V()]; 
		this.count = 0;
		
		if (G.V() > 0) {
			// check for connectedness
			bfs(G, 0);
			if (count < G.V()) throw new IllegalArgumentException("graph not connected");
			
			// loop through all of the nodes to determine eccentricity
			for (int i = 0; i < G.V(); i++) {
				int furthestPath = 0;
				this.edgeTo = new int[G.V()];
				this.marked = new boolean[G.V()];
				bfs(G, i);
				
				// find path lengths to other nodes
				for (int j = 0; j < G.V(); j++) {
					if (j ==i) continue;					
					int pathLength = pathTo(i, j).size() - 1;				
					if (pathLength > furthestPath) furthestPath = pathLength;
				}
					
				this.eccentricity[i] = furthestPath;
			}
			
			// set the diameter and radius
			for (int i = 0; i < G.V(); i++) {
				if (this.eccentricity[i] > diameter) diameter = this.eccentricity[i];
				if (this.eccentricity[i] < radius) radius = this.eccentricity[i];
			}
		}
		
		// TODO
		// compute the eccentricity of each vertex, the diameter & radius 
		this.diameter = diameter;
		this.radius   = radius;
	}

	// Do not change the following constant time methods
	public int eccentricity(int v) { return eccentricity[v]; }
	public int diameter()          { return diameter; }
	public int radius()            { return radius; }
	public boolean isCenter(int v) { return eccentricity[v] == radius; }
	
	// bfs implementation from the book
	private void bfs(Graph G, int s) {
		Queue<Integer> queue = new Queue<Integer>();
		marked[s] = true; count++;
		queue.enqueue(s);
		while (!queue.isEmpty()) {
			int v = queue.dequeue();
			for (int w : G.adj(v))
				if (!marked[w]) {
					edgeTo[w] = v;
					marked[w] = true; count++;
					queue.enqueue(w);
				}
		}
	}
	
	// pathTo implementation from the book
	private Stack<Integer> pathTo(int s, int v) {
		Stack<Integer> path = new Stack<Integer>();
		for (int x = v; x != s; x = edgeTo[x])
				path.push(x);
		path.push(s);
		return path;
	}

	public static void main(String[] args) {
		// comment in/out for testing
		//Graph G = GraphGenerator.fromIn(new In("data/tinyG.txt")); // this is non-connected -- should throw an exception
		//Graph G = GraphGenerator.connected (10, 20, 2); // Random non-connected graph -- should throw an exception

		//Graph G = GraphGenerator.fromIn(new In("data/tinyCG.txt")); // diameter=2, radius=2, every node is a center
		//Graph G = GraphGenerator.binaryTree (10); // A complete binary tree
		//Graph G = GraphGenerator.path (10); // A path -- diameter=V-1
		Graph G = GraphGenerator.connected (20, 400); // Random connected graph

		StdOut.println(G);
		//G.toGraphviz ("g.png");  // comment out if you don't have graphViz installed
		
		CSC403HW6 edrc = new CSC403HW6(G);
		for (int v = 0; v < G.V(); v++)
			StdOut.format ("eccentricity of %d: %d\n", v, edrc.eccentricity (v));
		StdOut.format ("diameter=%d, radius=%d\n", edrc.diameter(), edrc.radius() );
		for (int i = 0; i < G.V(); i++) {
			if ( edrc.isCenter(i))
			StdOut.format ("center=%d\n", i);
		}
	}
}
