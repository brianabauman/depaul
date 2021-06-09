package searcher;

import java.io.*;
import java.util.HashMap;

import searcher.Node;

public interface GraphSearcher extends Serializable {
	public static final int DISTANCE_INFINITE = -1;
	public int getDistance(Node from, Node to);
	public int getTransitiveDistance(int distance, Node from, Node to);
	public HashMap<Node, HashMap<Node,Integer>> searchBenchmark(int howMany, Node[] nodes);
}
