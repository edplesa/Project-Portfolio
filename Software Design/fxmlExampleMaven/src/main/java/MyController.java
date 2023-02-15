

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;

public class MyController implements Initializable {
	
	@FXML
	private BorderPane root;	
    
    @FXML
    private TextField t1;
    
    @FXML
    private TextField t2;
    
    @FXML
    private Button b1;

    @FXML
    private Button b2;
	

	@Override
	public void initialize(URL location, ResourceBundle resources) {
		// TODO Auto-generated method stub
	}  
	
	
	//method so that the controller created for second view can update the text
    //field with the text from the first view
	public void handleB1() throws IOException{
		String concat = t1.getText() + " : from the center text field!";	
		t2.setText(concat);
		b1.setDisable(true);
		b1.setText("pressed");
	}
	
	public void handleB2() throws IOException{
		t1.setText("");
		t2.setText("");
		t2.setText("final string goes here");
		b1.setDisable(false);
		b1.setText("button one");
	}	
    

}
