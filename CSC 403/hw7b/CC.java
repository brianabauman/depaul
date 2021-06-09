package hw7b;
import stdlib.*;
import algs41.Graph;
import algs41.GraphGenerator;

/* ***********************************************************************
 *  Compilation:  javac CC.java
 *  Execution:    java CC filename.txt
 *  Dependencies: Graph.java StdOut.java Queue.java
 *  Data files:   http://algs4.cs.princeton.edu/41undirected/tinyG.txt
 *
 *  Compute connected components using depth first search.
 *  Runs in O(E + V) time.
 *
 *  %  java CC tinyG.txt
 *  3 components
 *  0 1 2 3 4 5 6
 *  7 8
 *  9 10 11 12
 *
 *************************************************************************/

public class CC {
	private final boolean[] marked;   // marked[v] = has vertex v been marked?
	private final int[] id;           // id[v] = id of connected component containing v
	private final int[] size;         // size[id] = number of vertices in component containing v
	private int count;                // number of connected components

	public CC(Graph G) {
		marked = new boolean[G.V()];
		id = new int[G.V()];
		size = new int[G.V()];
		for (int v = 0; v < G.V(); v++) {
			if (!marked[v]) {
				dfs(G, v);
				count++;
			}
		}
	}

	// depth first search
	private void dfs(Graph G, int v) {
		marked[v] = true;
		id[v] = count;
		size[count]++;
		for (int w : G.adj(v)) {
			if (!marked[w]) {
				dfs(G, w);
			}
		}
	}

	// id of connected component containing v
	public int id(int v) {
		return id[v];
	}

	// size of connected component containing v
	public int size(int v) {
		return size[id[v]];
	}

	// number of connected components
	public int count() {
		return count;
	}

	// are v and w in the same connected component?
	public boolean areConnected(int v, int w) {
		return id(v) == id(w);
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
	
	// test client
	public static void anotherTest() {
		Graph G;
		do {
			G = GraphGenerator.simple(20,40);
		} while (new CC(G).count() != 1);
		//G.toGraphviz ("g.png");
	}

	// Erdos-Renyi (N,p) random graph
	public static Graph erRandom(int V, double p) {
	    if (V < 0 || p < 0) throw new IllegalArgumentException ();
	    Graph G = new Graph(V);	
	    for ( int v = 0; v < V; v++) 
	    for (int w = v+1; w < V; w++) 
	        if ( StdRandom.uniform() <= p)
	    	        G.addEdge(v, w);
	    return G; 
	}	
	
	public static void main(String[] args) {
		
//		args = new String [] { "10", "5" };
//		final int V = Integer.parseInt(args[0]);
//		final int E = Integer.parseInt(args[1]);
//		final Graph G = GraphGenerator.simple(V, E);
//		StdOut.println(G);
		
		for (double p = 0; p <= 0.051; p += 0.00125) {
			int largestSizeSum = 0;
			int M = 20;
			for (int i = 0; i < M; i++) {
				Graph G = erRandom(200, p);
				CC C = new CC(G);
				//StdOut.println("largestSize = " + C.largestSize());
				largestSizeSum += C.largestSize();
			}

			StdOut.printf("%.4f\t%.3f\n", 100 * p, largestSizeSum / (double)M);
		}
	}
}
