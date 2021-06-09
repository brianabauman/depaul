package hw7b;
import stdlib.*;
import algs13.Queue;
import algs41.Graph;
import algs42.Digraph;
import algs42.DepthFirstOrder;
import algs42.TransitiveClosure;
import algs42.DigraphGenerator;
/* ***********************************************************************
 *  Compilation:  javac KosarajuSharirSCC.java
 *  Execution:    java KosarajuSharirSCC filename.txt
 *  Dependencies: Digraph.java TransitiveClosure.java StdOut.java In.java
 *  Data files:   http://algs4.cs.princeton.edu/42directed/tinyDG.txt
 *
 *  Compute the strongly-connected components of a digraph using the
 *  Kosaraju-Sharir algorithm.
 *
 *  Runs in O(E + V) time.
 *
 *  % java KosarajuSharirSCC tinyDG.txt
 *  5 components
 *  1
 *  0 2 3 4 5
 *  9 10 11 12
 *  6
 *  7 8
 *
 *  % java KosarajuSharirSCC mediumDG.txt
 *  10 components
 *  21
 *  2 5 6 8 9 11 12 13 15 16 18 19 22 23 25 26 28 29 30 31 32 33 34 35 37 38 39 40 42 43 44 46 47 48 49
 *  14
 *  3 4 17 20 24 27 36
 *  41
 *  7
 *  45
 *  1
 *  0
 *  10
 *
 *************************************************************************/

public class KosarajuSharirSCC {
	private final boolean[] marked;     // marked[v] = has vertex v been visited?
	private final int[] id;             // id[v] = id of strong component containing v
	private int count;                  // number of strongly-connected components


	public KosarajuSharirSCC(Digraph G) {

		// compute reverse postorder of reverse graph
		Digraph R = G.reverse ();
		DepthFirstOrder dfs = new DepthFirstOrder(R);

		// run DFS on G, using reverse postorder to guide calculation
		marked = new boolean[G.V()];
		id = new int[G.V()];
		for (int v : dfs.reversePost()) {
			if (!marked[v]) {
				dfs(G, v);
				count++;
			}
		}

		// check that id[] gives strong components
		assert check(G);
	}

	// DFS on graph G
	private void dfs(Digraph G, int v) {
		marked[v] = true;
		id[v] = count;
		for (int w : G.adj(v)) {
			if (!marked[w]) dfs(G, w);
		}
	}

	// return the number of strongly connected components
	public int count() { return count; }

	// are v and w strongly connected?
	public boolean stronglyConnected(int v, int w) {
		return id[v] == id[w];
	}

	// id of strong component containing v
	public int id(int v) {
		return id[v];
	}
	
	/* this is my code */
	public int largestSize() {
		int sizes[] = new int[count];
		for (int i = 0; i < id.length; i++)
			sizes[id[i]]++;
		
		int largestSize = 0;
		for (int i = 0; i < count; i++)
			if (sizes[i] > largestSize) largestSize = sizes[i];
		
		return largestSize;
	}
	/* my code ends here */
	
	// does the id[] array contain the strongly connected components?
	private boolean check(Digraph G) {
		TransitiveClosure tc = new TransitiveClosure(G);
		for (int v = 0; v < G.V(); v++) {
			for (int w = 0; w < G.V(); w++) {
				if (stronglyConnected(v, w) != (tc.reachable(v, w) && tc.reachable(w, v)))
					return false;
			}
		}
		return true;
	}
	
	// Erdos-Renyi (N,p) random digraph
	public static Digraph erRandom(int V, double p) {
	    if (V < 0 || p < 0) throw new IllegalArgumentException (); 
	    Digraph D = new Digraph (V);
	    for ( int v = 0; v < V; v++)
	        for (int w = 0; w < V; w++) 
	        	    if ( v != w )
	        	    	    if ( StdRandom.uniform() <= p)
	        	    	    	    D.addEdge(v, w);
	    return D; 
	}
	
	public static void main(String[] args) {
		for (double p = 0; p <= 0.051; p += 0.00125) {
			int largestSizeSum = 0;
			int M = 20;
			for (int i = 0; i < M; i++) {
				Digraph G = erRandom(200, p);
				KosarajuSharirSCC KSSCC = new KosarajuSharirSCC(G);
				//StdOut.println("largestSize = " + KSSCC.largestSize());
				largestSizeSum += KSSCC.largestSize();
			}
			
			StdOut.printf("%.4f\t%.3f\n", 100 * p, largestSizeSum / (double)M);
		}
	}

}
