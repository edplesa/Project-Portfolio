import java.util.HashMap;
import java.util.Stack;

import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Duration;

/*
 * Author: Edward Plesa
 * NetID: eplesa2
 * CS342
 * Project 2: Connect 4 
 * 
 * Partner: None
 */

public class JavaFXTemplate extends Application {
	//BorderPane startBPane;
	EventHandler<ActionEvent> myHandler;
	Button startButton;
	Button endProgramButton;
	Button newGameButton;
	HashMap<String, Scene> sceneMap; 
	MenuBar gameMenu;
	GridPane gameGrid;
	ListView<Label> displayPlayerTurn;
	PauseTransition pause = new PauseTransition(Duration.seconds(3));
	int winnerNum = -1;
	
	Text playerPicking;
	
	ObservableList<Label> storeStackItemsInListView = FXCollections.observableArrayList();
	Stack<Label> turns = new Stack<>();
	Stack<GameButton> buttonStack = new Stack<>();
	
	GameButton buttonArray[][];
	int playerTurn = 0;	
	BorderPane gamePane;
	Menu gamePlayMenu;
	Menu themesMenu;
	Menu optionsMenu;
	
	MenuItem gpItem;
	
	MenuItem themeOrig;
	MenuItem themeOne;
	MenuItem themeTwo;
	
	MenuItem optionsHowTo;
	MenuItem optionsNewGame;
	MenuItem optionsExit;
	
	int movesMade = 0;
	
	int themeNum = 0; // 0 = originalTheme | 1 = themeOne | 2 = themeTwo

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Welcome to Connect Four!");
		
