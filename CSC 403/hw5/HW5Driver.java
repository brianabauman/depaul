package hw5;

import java.util.ArrayList;

import stdlib.In;
import stdlib.StdOut;
import stdlib.StdRandom;
import stdlib.Stopwatch;

import algs31.BinarySearchST;
import algs34.LinearProbingHashST;
import algs34.SeparateChainingHashST;

public class HW5Driver {

	public static class Word implements Comparable<Word> {
		public String text;
		public int length;
		
		public Word(String text, int length) {
			this.text = text;
			this.length = length;
		}
		
		public String toString() {
			return "text: " + text + ", length: " + length;
		}
		
		public int hashCode() {
			int hash = 1;
			hash = 31 * hash + text.hashCode();
			hash = 31 * hash + ((Integer)length).hashCode();
			return hash;
		}
		
		public boolean equals(Word that) {
			return (this.text.equals(that.text) && this.length == that.length);
		}
		
		public int compareTo(Word that) {
			if (this.text.equals(that.text)) return this.length - that.length;
			else return this.text.compareTo(that.text);
		}
	}
	
	public static void main(String[] args) {	
		//int minlen = 2; String file = "data/tinyTale.txt";
		//int minlen = 3; String file = "data/tale.txt";
		int minlen = 11; String file = "data/leipzig1M.txt";
		
		StdOut.println ("LinearProbingHashST"); 
		
		testST(minlen, file);
	}
	
	private static void testST(int minlen, String file) {
		//Load temporary storage of keys so that we can remove I/O costs		
		LinearProbingHashST<Word, Integer> tempStorage = new LinearProbingHashST<Word, Integer>();
		In in = new In(file);
		while(!in.isEmpty()) {
			String text = in.readString();
			int length = text.length();
			if (length < minlen) continue;
			tempStorage.put(new Word(text, length), 0);
		}	
		StdOut.println("Input file loaded, total keys: " + tempStorage.size());
		
		//createSTWithNKeys(tempStorage);
		//insertNPlusFirstKey(tempStorage);
		//getKeyFromSTWithNKeys(tempStorage);
		mixedPutsAndGets(tempStorage);
	}
	
	private static void createSTWithNKeys(LinearProbingHashST<Word, Integer> input) {	
		StdOut.println("Creating a ST with N keys");

		//Test multiple values of N
		for (int N = 0; N <= 400000; N += 50000) {
			LinearProbingHashST<Word, Integer> finalStorage = new LinearProbingHashST<Word, Integer>();
			//SeparateChainingHashST<Word, Integer> finalStorage = new SeparateChainingHashST<Word, Integer>();
					
			//Load keys into final symbol table for a given number of repetitions, time it
			double elapsedTime = 0.0;
			int reps = 10;
			for (int r = 0; r < reps; r++) {
				int count = 1;
				Stopwatch sw = new Stopwatch();
				for (Word thisWord : input.keys()) {
					finalStorage.put(thisWord,  0);
					if (count++ >= N) break;
				}
				elapsedTime += sw.elapsedTime();	
			}
			
			StdOut.println("N: " + N + ", key count: " + finalStorage.size() + ", time: " + elapsedTime/reps);
		}
	}
	
	private static void insertNPlusFirstKey(LinearProbingHashST<Word, Integer> input) {	
		StdOut.println("Inserting the N+1st key");
		
		//Test multiple values of N
		for (int N = 0; N <= 400000; N += 50000) {
			LinearProbingHashST<Word, Integer> finalStorage = new LinearProbingHashST<Word, Integer>();
			//SeparateChainingHashST<Word, Integer> finalStorage = new SeparateChainingHashST<Word, Integer>();
					
			//Build ST up to size N	
			int count = 0;
			int wordsToAddCount = 10;
			ArrayList<Word> wordsToAdd = new ArrayList<Word>();		
			for (Word thisWord : input.keys()) {
				finalStorage.put(thisWord,  0);
				count++;
				if (count >= N && count < N + wordsToAddCount) wordsToAdd.add(thisWord);
				else if (count >= N) break;
			}
			
			//Insert more keys into the ST 
			int reps = 10000;
			double elapsedTime = 0.0;
			for (int r = 0; r < reps; r++) {
				Stopwatch sw = new Stopwatch();
				for (Word wordToAdd : wordsToAdd) {
					finalStorage.put(wordToAdd, 0);
				}
				elapsedTime += sw.elapsedTime();
				
				//Remove the keys we just added so we can do it again
				for (Word wordToAdd : wordsToAdd) {
					finalStorage.delete(wordToAdd);
				}
			}
			
			StdOut.println("N: " + N + ", key count: " + finalStorage.size() + ", time: " + elapsedTime);
		}
	}
	
	private static void getKeyFromSTWithNKeys(LinearProbingHashST<Word, Integer> input) {	
		StdOut.println("Get from a ST with N keys");
		
		//Test multiple values of N
		for (int N = 0; N <= 400000; N += 50000) {
			//LinearProbingHashST<Word, Integer> finalStorage = new LinearProbingHashST<Word, Integer>();
			SeparateChainingHashST<Word, Integer> finalStorage = new SeparateChainingHashST<Word, Integer>();
					
			//Build ST up to size N	
			int count = 0;
			int wordsToGetCount = 10;
			ArrayList<Word> wordsToGet = new ArrayList<Word>();		
			for (Word thisWord : input.keys()) {
				finalStorage.put(thisWord,  0);
				if (StdRandom.uniform(100) < 10 && 
				    wordsToGet.size() < wordsToGetCount) wordsToGet.add(thisWord);
				if (count++ >= N) break;
			}
			
			//Get a random key from the ST
			int reps = 10000;
			double elapsedTime = 0.0;
			for (int r = 0; r < reps; r++) {
				Stopwatch sw = new Stopwatch();
				for (Word wordToGet : wordsToGet) {
					finalStorage.get(wordToGet);
				}
				elapsedTime += sw.elapsedTime();
			}
			
			StdOut.println("N: " + N + ", key count: " + finalStorage.size() + ", time: " + elapsedTime);
		}
	}
	
	private static void mixedPutsAndGets(LinearProbingHashST<Word, Integer> input) {
		StdOut.println("Interspersed puts and gets");
		
		//LinearProbingHashST<Word, Integer> finalStorage = new LinearProbingHashST<Word, Integer>();
		SeparateChainingHashST<Word, Integer> finalStorage = new SeparateChainingHashST<Word, Integer>();
		
		//Build ST up to size 200,000
		int count = 0;
		int wordsToGetCount = 10;
		ArrayList<Word> wordsToGet = new ArrayList<Word>();		
		for (Word thisWord : input.keys()) {
			finalStorage.put(thisWord,  0);
			if (StdRandom.uniform(100) < 10 && 
			    wordsToGet.size() < wordsToGetCount) wordsToGet.add(thisWord);
			if (count++ >= 200000) break;
		}

		int reps = 10;
		double elapsedTime = 0.0;
		for (int r = 1; r < reps; r++) {		
			int putCount = 0;
			int getCount = 0;			
			Stopwatch sw = new Stopwatch();
			for (Word thisWord : input.keys()) {
				if (StdRandom.random() > 0.5 && putCount <= 100000) { finalStorage.put(thisWord, 0); putCount++; }
				else if (getCount <= 100000) { finalStorage.get(thisWord); getCount++; }
				if (putCount >= 100000 && getCount >= 100000) break;
			}
			elapsedTime += sw.elapsedTime();
		}
		
		StdOut.println("Total time: " + elapsedTime/10);
	}
}
