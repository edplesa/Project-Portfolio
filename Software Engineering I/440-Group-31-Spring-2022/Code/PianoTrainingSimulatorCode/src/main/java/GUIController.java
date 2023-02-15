import java.io.IOException;
import java.net.URL;
import javafx.util.Duration;
import java.util.*;
import java.util.Arrays;
import java.util.ResourceBundle;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.function.IntToDoubleFunction;

import javax.print.DocFlavor;
import javax.sound.midi.Instrument;
import javax.sound.midi.MidiChannel;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Synthesizer;

import javafx.animation.Interpolator;
import javafx.animation.KeyFrame;
import javafx.animation.PathTransition;
import javafx.animation.PauseTransition;
import javafx.animation.Timeline;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.Insets;
import javafx.scene.*;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.*;
import javafx.scene.shape.Line;
import javafx.scene.text.Text;
import javafx.stage.Screen;
import javafx.stage.Stage;


public class GUIController implements Initializable {


    /*
        Numbers for Piano GUI sizing:
    */
    private final int NUM_OCTAVES = 7;

    private final int SCREEN_WIDTH = (int)Screen.getPrimary().getBounds().getWidth();
    private final int SCREEN_HEIGHT = (int)Screen.getPrimary().getBounds().getHeight();

    private final double KEYBOARD_DEFAULT_WIDTH  = 700; // -> default size in Piano.fxml
    private final double KEYBOARD_DEFAULT_HEIGHT = 450; // -> default size in Piano.fxml

    private final double HEIGHT_CEILING = Math.ceil(1/(KEYBOARD_DEFAULT_HEIGHT/SCREEN_HEIGHT))+1;
    private final double WIDTH_CEILING  = Math.ceil(1/(KEYBOARD_DEFAULT_WIDTH/SCREEN_WIDTH))+1;
    /*
        * Note: Ideally will work on any screen size, have only tested on one screen size so far
                - Ryan
    */




    /*
        Globals handy for GUI Controller:
    */
    MidiParser        midiParser  = new MidiParser();
    MidiDeviceHandler midiHandler = new MidiDeviceHandler();
    
    LinkedList<SlidingNoteData> listOfNotesToAnimate;

    public static String filename = "";

//    AnchorPane[] pianoAnchorPanes = new AnchorPane[NUM_OCTAVES];
//    GridPane[]   pianoGridPanes   = new GridPane[NUM_OCTAVES];
    double col_constraint_size = (KEYBOARD_DEFAULT_WIDTH/WIDTH_CEILING)/12;
    double row_constraint_size = (SCREEN_HEIGHT * .3);

    MidiChannel[] mChannels;
    Instrument[] instr;
    Synthesizer midiSynth;
    
    FXMLLoader fxmls[] = new FXMLLoader[12];
    /*

    */



    /*
        FXML Objects:
    */
    @FXML
    Button b;

//    @FXML
//    BorderPane Root;

    @FXML
    Pane animationGroup;

    @FXML
    Button createNewSlidyThingButton;

    @FXML
    HBox pianoScene;

    @FXML
    GridPane pianoGridPane;

    @FXML
    Label keyboardConnectionLabel;
    /*

    */




    /*
        If you run this, you'll see that there is a line for every key on the keyboard
        However, they aren't perfectly lined up.
        
        Additionally, the lines are lined up
        perfectly >:( I suspect that's something to with the way the piano GUI's are
        sitting in the VBox, maybe they should be 'centered'?

            ** The key to fixing those things is in this initialize function !!! :) lol
    */  
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        /*
            The following try statement sets up the Piano GUI and note paths:
        */
//        try {
//            //
//            // Add piano subscenes to GUI programmatically:
//            for (int i = 0; i < NUM_OCTAVES; i++) { // 7 Octaves? Could make it a different number, just decided with a google search of typical number of octaves on a keyboard
//                //
//                // Load the piano FXML:
//                FXMLLoader loader = new FXMLLoader(getClass().getResource("FXML/Piano.fxml"));
//                pianoAnchorPanes[i] = loader.load();
//                fxmls[i] = loader;
//                //
//                // Add to AnchorPane:
//                pianoScene.getChildren().add(pianoAnchorPanes[i]);
//                //
//                // Create Grid pane to sit above piano:
//                GridPane gp = new GridPane();
//                for (int j = 0; j < 12; j++) {
//                    /*
//                        In this for loop is where the gridpanes are (attemptedly) lined
//                        up with the gridpanes. Works... somewhat? Perhaps good enough
//                        for the demo LOL
//                    */
//                    ColumnConstraints column = new ColumnConstraints(col_constraint_size);
//                    gp.getColumnConstraints().add(column);
//                    Line line = new Line(0, -400, 0, 200); // <- **This is the phyiscal path
//                    gp.add(line, j, 0);
//                }
//                RowConstraints row = new RowConstraints(row_constraint_size);
//                gp.getRowConstraints().add(row);
//                pianoGridPanes[i] = gp;
//                //
//                // Add gridpane and piano to screen:
//                pianoScene.getChildren().add(new VBox(gp, pianoAnchorPanes[i]));
//                //
//                // Set size of the piano subscene:
//                pianoAnchorPanes[i].setScaleX(1/WIDTH_CEILING);
//                pianoAnchorPanes[i].setScaleY(1/HEIGHT_CEILING);
//                pianoAnchorPanes[i].setMaxHeight(KEYBOARD_DEFAULT_HEIGHT/HEIGHT_CEILING);
//                pianoAnchorPanes[i].setMinHeight(KEYBOARD_DEFAULT_HEIGHT/HEIGHT_CEILING);
//                pianoAnchorPanes[i].setMaxWidth(KEYBOARD_DEFAULT_WIDTH/WIDTH_CEILING);
//                pianoAnchorPanes[i].setMinWidth(KEYBOARD_DEFAULT_WIDTH/WIDTH_CEILING);
//            }
//            //
//            // Piano styles and junk
//            pianoScene.getStylesheets().add("/styles/piano.css");
//
//        } catch (IOException e) {
//            System.out.print("THE PIANOS DIDN'T LOAD >:(");
//            e.printStackTrace();
//        }