		myHandler = new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent e) {
				
				GameButton b1 = (GameButton)e.getSource();
				
				if (buttonArray[b1.getRow()][b1.getCol()].canBeClicked ) {					
					if (b1.getRow() != 0) {
						buttonArray[b1.getRow()-1][b1.getCol()].canBeClicked = true;
					}
					else {
						buttonArray[0][b1.getCol()].canBeClicked = true;
					}
					
					
					b1.setDisable(true);
					if (playerTurn == 0) {			
						b1.player = 0;
						b1.setStyle("-fx-color: red;");
						playerTurn = 1;
						turns.push(new Label("Player 1 moved to: [" + b1.getRow() + "," + b1.getCol() + "]."));
						buttonStack.push(b1);
						displayPlayerTurn.getItems().add(turns.peek());		
						playerPicking.setText("Player Picking: " + (playerTurn + 1) + " (Yellow)");
						if (checkWin(0)) {
							for (int i = 0; i < 7; i++) {
								for (int j = 0; j < 6; j++ ) {
									buttonArray[j][i].setDisable(true);				
								}
							}
							winnerNum = 1;
							pause.setOnFinished(r->primaryStage.setScene(createEndScene()));
							pause.play();
						}
					} else {				
						b1.player = 1;
						b1.setStyle("-fx-color: yellow;");
						playerTurn = 0;
						turns.push(new Label("Player 1 moved to: [" + b1.getRow() + "," + b1.getCol() + "]."));
						buttonStack.push(b1);
						displayPlayerTurn.getItems().add(turns.peek());	
						playerPicking.setText("Player Picking: " + (playerTurn + 1)  + " (Red)");
						if (checkWin(1)) {
							for (int i = 0; i < 7; i++) {
								for (int j = 0; j < 6; j++ ) {
									buttonArray[j][i].setDisable(true);				
								}
							}
							winnerNum = 2;
							pause.setOnFinished(r->primaryStage.setScene(createEndScene()));		
							pause.play();
						}
					}
					
				} else {
					if (playerTurn == 0)
						displayPlayerTurn.getItems().add(new Label("Player 1 moved to [" + b1.getRow() + "," + b1.getCol() + "]. Invalid move. Player 1 pick again." ));
					else
						displayPlayerTurn.getItems().add(new Label("Player 2 moved to [" + b1.getRow() + "," + b1.getCol() + "]. Invalid move. Player 2 pick again." ));
				}
				movesMade++;
				if (movesMade == 42) {
					pause.setOnFinished(r->primaryStage.setScene(createEndScene()));		
					pause.play();
				}
				displayPlayerTurn.scrollTo(displayPlayerTurn.getItems().size() - 1);				
			}			
		};
		
		
	
		
		// Setup startScene
		sceneMap = new HashMap<String,Scene>();
		
		startButton = new Button("Click to Start");
		startButton.setPrefSize(140,100);
		startButton.setStyle("-fx-font-size:15");
		
		endProgramButton =  new Button("Exit");
		newGameButton = new Button("New Game");
		endProgramButton.setPrefSize(140,100);
		newGameButton.setPrefSize(140,100);
		endProgramButton.setStyle("-fx-font-size:20");
		newGameButton.setStyle("-fx-font-size:20");
		endProgramButton.setOnAction(e->primaryStage.close());
		
		playerPicking = new Text();
		
		newGameButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				Scene newgame = reinitBoard();
				primaryStage.setScene(newgame);
				primaryStage.show();							
			}
		});
		
		startButton.setOnAction(e -> primaryStage.setScene(sceneMap.get("gameScene")));
		
		
		// Setup gameScene
		
			// set up Menu Bar
		gameMenu = new MenuBar();
		
		gamePlayMenu = new Menu("Game Play");
		themesMenu = new Menu("Themes");
		optionsMenu = new Menu("Options");
		
		gpItem = new MenuItem("Reverse Move");	
		
		themeOrig = new MenuItem("Original Theme");
		themeOne = new MenuItem("Theme 1");
		themeTwo = new MenuItem("Theme 2");
		
		themeOrig.setOnAction(e->originalTheme());
		themeOne.setOnAction(e->setThemeOne());
		themeTwo.setOnAction(e->setThemeTwo());
		
		
		optionsHowTo = new MenuItem("How to Play");
		optionsNewGame = new MenuItem("New Game");
		optionsExit = new MenuItem("Exit");
		
		optionsExit.setOnAction(e->primaryStage.close());
		
		optionsHowTo.setOnAction(new EventHandler<ActionEvent>() {
			
			@Override
			public void handle(ActionEvent event) {
				openHowTo();
			}
		});		

		gamePlayMenu.getItems().addAll(gpItem);		
		themesMenu.getItems().addAll(themeOrig,themeOne, themeTwo);	
		optionsMenu.getItems().addAll(optionsHowTo,optionsNewGame,optionsExit);		
		gameMenu.getMenus().addAll(gamePlayMenu, themesMenu, optionsMenu);
		
			// set up Player turn list view
		
		displayPlayerTurn = new ListView<Label>();
		displayPlayerTurn.setPrefHeight(200);		
		
		
			// set up game grid
		buttonArray = new GameButton[6][7];
		gameGrid = new GridPane();
		gameGrid.setHgap(5);
		gameGrid.setVgap(5);
		addGrid(gameGrid);		
		

		//
		gpItem.setOnAction(new EventHandler<ActionEvent>() {

			@Override
			public void handle(ActionEvent event) {				
				reverseMove();
			}
		});
		
		optionsNewGame.setOnAction(new EventHandler<ActionEvent>() {

			@Override
			public void handle(ActionEvent event) {				
				Scene newgame = reinitBoard();
				primaryStage.setScene(newgame);
				primaryStage.show();							
			}
		});
		
		
		
		sceneMap.put("startScene", createStartScene());
		sceneMap.put("gameScene", createGameScene());		
		
		originalTheme();
		
		primaryStage.setScene(sceneMap.get("startScene"));
		primaryStage.show();
	}
	
	
	public void reverseMove() {
		if (!turns.empty()) {
			turns.pop();
			
			if (playerTurn == 1) 
				playerTurn = 0;
			else
				playerTurn = 1;
			
			GameButton reset = buttonStack.pop();
			
			if (reset.getRow() != 0)
				buttonArray[reset.getRow()-1][reset.getCol()].canBeClicked = false;
			//else
				//buttonArray[0][reset.getCol()].canBeClicked = false;
			
			buttonArray[reset.getRow()][reset.getCol()].player = -1;
			reset.setStyle("-fx-color: lightGray;");
			reset.setDisable(false);
			
			displayPlayerTurn.getItems().removeAll(storeStackItemsInListView);
			storeStackItemsInListView.clear();
			
			for (Label elem: turns) {
				storeStackItemsInListView.add(elem);
			}
			
			displayPlayerTurn.setItems(storeStackItemsInListView);
			
			displayPlayerTurn.scrollTo(displayPlayerTurn.getItems().size() - 1);
			
			if (playerTurn == 0)
				playerPicking.setText("Player Picking: " + (playerTurn + 1)  + " (Red)");
			else
				playerPicking.setText("Player Picking: " + (playerTurn + 1)  + " (Yellow)");
		}	
	}
	
	public void openHowTo() {
		Label secondLabel = new Label("Decide who is Player 1 (Red Pieces) and Player 2 \n(Yellow Pieces). Which ever player connect 4 of\ntheir own pieces "
				+ "in a row (either vertically, \nhorizontally, or diagonally, wins.");

		StackPane secondaryLayout = new StackPane();
		secondaryLayout.getChildren().add(secondLabel);

		Scene secondScene = new Scene(secondaryLayout, 300, 100);

		
		Stage newWindow = new Stage();
		newWindow.setTitle("How to Play");
		newWindow.setScene(secondScene);

		
		newWindow.setX(350);
		newWindow.setY(200);

		newWindow.show();
	}
	
	public Scene reinitBoard() {
		movesMade = 0;
		playerTurn = 0;
		gameGrid = new GridPane();
		gameGrid.setHgap(5);
		gameGrid.setVgap(5);
		addGrid(gameGrid);
		
		
		HBox holdPicking = new HBox(playerPicking);
		holdPicking.setAlignment(Pos.CENTER);
		
		
		displayPlayerTurn = new ListView<Label>();
		displayPlayerTurn.setPrefHeight(200);	
		
		turns = new Stack<>();
		
		storeStackItemsInListView.clear();
		
		HBox holdGrid = new HBox(gameGrid);				
		holdGrid.setAlignment(Pos.CENTER);
		playerPicking.setText("Player Picking: " + (playerTurn + 1)+ " (Red)");
		VBox vbox = new VBox(20, gameMenu, displayPlayerTurn, holdGrid, holdPicking);			
		gamePane = new BorderPane(vbox);				
		 
		if (themeNum == 0)
			originalTheme();
		else if (themeNum == 1)
			setThemeOne();
		else 
			setThemeTwo();
		
		Scene newgame = new Scene(gamePane, 700,700);
		return newgame;
	}
	
	
	public boolean checkWin(int playerNum) {
		// horizontal
		for (int c = 0; c < 4; c++) {
			for (int r = 0; r < 6; r++) {
				if (buttonArray[r][c].player == playerNum && buttonArray[r][c+1].player == playerNum && buttonArray[r][c+2].player == playerNum && buttonArray[r][c+3].player == playerNum ) {
					System.out.println("We have a winner! " + playerNum);
					buttonArray[r][c].setStyle("-fx-color: purple;");
					buttonArray[r][c+1].setStyle("-fx-color: purple;");
					buttonArray[r][c+2].setStyle("-fx-color: purple;");
					buttonArray[r][c+3].setStyle("-fx-color: purple;");
					return true;
				}
			}
		}
		//vertical
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 7; c++) {
				if (buttonArray[r][c].player == playerNum && buttonArray[r+1][c].player == playerNum && buttonArray[r+2][c].player == playerNum && buttonArray[r+3][c].player == playerNum ) {
					System.out.println("We have a winner! " + playerNum);
					buttonArray[r][c].setStyle("-fx-color: purple;");
					buttonArray[r+1][c].setStyle("-fx-color: purple;");
					buttonArray[r+2][c].setStyle("-fx-color: purple;");
					buttonArray[r+3][c].setStyle("-fx-color: purple;");
					return true;
				}
			}
		}
		//diagonal1
		for (int r = 3; r < 6; r++) {
			for (int c = 0; c < 4; c++) {
				if (buttonArray[r][c].player == playerNum && buttonArray[r-1][c+1].player == playerNum && buttonArray[r-2][c+2].player == playerNum && buttonArray[r-3][c+3].player == playerNum ) {
					System.out.println("We have a winner! " + playerNum);
					buttonArray[r][c].setStyle("-fx-color: purple;");
					buttonArray[r-1][c+1].setStyle("-fx-color: purple;");
					buttonArray[r-2][c+2].setStyle("-fx-color: purple;");
					buttonArray[r-3][c+3].setStyle("-fx-color: purple;");
					return true;
				}
			}
		}		
		//diagonal2		
		for (int r = 3; r < 6; r++) {
			for (int c = 3; c < 7; c++) {
				if (buttonArray[r][c].player == playerNum && buttonArray[r-1][c-1].player == playerNum && buttonArray[r-2][c-2].player == playerNum && buttonArray[r-3][c-3].player == playerNum ) {
					System.out.println("We have a winner! " + playerNum);
					buttonArray[r][c].setStyle("-fx-color: purple;");
					buttonArray[r-1][c-1].setStyle("-fx-color: purple;");
					buttonArray[r-2][c-2].setStyle("-fx-color: purple;");
					buttonArray[r-3][c-3].setStyle("-fx-color: purple;");
					return true;
				}
			}
		}
		return false;
	}
	
	
	public void originalTheme() {
		themeNum = 0;
		displayPlayerTurn.setStyle("-fx-font-size: 15;"+ 
				"-fx-border-color: darkBlue;" + "-fx-background-color: lightGray;");
		
		gameMenu.setStyle("-fx-background-color: #131317;");
		gamePane.setStyle("-fx-background-color: #131317;");
		
		gamePlayMenu.setStyle("-fx-background-color: #61d5ff;");
		themesMenu.setStyle("-fx-background-color: #61d5ff;");
		optionsMenu.setStyle("-fx-background-color: #61d5ff;");
		
		gpItem.setStyle("-fx-background-color: #61d5ff;");
		
		themeOrig.setStyle("-fx-background-color: #61d5ff;");
		themeOne.setStyle("-fx-background-color: #61d5ff;");
		themeTwo.setStyle("-fx-background-color: #61d5ff;");
		
		optionsHowTo.setStyle("-fx-background-color: #61d5ff;");
		optionsNewGame.setStyle("-fx-background-color: #61d5ff;");
		optionsExit.setStyle("-fx-background-color: #61d5ff;");
		
	}
	
	public void setThemeOne() {
		themeNum = 1;
		displayPlayerTurn.setStyle("-fx-font-size: 15;"+ 
				"-fx-border-color: #F5624D;" + "-fx-background-color: lightGray;");
		
		gameMenu.setStyle("-fx-background-color: #CC231E;");
		gamePane.setStyle("-fx-background-color: #235E6F;");
		
		gamePlayMenu.setStyle("-fx-background-color: #34A65F;");
		themesMenu.setStyle("-fx-background-color: #34A65F;");
		optionsMenu.setStyle("-fx-background-color: #34A65F;");
		
		gpItem.setStyle("-fx-background-color: #F5624D;");
		
		themeOrig.setStyle("-fx-background-color: #F5624D;");
		themeOne.setStyle("-fx-background-color: #F5624D;");
		themeTwo.setStyle("-fx-background-color: #F5624D;");
		
		optionsHowTo.setStyle("-fx-background-color: #F5624D;");
		optionsNewGame.setStyle("-fx-background-color: #F5624D;");
		optionsExit.setStyle("-fx-background-color: #F5624D;");
		
	}
	
	public void setThemeTwo() {
		themeNum = 2;
		displayPlayerTurn.setStyle("-fx-font-size: 15;"+ 
				"-fx-border-color: #B54730;" + "-fx-background-color: lightGray;");
		
		gameMenu.setStyle("-fx-background-color: #A26B35;");
		gamePane.setStyle("-fx-background-color: #C0F1D1;");
		
		gamePlayMenu.setStyle("-fx-background-color: #EBBA38;");
		themesMenu.setStyle("-fx-background-color: #EBBA38;");
		optionsMenu.setStyle("-fx-background-color: #EBBA38;");
		
		gpItem.setStyle("-fx-background-color: #BDB850;");
		
		themeOrig.setStyle("-fx-background-color: #BDB850;");
		themeOne.setStyle("-fx-background-color: #BDB850;");
		themeTwo.setStyle("-fx-background-color: #BDB850;");
		
		optionsHowTo.setStyle("-fx-background-color: #BDB850;");
		optionsNewGame.setStyle("-fx-background-color: #BDB850;");
		optionsExit.setStyle("-fx-background-color: #BDB850;");
		
	}
	
	public Scene createStartScene() {
		BorderPane startBPane = new BorderPane();
		Image pic = new Image("c4.jpg");
		BackgroundImage bImg = new BackgroundImage(pic,
                BackgroundRepeat.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.DEFAULT,
                BackgroundSize.DEFAULT);
		Background bGround = new Background(bImg);
		
		startBPane.setBackground(bGround);		
		startBPane.setCenter(startButton);		
		
		return new Scene(startBPane,625,610);
	}
	
	public Scene createEndScene() {	
		Text winner;
		if (movesMade == 42) {
			winner = new Text("Its a tie!");
		}
		else
			winner = new Text("Player " + winnerNum + " wins!");
		
		winner.setStyle("-fx-font-size: 20pt;");
		HBox hbox = new HBox(winner);
		HBox hbox1 = new HBox(newGameButton);
		HBox hbox2 = new HBox(endProgramButton);
		hbox.setAlignment(Pos.CENTER);
		hbox1.setAlignment(Pos.CENTER);
		hbox2.setAlignment(Pos.CENTER);
		
		VBox vbox = new VBox(20, hbox, hbox1, hbox2);
		
		BorderPane endPane = new BorderPane(vbox);	
		
		endPane.setStyle("-fx-background-color: #0efeef;");		
		
		return new Scene(endPane,200,300);
	}
	
	public Scene createGameScene() {
		HBox holdGrid = new HBox(gameGrid);		
		HBox holdPicking = new HBox(playerPicking);
		holdPicking.setAlignment(Pos.CENTER);
		holdGrid.setAlignment(Pos.CENTER);
		playerPicking.setText("Player Picking: " + (playerTurn+1) + " (Red)");
		playerPicking.setStyle("-fx-font-size: 20;");
		playerPicking.setFill(Color.WHITE);
		VBox vbox = new VBox(20, gameMenu, displayPlayerTurn, holdGrid, holdPicking);		
		gamePane = new BorderPane(vbox);		
		return new Scene(gamePane, 700,700);
	}
	
	
	public void addGrid(GridPane grid) {
		
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++ ) {
				GameButton b1 = new GameButton(j,i, -1);
				if (j == 5) {
					b1.canBeClicked = true;
				} else {
					b1.canBeClicked = false;
				}				
				b1.setStyle("-fx-color: lightGray;");
				b1.setPrefSize(80,90);				
				b1.setOnAction(myHandler);
				grid.add(b1, i, j);
				buttonArray[j][i] = b1;				
			}
		}
	}
	
	
	public class GameButton extends Button {
		private int row;
		private int col;
		int player;       // 0 = player 1 | 1 = player2 | -1 = not set
		boolean canBeClicked;		
		
		GameButton(int r, int c, int p) {
			row = r;
			col = c;			
			player = p;
		}
		
		public int getRow(){
			return row;
		}
		public int getCol(){
			return col;
		}
	}
	

}
