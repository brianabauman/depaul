package group4;

import stdlib.StdAudio;

public class Note implements Comparable<Note> {
	
	private double frequency;
	private double duration;
	
	public Note(double duration, double frequency) {
		this.duration = duration;
		this.frequency = frequency;
	}
	
	public Note() {
		throw new IllegalArgumentException("A frequency and duration must be specified for a Note object.");
	}
	
	public double frequency() {
		return this.frequency;
	}
	
	public double duration() {
		return this.duration;
	}
	
	public void play() {
		final int sliceCount = (int) (StdAudio.SAMPLE_RATE * this.duration);
		final double[] slices = new double[sliceCount+1];
		for (int i = 0; i <= sliceCount; i++) {
			slices[i] = Math.sin(2 * Math.PI * i * this.frequency / StdAudio.SAMPLE_RATE);
		}
		StdAudio.play(slices);
	}
	
	public String toString() {
		return String.format("%.2f Hz for %.3f s", this.frequency, this.duration);
	}

	public int hashCode() {
		return Double.hashCode(this.frequency) + 31 * Double.hashCode(this.duration);
	}
	
	public boolean equals(Object that) {
		if (this == that) return true;
		if (!(that instanceof Note)) return false;
		Note thatNote = (Note) that;
		return this.frequency == thatNote.frequency && this.duration == thatNote.duration;
	}
	
	public int compareTo(Note that) {
		if (this.frequency < that.frequency) return -1;
		if (this.frequency > that.frequency) return 1;
		if (this.duration < that.duration) return -1;
		if (this.duration > that.duration) return 1;
		return 0;
	}
}