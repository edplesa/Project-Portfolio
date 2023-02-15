import javafx.util.Duration;

public class CustomMidiEventData {

    public static final int NOTE_ON = 0x90;
    public static final int NOTE_OFF = 0x80;

    public int key;
    public int octave;
    public int note;
    public String noteName;
    public int velocity;

    public long tick;
    public int ON_OFF;

    public CustomMidiEventData(int key, int octave, int note, String noteName, int velocity, long tick, int ON_OFF) {
        this.key =          key;
        this.octave =       octave;
        this.note =         note;
        this.noteName =     noteName;
        this.velocity =     velocity;
        this.tick =         tick;
        this.ON_OFF =       ON_OFF;
    } 

    @Override
    public String toString() {
        String s = "";
        s += "{";
        s += "\n  Key:   \t"   + key;
        s += "\n  Octave:\t"   + octave;
        s += "\n  Note:  \t"   + note;
        s += "\n  Note:  \t"   + noteName;
        s += "\n  Velocity:\t" + velocity;
        s += "\n  Tick:  \t"   + tick;
        s += "\n  Command:\t"  + ((ON_OFF == NOTE_OFF) ? "Off" : "On");
        s += "\n}";
        return s;
    }

    public boolean isStartTick() {
        return ON_OFF == NOTE_ON;
    }

    public boolean isEndTick() {
        return ON_OFF == NOTE_OFF;
    }
}