        try {
            pianoGridPane = FXMLLoader.load(getClass().getResource("/FXML/Piano.fxml"));
            pianoGridPane.getStylesheets().add("/styles/piano.css");
            pianoScene.getChildren().add(pianoGridPane);
            pianoGridPane.setPrefWidth(SCREEN_WIDTH);
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("ERROR!!!\n");
        }
//                pianoScene.getChildren().add(pianoAnchorPanes[i]);
//        } catch (IOException e) {
//            System.out.print("THE PIANOS DIDN'T LOAD >:(");
//            e.printStackTrace();
//        }



        try {
            midiSynth = MidiSystem.getSynthesizer(); 
            midiSynth.open();
        } catch (Exception e) {
            System.out.println(e.toString());
        }
        //
        // Get and load default instrument and channel lists:
        instr = midiSynth.getDefaultSoundbank().getInstruments();
        mChannels = midiSynth.getChannels();
        
        midiSynth.loadInstrument(instr[0]);//load an instrument
    }



    public void playSong(ActionEvent event) throws IOException {
        listOfNotesToAnimate = midiParser.parseMidiFileIntoNotes(filename);
        if (listOfNotesToAnimate == null) {
            System.out.println("uh oh...");
            return;
        }
        beginSlidingNotes((LinkedList<SlidingNoteData>)listOfNotesToAnimate.clone());
    }

    public void connectMidiKeyBoard(ActionEvent event) throws IOException {

    }



    public void loadMidiKeyboard(ActionEvent e) throws IOException {
        keyboardConnectionLabel.setText("LOADING KEYBOARD...");
        PauseTransition pause = new PauseTransition(Duration.millis(100));
        pause.setOnFinished(event -> {
            midiHandler.loadMidiDevice(fxmls);
            if (midiHandler.load_success) {
                keyboardConnectionLabel.getStyleClass().remove("labelKeyboardNotLoaded");
                keyboardConnectionLabel.getStyleClass().add("labelKeyboardLoaded");
                keyboardConnectionLabel.setText("Key Board Connected: " + midiHandler.device_name);
            } else {
                keyboardConnectionLabel.setText("KEYBOARD COULD NOT BE LOADED...");
            }
        });
        pause.play();
    }



    /*

    Animation Functions (NEED FINE TUNING)

    (A couple of them are redundant)

    */

    private void beginSlidingNotes(LinkedList<SlidingNoteData> notes) {
        SlidingNoteData snd = notes.poll();
        newSlidingNote(snd);
        if (!notes.isEmpty()) {
            long diff = notes.peek().start-snd.start;
            // System.out.println(diff);
            PauseTransition pause = new PauseTransition(Duration.millis((diff < 0) ? 0 : diff));
            pause.setOnFinished(e -> {
                beginSlidingNotes(notes);
            });
            pause.play();
        }
    }

    private void newSlidingNote(SlidingNoteData snd) {
        //
        // Create path for note to follow:
        Line line = new Line(0, -400, 0, 200); // <- **This is the phyiscal path
        //
        // Define how the note will move:
        PathTransition transition = new PathTransition();
        transition.setInterpolator(Interpolator.LINEAR);
        Button box = new Button(); // <- Physical note
        box.setMinHeight((snd.end-snd.start) / 5);
        box.setMaxWidth(46*KEYBOARD_DEFAULT_WIDTH/SCREEN_WIDTH); // won't change size? >:( (46 is the default width in the FXML)
        //
        // Some more details for animation
        transition.setNode(box);
        transition.setDuration(Duration.seconds(2.3));
        transition.setPath(line);
        transition.setCycleCount(1);
        /* ABEL: The transitions need to be changed from pianoGridPanes[] to the single pianoGridPane, but we need to
        add objects to the 0-11th columns in the 0th row (like VBoxes) to hold the sliding notes and have them traverse
        down the grid lines. */
//        transition.setOnFinished(e -> pianoGridPanes[snd.octave-1].getChildren().remove(box));
        //
        // Add path and note to gridpane in
        // their respective columns:
//        pianoGridPanes[snd.octave-1].add(line, snd.note, 0);
//        pianoGridPanes[snd.octave-1].add(box,  snd.note, 0);
        transition.play();
    }

    public void handleBackToLogin(ActionEvent event) throws IOException {
        Parent LoginGui = FXMLLoader.load(getClass().getResource("/FXML/Login.fxml"));
        Scene loginScene = new Scene(LoginGui, 400, 200);

        loginScene.getStylesheets().add("/styles/loginStyle.css");


        Stage win = (Stage)((Node)event.getSource()).getScene().getWindow();
        win.setScene(loginScene);
        win.show();
    }

    public void handleBackToSongs(ActionEvent event) throws IOException {
        Parent PianoGui = FXMLLoader.load(getClass().getResource("/FXML/PickSongs.fxml"));
        int screenHeight = (int)Screen.getPrimary().getBounds().getHeight();        

        Scene piano = new Scene(PianoGui, 400, screenHeight*.85);
        piano.getStylesheets().add("/styles/pickSongsStyle.css");

        Stage win = (Stage)((Node)event.getSource()).getScene().getWindow();
        win.setScene(piano);
        win.show();
    }

}









/*


width = 700 * SCREEN_HEIGHT / x;
height = 450 * SCREEN_HEIGHT / x;



*/