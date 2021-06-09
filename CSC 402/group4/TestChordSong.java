package group4;
//Brian Bauman

public class TestChordSong {

	public static void main(String[] args) {
		ChordSong song = new ChordSong(new Chord[0]);
		song.add(new Chord(0.25, 27.500, 29.135, 30.868));
		song.add(new Chord(0.25, 55.000, 58.270, 61.735));
		song.add(new Chord(0.25, 110.000, 116.541, 123.471));
		song.add(new Chord(0.25, 220.000, 233.082, 246.942));
		song.add(new Chord(0.25, 440.000, 466.164, 493.883));
		song.add(new Chord(0.25, 880.000, 932.328, 987.767));
		song.add(new Chord(0.25, 1760.000, 1864.655, 1975.533));
		song.add(new Chord(0.25, 3520.000, 3729.310, 3951.066));
		song.play();
	}
}
