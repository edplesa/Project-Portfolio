import java.util.ArrayList;
import java.util.HashMap;
import java.util.Stack;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

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
 * Project 4: 15 Puzzle 
 * 
 * Partner: None
 */

public class JavaFXTemplate extends Application {
	int[][] puzzles = {
						{2,6,10,3,1,4,7,11,8,5,9,15,12,13,14,0},
						{2,6,10,3,1,4,7,11,8,5,9,15,12,13,0,14},
						{2,6,10,3,1,4,7,11,8,5,9,15,0,13,14,12},					
						{0,6,10,3,1,4,7,11,8,5,9,15,2,13,14,12},
						{1,6,10,3,0,4,7,11,8,5,9,15,2,13,14,12},
						{1,6,10,3,11,4,7,0,8,5,9,15,2,13,14,12},
						{1,6,10,3,11,4,7,5,8,0,9,15,2,13,14,12},
						{1,6,10,3,11,4,7,5,8,9,0,15,2,13,14,12},
						{1,6,10,3,11,4,7,5,8,9,2,15,0,13,14,12},
						{0,6,10,3,11,4,7,5,8,9,2,15,1,13,14,12}
                      };
	int puzzleNum = 0;
	EventHandler<ActionEvent> myHandler;
	Button startButton;
	Button endProgramButton;
	Button newGameButton;
	HashMap<String, Scene> sceneMap; 
	MenuBar gameMenu;
	GridPane gameGrid;
	
	PauseTransition pause = new PauseTransition(Duration.seconds(3));	
	
	
	
	GameButton buttonArray[][];
	
	BorderPane gamePane;
	Menu solver;
	
	Menu optionsMenu;
	
	MenuItem solver1;
	MenuItem solver2;
	MenuItem showSol;
	
	
	
	MenuItem optionsHowTo;
	MenuItem optionsNewGame;
	MenuItem optionsExit;
	
	String heuristic = "";
	
	ArrayList<Node> solutionPath = null;
	Node currentBoard = null;
	
	int pathCounter = 0;
	int pathSize=0;
	
		

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Awesome 15 Puzzle!");
		
		myHandler = new EventHandler<ActionEvent>() {
			
			public void handle(ActionEvent e) {
				
				GameButton b1 = (GameButton)e.getSource();
				
				if (checkValidMove(b1) ) {
					if (checkWin()) {
						for (int i = 0; i < 4; i++) {
							for (int j = 0; j < 4; j++ ) {
								buttonArray[j][i].setDisable(true);				
							}
						}
						pause.setOnFinished(r->primaryStage.setScene(createEndScene()));
						pause.play();
					}
					
				}				
							
			}			
		};
		
		
	
		
		// Setup startScene
		sceneMap = new HashMap<String,Scene>();
		

		pause.setOnFinished(e -> primaryStage.setScene(sceneMap.get("gameScene")));
		pause.play();
		
		endProgramButton =  new Button("Exit");
		newGameButton = new Button("New Puzzle");
		endProgramButton.setPrefSize(140,100);
		newGameButton.setPrefSize(140,100);
		endProgramButton.setStyle("-fx-font-size:20");
		newGameButton.setStyle("-fx-font-size:20");
		endProgramButton.setOnAction(e->primaryStage.close());
		
		
		
		newGameButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				Scene newgame = reinitBoard();
				primaryStage.setScene(newgame);
				primaryStage.show();							
			}
		});
		
		
		
		// Setup gameScene
		
			// set up Menu Bar
		gameMenu = new MenuBar();
		
		solver = new Menu("Solver");
		
		optionsMenu = new Menu("Options");
		
		solver1 = new MenuItem("AI H1");	
		solver2 = new MenuItem("AI H2");
		showSol = new MenuItem("Solution");
		
		

		
		
		optionsHowTo = new MenuItem("How to Play");
		optionsNewGame = new MenuItem("New Puzzle");
		optionsExit = new MenuItem("Exit");
		
		optionsExit.setOnAction(e->primaryStage.close());
		
		optionsHowTo.setOnAction(new EventHandler<ActionEvent>() {
			
			@Override
			public void handle(ActionEvent event) {
				openHowTo();
			}
		});		

		solver.getItems().addAll(solver1,solver2,showSol);		
		
		showSol.setDisable(true);
		
		optionsMenu.getItems().addAll(optionsHowTo,optionsNewGame,optionsExit);	
		
		gameMenu.getMenus().addAll(solver, optionsMenu);
		
		
		
			// set up game grid
		buttonArray = new GameButton[4][4];
		gameGrid = new GridPane();
		gameGrid.setHgap(5);
		gameGrid.setVgap(5);
		addGrid(gameGrid);		
		//printGrid();

		//
		solver1.setOnAction(new EventHandler<ActionEvent>() {
			
			@Override
			public void handle(ActionEvent event) {		
				
				heuristic = "heuristicOne";
				currentBoard = getBoardAsNode();
				
//				future = ex.submit(new MySolver(currentBoard,heuristic));
//				try {
//					solutionPath = future.get();
//				} catch (InterruptedException | ExecutionException e) {					
//					e.printStackTrace();
//				}
//				pathSize = solutionPath.size();
				
				ExecutorService ex = Executors.newFixedThreadPool(1);
				ex.submit(()-> {
					ExecutorService ex2 = Executors.newFixedThreadPool(1);
					Future<ArrayList<Node>>future = ex2.submit(new MySolver(currentBoard,heuristic));
					try {
						solutionPath = future.get();
						pathSize = solutionPath.size();
					} catch (InterruptedException | ExecutionException e) {
						e.printStackTrace();
					}
					ex2.shutdown();
				});
				ex.shutdown();
				showSol.setDisable(false);
			}
			
		});
		solver2.setOnAction(new EventHandler<ActionEvent>() {

			@Override
			public void handle(ActionEvent event) {	
				
				heuristic = "heuristicTwo";
				currentBoard = getBoardAsNode();
				
//				future = ex.submit(new MySolver(currentBoard,heuristic));
//				try {
//					solutionPath = future.get();
//				} catch (InterruptedException | ExecutionException e) {					
//					e.printStackTrace();
//				}
				
				ExecutorService ex = Executors.newFixedThreadPool(1);
				ex.submit(()-> {
					ExecutorService ex2 = Executors.newFixedThreadPool(1);
					Future<ArrayList<Node>>future = ex2.submit(new MySolver(currentBoard,heuristic));
					try {
						solutionPath = future.get();
						pathSize = solutionPath.size();
					} catch (InterruptedException | ExecutionException e) {
						e.printStackTrace();
					}
					ex2.shutdown();
				});
				
				ex.shutdown();
				showSol.setDisable(false);
				
			}
		});
		showSol.setOnAction(new EventHandler<ActionEvent>() {

			@Override
			public void handle(ActionEvent event) {				
				
				if (pathSize > 10) {
					
					
					for (int i = 0; i < 10; i++) {						
						
						PauseTransition movesPause = new PauseTransition(Duration.seconds(i));	
						
						movesPause.setOnFinished(f-> {
							updateBoard(solutionPath.get(pathCounter));
							pathCounter++;
							pathSize--;
						});
						
						movesPause.play();
					}
					
				}
				else {					
					for (int x = 0; x < pathSize; x++) {
						PauseTransition movesPause = new PauseTransition(Duration.seconds(x));	
						
						movesPause.setOnFinished(f-> {						
							updateBoard(solutionPath.get(pathCounter));
							pathCounter++;
							if (checkWin()) {
								for (int i = 0; i < 4; i++) {
									for (int j = 0; j < 4; j++ ) {
										buttonArray[j][i].setDisable(true);				
									}
								}
								pause.setOnFinished(r->primaryStage.setScene(createEndScene()));
								pause.play();
							}
						});	
						
						movesPause.play();
						
					}					
					
					
				}	
				
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
		
		
		
		primaryStage.setScene(sceneMap.get("startScene"));
		primaryStage.show();
	}
	
	public void updateBoard(Node node) {
		int[] puzzleArray = node.getKey();
		//row 1
		buttonArray[0][0].num = puzzleArray[0]; buttonArray[1][0].num = puzzleArray[1]; buttonArray[2][0].num = puzzleArray[2]; buttonArray[3][0].num = puzzleArray[3];
		
		buttonArray[0][0].setText(Integer.toString(puzzleArray[0])); buttonArray[1][0].setText(Integer.toString(puzzleArray[1])); 
		buttonArray[2][0].setText(Integer.toString(puzzleArray[2])); buttonArray[3][0].setText(Integer.toString(puzzleArray[3]));
		
		
		//row 2
	    buttonArray[0][1].num = puzzleArray[4]; buttonArray[1][1].num = puzzleArray[5]; buttonArray[2][1].num = puzzleArray[6]; buttonArray[3][1].num = puzzleArray[7];
	    
	    buttonArray[0][1].setText(Integer.toString(puzzleArray[4])); buttonArray[1][1].setText(Integer.toString(puzzleArray[5])); 
	    buttonArray[2][1].setText(Integer.toString(puzzleArray[6])); buttonArray[3][1].setText(Integer.toString(puzzleArray[7]));
	    
	    
	    //row 3
	    buttonArray[0][2].num = puzzleArray[8]; buttonArray[1][2].num = puzzleArray[9]; buttonArray[2][2].num = puzzleArray[10]; buttonArray[3][2].num = puzzleArray[11];
	    
	    buttonArray[0][2].setText(Integer.toString(puzzleArray[8])); buttonArray[1][2].setText(Integer.toString(puzzleArray[9])); 
	    buttonArray[2][2].setText(Integer.toString(puzzleArray[10])); buttonArray[3][2].setText(Integer.toString(puzzleArray[11]));
	    
	    
	    //row 4
	    buttonArray[0][3].num = puzzleArray[12]; buttonArray[1][3].num = puzzleArray[13]; buttonArray[2][3].num = puzzleArray[14]; buttonArray[3][3].num = puzzleArray[15];
	    
	    buttonArray[0][3].setText(Integer.toString(puzzleArray[12])); buttonArray[1][3].setText(Integer.toString(puzzleArray[13])); 
	    buttonArray[2][3].setText(Integer.toString(puzzleArray[14])); buttonArray[3][3].setText(Integer.toString(puzzleArray[15]));
	    
	    updateZero();
	}
	
	public void updateZero() {
		for (GameButton[] row : buttonArray) {
			for (GameButton b : row) {
				if (b.num == 0) {
					b.setText("");
					break;
				}
			}
		}
	}
	
	public boolean checkWin() {
		if ( buttonArray[0][0].num == 0 && buttonArray[1][0].num == 1 && buttonArray[2][0].num == 2 && buttonArray[3][0].num == 3 &&
		     buttonArray[0][1].num == 4 && buttonArray[1][1].num == 5 && buttonArray[2][1].num == 6 && buttonArray[3][1].num == 7 &&
		     buttonArray[0][2].num == 8 && buttonArray[1][2].num == 9 && buttonArray[2][2].num == 10 && buttonArray[3][2].num == 11 &&
		     buttonArray[0][3].num == 12 && buttonArray[1][3].num == 13 && buttonArray[2][3].num == 14 && buttonArray[3][3].num == 15 ) {
			return true;
		}
		
		
		
		return false;
	}
	
	
	public boolean checkValidMove(GameButton b) {
		if ( b.row+1 < 4 && buttonArray[b.row + 1][b.col].num == 0 ) {
			buttonArray[b.row + 1][b.col].num = b.num;
			b.num = 0;
			
			b.setText("");
			buttonArray[b.row + 1][b.col].setText(Integer.toString(buttonArray[b.row + 1][b.col].num));
			return true;
		} else if ( b.row-1 > -1 && buttonArray[b.row - 1][b.col].num == 0 ) {
			buttonArray[b.row - 1][b.col].num = b.num;
			b.num = 0;
			
			b.setText("");
			buttonArray[b.row - 1][b.col].setText(Integer.toString(buttonArray[b.row - 1][b.col].num));
			return true;
		} else if ( b.col+1 < 4 && buttonArray[b.row][b.col + 1].num == 0 ) {
			buttonArray[b.row][b.col + 1].num = b.num;
			b.num = 0;
			
			b.setText("");
			buttonArray[b.row][b.col + 1].setText(Integer.toString(buttonArray[b.row][b.col + 1].num));
			return true;
		} else if ( b.col-1 > -1 && buttonArray[b.row][b.col - 1].num == 0 ) {
			buttonArray[b.row][b.col - 1].num = b.num;
			b.num = 0;
			
			b.setText("");
			buttonArray[b.row][b.col - 1].setText(Integer.toString(buttonArray[b.row][b.col - 1].num));
			return true;
		}
		return false;
	}
	
	public void openHowTo() {
		Label secondLabel = new Label("Simply click on a piece to move it to the empty spot. \nIf you get all the pieces in numeric order with \nthe empty spot in the top left, you win!");

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
		
		if (puzzleNum == 9) {
			puzzleNum = 0;
		} else {
			puzzleNum++;
		}
		pathCounter = 0;
		pathSize = 0;
		
		showSol.setDisable(true);
		
		gameGrid = new GridPane();
		gameGrid.setHgap(5);
		gameGrid.setVgap(5);
		addGrid(gameGrid);	
		
		
		
		HBox holdGrid = new HBox(gameGrid);				
		holdGrid.setAlignment(Pos.CENTER);
		
		VBox vbox = new VBox(20, gameMenu, holdGrid);			
		gamePane = new BorderPane(vbox);	
		
		Scene newgame = new Scene(gamePane, 600,450);
		return newgame;
	}
	
	
	
	
	
	public Scene createStartScene() {
		BorderPane startBPane = new BorderPane();
		Image pic = new Image("15puzzlepic.jpg");
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
		
		HBox hbox = new HBox();
		HBox hbox1 = new HBox(newGameButton);
		HBox hbox2 = new HBox(endProgramButton);
		hbox.setAlignment(Pos.CENTER);
		hbox1.setAlignment(Pos.CENTER);
		hbox2.setAlignment(Pos.CENTER);
		
		VBox vbox = new VBox(20, hbox, hbox1, hbox2);
		
		BorderPane endPane = new BorderPane(vbox);		
		
		return new Scene(endPane,200,300);
	}
	
	public Scene createGameScene() {
		HBox holdGrid = new HBox(gameGrid);		
		holdGrid.setAlignment(Pos.CENTER);		
		VBox vbox = new VBox(20, gameMenu, holdGrid);		
		gamePane = new BorderPane(vbox);		
		return new Scene(gamePane, 600,450);
	}
	
	
	public void addGrid(GridPane grid) {		
		int count = 0;
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++ ) {
				GameButton b1 = new GameButton(x,y,puzzles[puzzleNum][count]);
				if (puzzles[puzzleNum][count] != 0) {
					b1.setText(Integer.toString(puzzles[puzzleNum][count]));										
				}
				
				b1.setStyle("-fx-color: lightGray;");
				b1.setOnAction(myHandler);
				b1.setPrefSize(80,90);				
				b1.setOnAction(myHandler);
				grid.add(b1, x, y);
				buttonArray[x][y] = b1;	
				count++;
			}
		}
	}
	
	public void printGrid() {
		
		System.out.println(buttonArray[0][0].num + " " + buttonArray[1][0].num + " " + buttonArray[2][0].num + " " + buttonArray[3][0].num);
		System.out.println(buttonArray[0][1].num + " " + buttonArray[1][1].num + " " + buttonArray[2][1].num + " " + buttonArray[3][1].num);
		System.out.println(buttonArray[0][2].num + " " + buttonArray[1][2].num + " " + buttonArray[2][2].num + " " + buttonArray[3][2].num);
		System.out.println(buttonArray[0][3].num + " " + buttonArray[1][3].num + " " + buttonArray[2][3].num + " " + buttonArray[3][3].num);
		
	}
	
	public Node getBoardAsNode() {
		int board[] = {buttonArray[0][0].num , buttonArray[1][0].num , buttonArray[2][0].num,buttonArray[3][0].num,
				       buttonArray[0][1].num , buttonArray[1][1].num , buttonArray[2][1].num , buttonArray[3][1].num,
				       buttonArray[0][2].num , buttonArray[1][2].num , buttonArray[2][2].num , buttonArray[3][2].num,
				       buttonArray[0][3].num , buttonArray[1][3].num , buttonArray[2][3].num , buttonArray[3][3].num}; 
		return new Node(board);
	}
	
	
	public class GameButton extends Button {
		private int row;
		private int col;
		int num;		
		
		GameButton(int r, int c, int n) {
			row = r;
			col = c;			
			num = n;
			
		}
		
		public int getRow(){
			return row;
		}
		public int getCol(){
			return col;
		}
	}
	

}
