import java.net.URL;
import java.util.ResourceBundle;

import javax.swing.text.StyledEditorKit.BoldAction;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.stage.Screen;
import javafx.stage.PopupWindow.AnchorLocation;

public class PianoController implements Initializable {

    @FXML
    Button A;
    @FXML
    Button B;
    @FXML
    Button C;
    @FXML
    Button D;
    @FXML
    Button E;
    @FXML
    Button F;
    @FXML
    Button G;
    @FXML
    Button ASharp;
    @FXML
    Button CSharp;
    @FXML
    Button DSharp;
    @FXML
    Button FSharp;
    @FXML
    Button GSharp;


    @Override
    public void initialize(URL location, ResourceBundle resources) {
        // TODO Auto-generated method stub
    }

    public void keyOn(int note) {
        Button b;
        boolean is_black = false;
        switch (note) {
            case 9: b = A; break;
            case 10: b = ASharp; is_black = true; break;
            case 11: b = B; break;
            case 0: b = C; break;
            case 1: b = CSharp; is_black = true; break;
            case 2: b = D; break;
            case 3: b = DSharp; is_black = true; break;
            case 4: b = E; break;
            case 5: b = F; break;
            case 6: b = FSharp; is_black = true; break;
            case 7: b = G; break;
            case 8: b = GSharp; is_black = true; break;
            default: b = A;
        }
        if (is_black) {
            b.getStyleClass().remove("black-key");
            b.getStyleClass().add("black-key-midi");
        } else {
            b.getStyleClass().remove("white-key");
            b.getStyleClass().add("white-key-midi");
        }
    }

    public void keyOff(int note) {
        Button b;
        boolean is_black = false;
        switch (note) {
            case 9: b = A; break;
            case 10: b = ASharp; is_black = true; break;
            case 11: b = B; break;
            case 0: b = C; break;
            case 1: b = CSharp; is_black = true; break;
            case 2: b = D; break;
            case 3: b = DSharp; is_black = true; break;
            case 4: b = E; break;
            case 5: b = F; break;
            case 6: b = FSharp; is_black = true; break;
            case 7: b = G; break;
            case 8: b = GSharp; is_black = true; break;
            default: b = A;
        }
        if (is_black) {
            b.getStyleClass().add("black-key");
            b.getStyleClass().remove("black-key-midi");
        } else {
            b.getStyleClass().add("white-key");
            b.getStyleClass().remove("white-key-midi");
        }
    }

    
    
}
