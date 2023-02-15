import java.io.File;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Screen;
import javafx.stage.Stage;

public class PickSongsController implements Initializable{
    private boolean buttonPressed = false;

    @FXML
    private VBox holdSongs;

    @FXML
    private Button pickSongsButton;
    

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        // TODO Auto-generated method stub        
    }

    public void handleLoadSongsButton(ActionEvent event) {

        if (!buttonPressed) {
            File folder = new File(System.getProperty("user.dir"));

            for (File entry : folder.listFiles()) {
                System.out.println(entry.getName());
                if (entry.getName().endsWith(".mid")) {

                    Button song = new Button(entry.getName());

                    song.setOnAction(new EventHandler<ActionEvent>() {
                        @Override public void handle(ActionEvent e) {
                            try {
                                GUIController.filename = song.getText();
                                Parent PianoGui = FXMLLoader.load(getClass().getResource("/FXML/FXML.fxml"));
                    
                                int screenWidth = (int)Screen.getPrimary().getBounds().getWidth();
                                int screenHeight = (int)Screen.getPrimary().getBounds().getHeight();        
                    
                                Scene piano = new Scene(PianoGui, 1000, 800);
                                piano.getStylesheets().add("/styles/style1.css");
                    
                                Stage win = (Stage)((Node)event.getSource()).getScene().getWindow();
                                win.setScene(piano);
                                win.show();
                                
                            } catch (Exception exc) {
                                System.out.println("You werent supposed to do that: PickSong\n" + e.toString());
                            }
                        }
                    });

                    HBox newSongEntry = new HBox(song);
                    newSongEntry.setAlignment(Pos.CENTER);
                    
                    holdSongs.getChildren().add(newSongEntry);
                }
            }

            buttonPressed = true;
        }              

    }
    
}
