import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

public class CoffeeShop extends Application {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		/*
		// TODO Auto-generated method stub
		primaryStage.setTitle("Who want's coffee!!!");
		
		Scene scene = new Scene(new HBox(),600,600);
		primaryStage.setScene(scene);
		primaryStage.show();
		
		Coffee order = new Sugar(new Cream( new ExtraShot(new BasicCoffee())));
		
		double cost = order.makeCoffee();
		System.out.println("Total: "+cost);
		
		*/
		
		try {
            // Read file fxml and draw interface.
            Parent root = FXMLLoader.load(getClass()
                    .getResource("/FXML/Myfxml.fxml"));
 
            primaryStage.setTitle("Who want's coffee!!!");
         Scene s1 = new Scene(root, 400,500);
         s1.getStylesheets().add("/styles/style1.css");
            primaryStage.setScene(s1);
            primaryStage.show();
         
        } catch(Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
	}

}
