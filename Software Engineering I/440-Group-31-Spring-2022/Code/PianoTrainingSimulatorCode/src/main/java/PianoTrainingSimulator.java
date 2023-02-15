import java.util.HashMap;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

public class PianoTrainingSimulator extends Application {
	
	ListView<String> listItems, listItems2;

    @Override
    public void start(Stage primaryStage) throws Exception {

        //
        // Set the title at the top of the window
        primaryStage.setTitle("Piano Training Simulator");

        //
        // Set the initial fxml file:
        Parent LoginGui = FXMLLoader.load(getClass().getResource("/FXML/Login.fxml"));

        // GraphicsDevice gd = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();
        // int width = gd.getDisplayMode().getWidth();
        // int height = gd.getDisplayMode().getHeight();       


        //
        // Initialize start the app:
        Scene loginScene = new Scene(LoginGui, 400, 200);
        loginScene.getStylesheets().add("/styles/loginStyle.css");

        primaryStage.setScene(loginScene);
        primaryStage.show();
        primaryStage.setMinWidth(600);
        primaryStage.setMinHeight(980);
    }
    
    public static void main(String[] args) {
		launch(args);
	}

  
}