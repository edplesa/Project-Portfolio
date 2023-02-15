import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.application.Platform;


public class JavaFXTemplate extends Application {

	EventHandler<ActionEvent> myHandler;
	MenuBar menu;
	int playerTurn = 0;	
	ListView<String> showPlayerTurn;
	GridPane grid;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Simple Tic-Tac-Toe Game");		
		
		
		
		myHandler = new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent e) {
				
				Button b1 = (Button)e.getSource();
				
				b1.setDisable(true);
				
				
				
				if (playerTurn == 0) {
					b1.setText("X");
					b1.setStyle("-fx-font-size:40;" + "-fx-color: pink;");
					playerTurn = 1;
					showPlayerTurn.getItems().add("O is now picking!");
				} else {
					b1.setText("O");
					b1.setStyle("-fx-font-size:40;" + "-fx-color: orange;");
					playerTurn = 0;
					showPlayerTurn.getItems().add("X is now picking!");
				}
				
			}			
		};
		
		
		menu = new MenuBar();
		menu.setStyle("-fx-background-color: lightblue");
		
		Menu startOver = new Menu("Start Over");
		MenuItem sItem = new MenuItem("Redo");
		sItem.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent e) {
				playerTurn = 0;				
				
				grid = new GridPane();
				grid.setAlignment(Pos.CENTER);
				addGrid(grid);
				showPlayerTurn = new ListView<>();
				
				
				showPlayerTurn.setPrefHeight(200);
				showPlayerTurn.setStyle("-fx-font-size: 18;" + "-fx-border-size: 20;" + "-fx-border-color: green;");
				showPlayerTurn.getItems().add("New Game Start!");
				showPlayerTurn.getItems().add("X is now picking!");
				
				
				Scene newscene = new Scene(new VBox(20, menu, showPlayerTurn, grid), 700,600);
				
				primaryStage.setScene(newscene);
				primaryStage.show();
			}
			
		});
		
		Menu exitGame = new Menu("Exit Game");		
		MenuItem eItem = new MenuItem("Close");
		eItem.setOnAction(e->primaryStage.close());
		
		
		startOver.getItems().add(sItem);
		exitGame.getItems().add(eItem);
		
		menu.getMenus().addAll(startOver, exitGame);
		
		showPlayerTurn = new ListView<>();
		showPlayerTurn.setPrefHeight(200);
		showPlayerTurn.setStyle("-fx-font-size: 18;" + "-fx-border-size: 20;" + "-fx-border-color: green;");
		showPlayerTurn.getItems().add("New Game Start!");
		showPlayerTurn.getItems().add("X is now picking!");
		
		grid = new GridPane();
		grid.setAlignment(Pos.CENTER);
		addGrid(grid);
		
		
		
				
		Scene scene = new Scene(new VBox(20, menu, showPlayerTurn, grid), 700,600);		
		primaryStage.setScene(scene);
		primaryStage.show();
	}
	
	public void addGrid(GridPane grid) {
		
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++ ) {
				Button b1 = new Button("");
				b1.setStyle("-fx-color: yellow;");
				b1.setPrefSize(90,90);				
				b1.setOnAction(myHandler);
				grid.add(b1, i, j);
				
			}
		}
	}

	

}
