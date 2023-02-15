public class SlidingNoteData {
    public static final int NOTE_ON = 0x90;
    public static final int NOTE_OFF = 0x80;

    public int key;
    public int octave;
    public int note;
    public String noteName;
    public int velocity;

    public long start;
    public long end;

    public SlidingNoteData(int key, int octave, int note, String noteName, int velocity, long start) {
        this.key =          key;
        this.octave =       octave;
        this.note =         note;
        this.noteName =     noteName;
        this.velocity =     velocity;
        this.start =        start;
    } 

    @Override
    public String toString() {
        String s = "";
        s += "{";
        s += "\n  Key:     \t"   + key;
        s += "\n  Octave:  \t"   + octave;
        s += "\n  Note:    \t"   + note;
        s += "\n  Name:    \t"   + noteName;
        s += "\n  Velocity:\t"   + velocity;
        s += "\n  Start:   \t"   + start;
        s += "\n  End:     \t"   + end;
        s += "\n}";
        return s;
    }
}


