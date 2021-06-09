package group4;
//Author: Brian Bauman

public class TestChord {

	public static void main(String[] args) {
		Chord chord1 = new Chord(0.5, 261.626, 349.228, 391.995);
		Chord chord2 = new Chord(0.5, 440.0, 880.0, 1760.0);
		Chord chord3 = new Chord(0.5, 329.628, 391.995, 493.883);
		
		chord1.playChord();
		chord2.playChord();
		chord3.playChord();
	}
}
