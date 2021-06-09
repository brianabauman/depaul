import java.io.*;
import java.net.Socket;
import java.util.*;

public class Client {
	// How many nodes and how many edges to create.
	private static final int GRAPH_NODES = 100;
	private static final int GRAPH_EDGES = 200;

	private static Node[] nodes;
	private static Random random = new Random();

	/**
	 * Creates nodes of a graph.
	 * 
	 * @param howMany
	 */
	public static void createNodes(int howMany) {
		nodes = new Node[howMany];

		for (int i = 0; i < howMany; i++) {
			nodes[i] = new NodeImpl();
		}
	}

	/**
	 * Creates a fully connected graph.
	 */
	public static void connectAllNodes() {
		for (int idxFrom = 0; idxFrom < nodes.length; idxFrom++) {
			for (int idxTo = idxFrom + 1; idxTo < nodes.length; idxTo++) {
				nodes[idxFrom].addNeighbor(nodes[idxTo]);
				nodes[idxTo].addNeighbor(nodes[idxFrom]);
			}
		}
	}

	/**
	 * Creates a randomly connected graph.
	 * 
	 * @param howMany
	 */
	public static void connectSomeNodes(int howMany) {
		for (int i = 0; i < howMany; i++) {
			final int idxFrom = random.nextInt(nodes.length);
			final int idxTo = random.nextInt(nodes.length);

			nodes[idxFrom].addNeighbor(nodes[idxTo]);
		}
	}

	public static void main(String[] args) {
		String hostName = args[0];
		int portNumber = Integer.parseInt(args[1]);
		int howMany = Integer.parseInt(args[2]);
		
		//Create graph and attach some nodes
		createNodes(GRAPH_NODES);
		connectSomeNodes(GRAPH_EDGES);
		
		HashMap<Node, HashMap<Node, Integer>> rtnMap = new HashMap<Node, HashMap<Node, Integer>>();
		
		//Create a connection to the server
        try 
        {
        		//Create socket and streams
        		Socket socket = new Socket(hostName, portNumber);
        		ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream()); 
        		ObjectInputStream in = new ObjectInputStream(socket.getInputStream());       		      		
        		System.out.println("Connected to " + hostName + " on port " + portNumber + ".");
        		
        		//Write input variables to server
        		out.writeObject(howMany);
        		out.writeObject(nodes);
        		
        		//Read response object from server
        		rtnMap = (HashMap<Node, HashMap<Node, Integer>>)in.readObject();
        		
        		in.close();
        		out.close();
        		socket.close();
        }
        catch (Exception ex)
        {
        		System.out.println(ex.getMessage());
        		System.exit(1);
        }

		//Print results
		int outerCount = 1;
		for (Node outerNode : rtnMap.keySet())
		{
			int innerCount = 1;
			for (Node innerNode : rtnMap.get(outerNode).keySet())
			{
				System.out.println("Random node " + outerCount + " is a distance of " + rtnMap.get(outerNode).get(innerNode) + " from original node " + innerCount);
				innerCount++;
			}	
			
			outerCount++;
		}	
	}
}