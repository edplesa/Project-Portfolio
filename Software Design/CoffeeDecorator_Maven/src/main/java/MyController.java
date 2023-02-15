

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.scene.layout.HBox;

import javafx.scene.control.ListView;
import java.text.DecimalFormat;

public class MyController implements Initializable {
	MakeCoffee c1 = new MakeCoffee();
	
	@FXML
	private BorderPane root;
	
	@FXML
	private Button makeOrder;
    
    @FXML
    private Button addSugar;
    
    @FXML
    private Button addCream;
    
    @FXML
    private Button addExtraShot;
    
    @FXML
    private Button addSprinkles;
    
    @FXML
    private Button addPumpkinSpice;
    
    String coffeeWithAddons = "Black Coffee: $3.99\n";
    
    @FXML
    private Label orderForm = new Label();
	

	@Override
	public void initialize(URL location, ResourceBundle resources) {
		// TODO Auto-generated method stub
	}  
	
	
	//method so that the controller created for second view can update the text
    //field with the text from the first view
	public void handleAddSugar() throws IOException{
		c1.withSugar();
		coffeeWithAddons += " + sugar: $.50\n";
		orderForm.setText(coffeeWithAddons);
	}	
	
    
	public void handleAddExtraShot() throws IOException{
		c1.withExtraShot();
		coffeeWithAddons += " + extra shot: $1.20\n";
		orderForm.setText(coffeeWithAddons);
	}		
	
	
	public void handleAddCream() throws IOException{
		c1.withCream();
		coffeeWithAddons += " + cream: $.50\n";
		orderForm.setText(coffeeWithAddons);
	}	
	
	
	public void handleAddPumpkinSpice() throws IOException{
		c1.withPumpkinSpice();
		coffeeWithAddons += " + pumpkin spice: $.35\n";
		orderForm.setText(coffeeWithAddons);
	}		
	
	
	public void handleAddSprinkles() throws IOException{
		c1.withSprinkles();
		coffeeWithAddons += " + sprinkles: $.25\n";
		orderForm.setText(coffeeWithAddons);
	}	
	
		
	
	public void handleMakeOrder() throws IOException{
		System.out.println(c1.getOrder());
		makeOrder.setDisable(true);
		
		addSugar.setDisable(true);
		addCream.setDisable(true);
		addExtraShot.setDisable(true);
		addSprinkles.setDisable(true);
		addPumpkinSpice.setDisable(true);
		
		DecimalFormat dec = new DecimalFormat("0.00");
		
		coffeeWithAddons += "\nTotal Cost: $" + dec.format(c1.getOrder());
		orderForm.setText(coffeeWithAddons);
	}
	
	public void handleResetOrder() throws IOException{
		c1 = new MakeCoffee();		
		coffeeWithAddons = "Black Coffee: $3.99\n";
		orderForm.setText(coffeeWithAddons);
		makeOrder.setDisable(false);

		addSugar.setDisable(false);
		addCream.setDisable(false);
		addExtraShot.setDisable(false);
		addSprinkles.setDisable(false);
		addPumpkinSpice.setDisable(false);
	}
    

}
