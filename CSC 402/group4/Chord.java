package group4;
//Author: Brian Bauman

import stdlib.StdAudio;

public class Chord {

	private Note[] notes = new Note[3];
	
	public Chord(double duration, double frequency1, double frequency2, double frequency3) {
		notes[0] = new Note(duration, frequency1);
		notes[1] = new Note(duration, frequency2);
		notes[2] = new Note(duration, frequency3);
	}
	
	public Note[] notes() {
		return this.notes;
	}
	
	public void playChord() {
		final int sliceCount = (int) (StdAudio.SAMPLE_RATE * this.notes[0].duration());
		final double[] slices = new double[sliceCount+1];
		for (int i = 0; i <= sliceCount; i++) {
			for (Note thisNote: this.notes()) {
				slices[i] += Math.sin(2 * Math.PI * i * thisNote.frequency() / StdAudio.SAMPLE_RATE);
			}
			slices[i] /= this.notes().length;
		}
		StdAudio.play(slices);
	}
	
	public String toString() {
		return String.format("%.3f Hz for %.3f s, %.3f Hz for %.3f s, %.3f Hz for %.3f s", 
				             this.notes[0].frequency(), 
				             this.notes[0].duration(),
				             this.notes[1].frequency(), 
				             this.notes[1].duration(),
				             this.notes[2].frequency(), 
				             this.notes[2].duration());
	}
	
	public int hashCode() {
		return notes[0].hashCode() + 31 * notes[1].hashCode() + 31 * 31 * notes[2].hashCode();
	}
	
	public boolean equals(Object that) {
		if (this == that) return true;
		if (!(that instanceof Chord)) return false;
		
		Chord thatChord = (Chord) that;
		boolean isEqual = true;
		
		//By definition above, all notes in a chord have equal duration
		if (thatChord.notes[0].duration() != this.notes[0].duration()) return false;
		
		//Does that chord have all of these notes?
		for (Note thatNote : thatChord.notes()) {
			boolean noteFound = false;
			for (Note thisNote : this.notes()) {
				if (thatNote.frequency() == thisNote.frequency()) {
					noteFound = true;
					break;
				}
			}
			
			if (noteFound == false) return false;
		}
		
		//Does this chord have all of those notes?
		for (Note thisNote : this.notes()) {
			boolean noteFound = false;
			for (Note thatNote : thatChord.notes()) {
				if (thisNote.frequency() == thatNote.frequency()) {
					noteFound = true;
					break;
				}
			}
			
			if (noteFound == false) return false;
		}
		
		return true;
	}
	
	public int compareTo(Chord that) {
		if (this.notes[0].frequency() + this.notes[1].frequency() + this.notes[2].frequency() <
			that.notes[0].frequency() + that.notes[1].frequency() + that.notes[2].frequency()) return -1;
		if (this.notes[0].frequency() + this.notes[1].frequency() + this.notes[2].frequency() <
			that.notes[0].frequency() + that.notes[1].frequency() + that.notes[2].frequency()) return 1;
		if (this.notes[0].duration() < that.notes[0].duration()) return -1;
		if (this.notes[0].duration() > that.notes[0].duration()) return 1;
		return 0;
	}	
}
