import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class Djikstra {

	//class to contain node information
	private static class Node implements Comparable<Node> {
		public String name;
		public String fromName;
		public int weightTo;
		
		public Node(String name, String fromName, int weightTo) {
			this.name = name;
			this.fromName = fromName;
			this.weightTo = weightTo;
		}
		
		public int compareTo(Node b) {
			return this.weightTo - b.weightTo;
		}
		
		public String toString() {
			return name + " (" + weightTo + ")";
		}
	}

	public static void main(String[] args) {
		try {
			//gather input filepath
			Scanner reader = new Scanner(System.in);
			System.out.print("Please enter the name of the input file: ");	
			String fileName = reader.nextLine();
			reader.close();
			
			String filePath = System.getProperty("user.dir");
			reader = new Scanner(new File(filePath, fileName));
			
			//determine node count and initialize variables
			int nodeCount = Integer.parseInt(reader.nextLine());
			
			ArrayList<ArrayList<Node>> graph = new ArrayList<ArrayList<Node>>();
			BinaryHeap<Node> minDistances = new BinaryHeap<Node>();	
			boolean[] visited = new boolean[nodeCount];
			Node[] shortestPaths = new Node[nodeCount];
			
			//populate new variables
			for (int i = 0; i < nodeCount; i++) {
				graph.add(new ArrayList<Node>());
				
				Node thisNode = new Node(indexToName(i), "", Integer.MAX_VALUE);
				if (i == 0) thisNode.weightTo = 0;
				minDistances.add(thisNode);			
				shortestPaths[i] = thisNode;
			}

			//read from input and create the edges of the graph
			while (reader.hasNextLine()) {
				String[] textArray = reader.nextLine().split(" ");
				String fromName = textArray[0];
				String toName = textArray[1];
				int weight = Integer.parseInt(textArray[2]);
				
				Node thisNode = new Node(toName, fromName, weight);
				graph.get(nameToIndex(fromName)).add(thisNode);
			}
			reader.close();

			//run through the algorithm
			while (!minDistances.isEmpty()) {

				//pluck a node off the heap
				Node currentNode = minDistances.remove();
				shortestPaths[nameToIndex(currentNode.name)] = currentNode;
				visited[nameToIndex(currentNode.name)] = true;
				
				//update its neighbors if not visited
				for (Node adjacentNode : graph.get(nameToIndex(currentNode.name))) {
					
					if (!visited[nameToIndex(adjacentNode.name)]) {
						int currDist = shortestPaths[nameToIndex(adjacentNode.name)].weightTo;
						int newDist = shortestPaths[nameToIndex(currentNode.name)].weightTo + adjacentNode.weightTo;
						
						if (newDist < currDist) {
							shortestPaths[nameToIndex(adjacentNode.name)].weightTo = newDist;
							shortestPaths[nameToIndex(adjacentNode.name)].fromName = currentNode.name;
						}
					}
				}	
				
				minDistances = heapify(shortestPaths, visited);
			}
			
			System.out.println("Node A is a distance of " + shortestPaths[1].weightTo + " from node B.");

			//print path
			Node currNode = shortestPaths[1];
			Stack<String> path = new Stack<String>();
			path.push("B");
			
			while (currNode.fromName != "") {
				path.push(currNode.fromName);
				currNode = shortestPaths[nameToIndex(currNode.fromName)];
			}

			while (!path.isEmpty()) {
				System.out.print(path.pop() + " ");
			}
			System.out.println();
			
		} catch (Exception ex) {
			System.out.println("Error:");
			System.out.println(ex.toString());
		}
	}
	
	//helper method to heapify
	private static BinaryHeap<Node> heapify(Node[] inpShortestPaths, boolean[] inpVisited) {
		BinaryHeap<Node> rtnHeap = new BinaryHeap<Node>();
		
		for (int i = 0; i < inpShortestPaths.length; i++) {
			if (!inpVisited[i]) rtnHeap.add(inpShortestPaths[i]);
		}
		
		return rtnHeap;
	}
	
	//helper method to convert letters to indices
	private static int nameToIndex(String inpName) throws Exception {
		if (inpName.length() > 1) throw new Exception("Node name must be a single letter");
		char letter = inpName.charAt(0);
		int rtnInt = (int)letter - 65;
		if (rtnInt < 0) throw new Exception("Node name must be a single letter");
		return rtnInt;
	}
	
	//helper method to convert indices to letters
	private static String indexToName(int inpIndex) throws Exception {
		if (inpIndex < 0 || inpIndex > 25) throw new Exception("Node index must be between 0 and 25");		
		char letter = (char)(inpIndex + 65);
		return Character.toString(letter);
	}
}
