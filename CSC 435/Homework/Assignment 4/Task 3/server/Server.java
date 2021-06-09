package server;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import searcher.GetSearcher;

public class Server {
	
	public static void main(String[] args) {		
		if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("Getter", new SearcherGetter());
            System.out.println("SearcherGetter bound");
        } catch (Exception e) {
            System.err.println("SearcherGetter exception:");
            e.printStackTrace();
        }
	}
}
