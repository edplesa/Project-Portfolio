import java.io.File;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

import javax.sound.midi.MidiEvent;
import javax.sound.midi.MidiMessage;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.Sequence;
import javax.sound.midi.ShortMessage;
import javax.sound.midi.Track;

public class MidiParser {
    public static final int NOTE_ON = 0x90;
    public static final int NOTE_OFF = 0x80;
    public static final String[] NOTE_NAMES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};





    public LinkedList<SlidingNoteData> parseMidiFileIntoNotes(String filename) {
        try {
            LinkedList<CustomMidiEventData> list = createListOfMidiEvents(filename);
            LinkedList<SlidingNoteData> snd_list = createListOfDisplayableNotes(list);
            //
            // Ensure the notes are sorted by start tick:
            Collections.sort(snd_list, new Comparator<SlidingNoteData>() {
                @Override
                public int compare(SlidingNoteData s1, SlidingNoteData s2) {
                    return s1.start < s2.start ? -1
                         : s2.start > s2.start ? 1
                         : 0;
                }
            });
            return snd_list;
        } catch (Exception e) {
            System.out.println("Midi Parsing failed...\n" + e.toString());
            return null;
        }
    }





    private LinkedList<CustomMidiEventData> createListOfMidiEvents(String filename) throws Exception {
        LinkedList<CustomMidiEventData> list = new LinkedList<>();
        Sequence sequence = MidiSystem.getSequence(new File(filename));
        int trackNumber = 0;
        for (Track track :  sequence.getTracks()) {
            trackNumber++;
            // System.out.println("Track " + trackNumber + ": size = " + track.size());
            // System.out.println();
            for (int i=0; i < track.size(); i++) { 
                MidiEvent event = track.get(i);
                // System.out.print("@" + event.getTick() + " ");
                MidiMessage message = event.getMessage();
                if (message instanceof ShortMessage) {
                    ShortMessage sm = (ShortMessage) message;
                    // System.out.print("Channel: " + sm.getChannel() + " ");
                    if (sm.getCommand() == NOTE_OFF || sm.getCommand() == NOTE_ON) {
                        int key = sm.getData1();
                        int octave = (key / 12)-1;
                        int note = key % 12;
                        String noteName = NOTE_NAMES[note];
                        int velocity = sm.getData2();
                        list.add(new CustomMidiEventData(key, octave, note, noteName, velocity, event.getTick()*5/2, sm.getCommand()));
                        // System.out.println("Note " + ((sm.getCommand()==NOTE_OFF)?"off: ":"on: ") + noteName + octave + " key=" + key + " velocity: " + velocity);
                    
                    } else {
                        // System.out.println("Command:" + sm.getCommand());
                    }
                } else {
                    // System.out.println("Other message: " + message.getClass());
                }
            }
            // System.out.println();
        }
        return list;
    }

    private LinkedList<SlidingNoteData> createListOfDisplayableNotes(LinkedList<CustomMidiEventData> list) {
        HashMap<Integer,SlidingNoteData> lhm = new HashMap<>();
        LinkedList<SlidingNoteData> new_list = new LinkedList<>();
        for (CustomMidiEventData cmed: list) {
            if (cmed.isStartTick()) {
                lhm.put(cmed.key, new SlidingNoteData(cmed.key, cmed.octave, cmed.note, cmed.noteName, cmed.velocity, cmed.tick));
            } else {
                lhm.get(cmed.key).end = cmed.tick;
                new_list.add(lhm.get(cmed.key));
            }
        }
        return new_list;
    }
}
