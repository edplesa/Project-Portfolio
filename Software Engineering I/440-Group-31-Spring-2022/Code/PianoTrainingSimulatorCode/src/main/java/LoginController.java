import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Screen;
import javafx.stage.Stage;

public class LoginController implements Initializable{

    @FXML
    private Label userNameLabel;

    @FXML
    private Label userPassLabel;

    @FXML
    private TextField userNameIn;   

    @FXML
    private TextField userPassIn; 

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        // TODO Auto-generated method stub        
    }

    public void handleLoginButton(ActionEvent event) {
        String userName = userNameIn.getText();
        String userPass = userPassIn.getText();

        // TODO: 
        // Process users from a file and check if the login matches any of them
        // only then may the user be allowed to continue to the next screen
        
        try {
            Parent PianoGui = FXMLLoader.load(getClass().getResource("/FXML/PickSongs.fxml"));

            //int screenWidth = (int)Screen.getPrimary().getBounds().getWidth();
            int screenHeight = (int)Screen.getPrimary().getBounds().getHeight();        

            Scene piano = new Scene(PianoGui, 400, screenHeight*.85);
            piano.getStylesheets().add("/styles/pickSongsStyle.css");

            Stage win = (Stage)((Node)event.getSource()).getScene().getWindow();
            win.setScene(piano);
            win.show();
            
        } catch (Exception e) {
            System.out.println("You werent supposed to do that: Login");
        }
        

    }
    
}
