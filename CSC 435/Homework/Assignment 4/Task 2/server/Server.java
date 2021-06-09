package server;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Server {
	
	public static void main(String[] args) {		
		if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("Searcher", new SearcherImpl());
            System.out.println("SearcherImpl bound");
        } catch (Exception e) {
            System.err.println("SearcherImpl exception:");
            e.printStackTrace();
        }
	}
}
