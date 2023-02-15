import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class JavaFXTemplate extends Application {

	Button b1;
	Button b2;
	
	TextField t1;
	TextField t2;
	
	BorderPane bPane;
	
	VBox vBox;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Edward Plesa Homework 3");
		
		t1 = new TextField();
		t2 = new TextField();
		
		b1 = new Button("button 1");
		b2 = new Button("button 2");
		
		bPane = new BorderPane();
		vBox = new VBox();
		
		bPane.setStyle("-fx-background-color: #0efeef;");
		
		t1.setPromptText("enter text here then press button 1");
		t2.setEditable(false);
		t2.setText("final string goes here");
		
		bPane.setCenter(t1);
		bPane.setRight(t2);
		
		vBox.getChildren().add(b1);
		vBox.getChildren().add(b2);
		
		bPane.setLeft(vBox);
		
		b1.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent e) {
				String concat = t1.getText() + " : from the center text field!";	
				t2.setText(concat);
				b1.setDisable(true);
				b1.setText("pressed");
			}
		});
		
		b2.setOnAction(e-> {
							t1.setText("");
							t2.setText("");
							t2.setText("final string goes here");
							b1.setDisable(false);
							b1.setText("button one");
		});
				
		Scene scene = new Scene(bPane, 800,400);
		primaryStage.setScene(scene);
		primaryStage.show();
	}

}
