import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/*
 * Author: Edward Plesa
 * CS 342
 * Design Pattern Choice: Abstract Factory
 * Homework 4
 */

public class JavaFXTemplate extends Application {

	BorderPane bPane;
	TextField t1;
	TextField t2;
	
	VBox holdInfo;
	
	Label info;
	
	Button b1;
	
	Button b2 = new Button();
	
	AbstractFactory whichFactory;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Weapons of Mass Destruction Order Form");
		
		
		bPane = new BorderPane();
		
		holdInfo = new VBox(15);
		
		b1 = new Button("Choose Factory");
		
		info = new Label(" Welcome to the Weapons of Mass Destruction Order Form!\n This form will act as the middle man for "
				+ "the vehicle of your choice.\n In the box below please specifiy from which factory you would like\n to order your desired "
				+ "vehicle. (Choose from: Jet, Boat, or Tank)");
		
		t1 = new TextField();
		t1.setMaxWidth(300);
		t1.setPromptText("Enter Factory Choice (Jet, Boat or Tank)... ");
		
		holdInfo.getChildren().addAll(info,t1,b1);
		
				
		b1.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent e){
				b1.setDisable(true);
				String choice = t1.getText();
				whichFactory = VehicleProducer.getFactory(t1.getText());
				Label info2 = null;
				
				if (choice.equalsIgnoreCase("JET")) {
					info2 = new Label("Please pick from SU50 or F35 jet options.");
					t2 = new TextField();
					t2.setMaxWidth(300);
					t2.setPromptText("Pick SU50 or F35");
					b2.setText("Pick Jet");
				} 
				else if (choice.equalsIgnoreCase("Boat")) {
					info2 = new Label("Please pick from RCB or DV15 boat options.");
					t2 = new TextField();
					t2.setMaxWidth(300);
					t2.setPromptText("Pick RCB or DV15");
					b2.setText("Pick Boat");
				}
				else if (choice.equalsIgnoreCase("Tank")) {
					info2 = new Label("Please pick from T90 or Abrams boat options.");
					t2 = new TextField();
					t2.setMaxWidth(300);
					t2.setPromptText("Pick T90 or Abrams");
					b2.setText("Pick Tank");
				}			
				
				holdInfo.getChildren().addAll(info2, t2,b2);	
								
			}
		});
		
		
		b2.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent e){
				Vehicle vehicleChosen = whichFactory.getVehicle(t2.getText());
				Label info3 = new Label(vehicleChosen.whatType() + "\nRestart this app to pick new vehicle!");
				holdInfo.getChildren().addAll(info3);	
			}
		});
		
		bPane.setCenter(holdInfo);
				
		Scene scene = new Scene(bPane, 375,325);
		primaryStage.setScene(scene);
		primaryStage.show();
	}

}
