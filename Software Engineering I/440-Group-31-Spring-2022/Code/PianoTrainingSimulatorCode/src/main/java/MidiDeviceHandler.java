import javax.sound.midi.*;

import javafx.fxml.FXMLLoader;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.io.*;

public class MidiDeviceHandler
{
    public static final int NOTE_ON = 0x90;
    public static final int NOTE_OFF = 0x80;
    public static final String[] NOTE_NAMES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    public ConcurrentLinkedQueue<Pair<Boolean,Pair<Integer,Integer>>> q;
    public boolean load_success = false;
    public String device_name = "";
    FXMLLoader fxmls[];

    public MidiDeviceHandler()
    {
        // MidiDevice device;
        // MidiDevice.Info[] infos = MidiSystem.getMidiDeviceInfo();
        // for (int i = 0; i < infos.length; i++) {
        //     try {
        //     device = MidiSystem.getMidiDevice(infos[i]);
        //     //does the device have any transmitters?
        //     //if it does, add it to the device list
        //     System.out.println(infos[i]);

        //     //get all transmitters
        //     List<Transmitter> transmitters = device.getTransmitters();
        //     //and for each transmitter

        //     for(int j = 0; j<transmitters.size();j++) {
        //         //create a new receiver
        //         transmitters.get(j).setReceiver(
        //                 //using my own MidiInputReceiver
        //                 new MidiInputReceiver(fxmls, device.getDeviceInfo().toString())
        //         );
        //     }

        //     Transmitter trans = device.getTransmitter();
        //     trans.setReceiver(new MidiInputReceiver(fxmls, device.getDeviceInfo().toString()));

        //     //open each device
        //     device.open();
        //     //if code gets this far without throwing an exception
        //     //print a success message
        //     System.out.println(device.getDeviceInfo()+" Was Opened");

            

        // } catch (MidiUnavailableException e) {}
    }

    public void loadMidiDevice(FXMLLoader fxmls[])  {
        this.fxmls = fxmls;
        q = new ConcurrentLinkedQueue<>();
        MidiDevice device;
        MidiDevice.Info[] infos = MidiSystem.getMidiDeviceInfo();
        for (int i = 0; i < infos.length; i++) {
            try {
            device = MidiSystem.getMidiDevice(infos[i]);
            //does the device have any transmitters?
            //if it does, add it to the device list
            System.out.println(infos[i]);

            //get all transmitters
            List<Transmitter> transmitters = device.getTransmitters();
            //and for each transmitter

            for(int j = 0; j<transmitters.size();j++) {
                //create a new receiver
                transmitters.get(j).setReceiver(
                        //using my own MidiInputReceiver
                        new MidiInputReceiver(fxmls, q, device.getDeviceInfo().toString())
                );
            }

            Transmitter trans = device.getTransmitter();
            trans.setReceiver(new MidiInputReceiver(fxmls, q, device.getDeviceInfo().toString()));

            //open each device
            device.open();
            //if code gets this far without throwing an exception
            //print a success message
            System.out.println(device.getDeviceInfo()+" Was Opened");

            load_success = true;
            device_name = device.getDeviceInfo().toString();
            

        } catch (MidiUnavailableException e) {}
    }

    // public void setPianoGUIReference(B)
}
//tried to write my own class. I thought the send method handles an MidiEvents sent to it
public class MidiInputReceiver implements Receiver {
    public String name;
    private FXMLLoader fxmls[];
    private PianoController pianoController[];
    public ConcurrentLinkedQueue<Pair<Boolean,Pair<Integer,Integer>>> q;

    public void setPianoControllers(PianoController pc[]) {
        pianoController = pc;
    }
    public MidiInputReceiver(FXMLLoader fx[], ConcurrentLinkedQueue<Pair<Boolean,Pair<Integer,Integer>>> q, String name) {
        this.name = name;
        this.fxmls = fx;
        this.q = q;
        new Thread(() -> {
            while (true) {
                if (!q.isEmpty()) {
                    Pair<Boolean,Pair<Integer,Integer>> p = q.poll();
                    Pair<Integer, Integer> note_p = p.getValue();
                    if (note_p.getValue() >= 0) {
                        PianoController pc = fxmls[note_p.getValue()].getController();
                        if (p.getKey()) {
                            pc.keyOn(note_p.getKey());
                        } else {
                            pc.keyOff(note_p.getKey());
                        }
                    }
                }
            }
        }).start();
    }
    public void send(MidiMessage msg, long timeStamp) {
        if (msg instanceof ShortMessage) {
            ShortMessage sm = (ShortMessage) msg;
            if (sm.getCommand() == NOTE_ON) {
                int key = sm.getData1();
                int octave = (key / 12)-1;
                int note = key % 12;
                String noteName = NOTE_NAMES[note];
                int velocity = sm.getData2();
                System.out.println(noteName+octave);
                Pair<Integer,Integer> p = new Pair(note, octave);
                Pair<Boolean,Pair<Integer,Integer>> b = new Pair(true, p);
                q.add(b);
                // PianoController pc = fxmls[octave].getController();
                // pc.keyOn(note);
                // System.out.println("Note " + ((sm.getCommand()==NOTE_OFF)?"off: ":"on: ") + noteName + octave + " key=" + key + " velocity: " + velocity);
                
            } else {
                int key = sm.getData1();
                int octave = (key / 12)-1;
                int note = key % 12;
                String noteName = NOTE_NAMES[note];
                int velocity = sm.getData2();
                System.out.println("Command:" + sm.getCommand());
                Pair<Integer,Integer> p = new Pair(note, octave);
                Pair<Boolean,Pair<Integer,Integer>> b = new Pair(false, p);
                q.add(b);
                // PianoController pc = fxmls[octave].getController();
                // pc.keyOff(note);
            }
        }
    }
    public void close() {}
    }




}