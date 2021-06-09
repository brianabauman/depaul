import java.io.*;
import java.net.*;
import java.util.*;

public class Server {
	
	private static Random random = new Random();
	private static Searcher searcher = new SearcherImpl();
	
	/**
	 * Runs a quick measurement on the graph.
	 * 
	 * @param howMany
	 */
	private static HashMap<Node, HashMap<Node, Integer>> searchBenchmark(int howMany, Node[] nodes) {
		
		//Create array of random Nodes from the graph of size howMany
		Node[] nodesToProcess = new Node[howMany];
		LinkedList<Integer> indicesUsed = new LinkedList<Integer>();
		
		int i = 0;
		while (i < howMany)
		{
			int randomNum = random.nextInt(nodes.length);
			if (!indicesUsed.contains(randomNum)) nodesToProcess[i] = nodes[randomNum];
			i++;
		}
		
		//Find the distance from each relevant node to all other neighbors and record in a HashMap 
		HashMap<Node, HashMap<Node, Integer>> graphMap = new HashMap<Node, HashMap<Node, Integer>>();	
		for (Node outerNode : nodesToProcess)
		{
			HashMap<Node, Integer> nodeMap = new HashMap<Node, Integer>();		
			for (Node innerNode : nodes)
				nodeMap.put(innerNode, searcher.getDistance(outerNode, innerNode));

			graphMap.put(outerNode, nodeMap);
		}
		
		return graphMap;
	}
	
	public static void main(String[] args) {
		
		//Gather port number from user
		int portNumber = Integer.parseInt(args[0]);
		
		int howMany;
		Node[] nodes;
		HashMap<Node, HashMap<Node, Integer>> rtnMap;
		
		try
		{
			//Create sockets and streams
			ServerSocket serverSocket = new ServerSocket(portNumber);
			Socket clientSocket = serverSocket.accept();
			ObjectOutputStream out = new ObjectOutputStream(clientSocket.getOutputStream());
			ObjectInputStream in = new ObjectInputStream(clientSocket.getInputStream());
			
			//Gather input variables from client
			howMany = (int)in.readObject();
			nodes = (Node[])in.readObject();
			
			//Generate return object and send to client
			rtnMap = searchBenchmark(howMany, nodes);
			out.writeObject(rtnMap);
			
			//Close streams
			in.close();
			out.close();
			clientSocket.close();
			serverSocket.close();
		}
		catch (Exception ex)
		{
			System.out.println(ex.getMessage());
    			System.exit(1);
		}
	}
}
