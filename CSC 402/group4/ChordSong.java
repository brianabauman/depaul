package group4;
//Author: Brian Bauman

public class ChordSong {
	
	private Chord[] chords;
	
	public ChordSong(Chord[] chords) {
		this.chords = chords;
	}
	
	public void add(Chord note) {
		Chord[] newChords = new Chord[this.chords.length + 1];
		for (int i = 0; i < this.chords.length; i++) {
			newChords[i] = this.chords[i];
		}
		
		newChords[this.chords.length] = note;
		this.chords = newChords;
	}
	
	public void play() {
		for (Chord thisChord: chords) {
			thisChord.playChord();
		}
	}
	
	public Chord chordAt(int index) {
		if (index < 0 || index >= this.chords.length) throw new IndexOutOfBoundsException("Out of range index: " + index);
		return this.chords[index];
	}
	
	public String toString() {
		StringBuilder builder = new StringBuilder();
		for (int i = 1; i <= this.chords.length; i++) {
			builder.append("Chord " + i + ": " + this.chords[i - 1].toString());
			if (i < this.chords.length) builder.append(", ");
		}
		
		return builder.toString();
	}
}
