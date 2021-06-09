package searcher;

import java.io.Serializable;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.HashMap;

import searcher.Node;

public interface GraphSearcher extends Remote, Serializable {
	HashMap<Node, HashMap<Node,Integer>> searchBenchmark(int howMany, Node[] nodes) throws RemoteException;
	
	public static final int DISTANCE_INFINITE = -1;
	public int getDistance(Node from, Node to) throws RemoteException;
	public int getTransitiveDistance(int distance, Node from, Node to) throws RemoteException;
}
