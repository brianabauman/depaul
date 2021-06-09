package server;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

import searcher.GetSearcher;
import searcher.GraphSearcher;

public class SearcherGetter extends UnicastRemoteObject implements GetSearcher {
	
	public SearcherGetter() throws RemoteException {
		
	}
	
	public GraphSearcher getSearcher() throws RemoteException {
		return (GraphSearcher) new SearcherImpl();
	}
}
