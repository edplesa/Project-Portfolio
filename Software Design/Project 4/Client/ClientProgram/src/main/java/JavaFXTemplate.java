import java.util.HashMap;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import javafx.util.Duration;
import javafx.animation.PauseTransition;

public class JavaFXTemplate extends Application {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}
	
	TextField ipAddress;
	TextField portNum;
	
	Button joinButton;
	
	Client clientConnection;
	ListView<String> gameInfo;
	
	HashMap<String, Scene> sceneMap;
	
	Button player;
	Button banker;
	Button draw;
	Button placeBet;
	
	TextField betArea;
	
	double totalPlayerWinnings;
	String betOnWho;	
	
	BaccaratInfo info;
	
	
	PauseTransition pause = new PauseTransition(Duration.seconds(3));

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Join Server");
		
		
		
		joinButton = new Button("Join");
		joinButton.setPrefSize(100,60);
		gameInfo = new ListView<>();
		gameInfo.setPrefSize(500,200);
		
		joinButton.setOnAction(e-> {primaryStage.setScene(sceneMap.get("clientInfoScene"));
			primaryStage.setTitle("Player Info");
				clientConnection = new Client(data->{
					Platform.runLater(()->{gameInfo.getItems().add(data.toString());
					});
				},ipAddress.getText(), Integer.parseInt(portNum.getText()));
				info = new BaccaratInfo("", 0);
				clientConnection.info = info;

				clientConnection.start();
		});
		
		
		
		player = new Button("Bet on Player");
		banker = new Button("Bet on Banker");
		draw = new Button("Bet on Draw");
		placeBet = new Button("Place Bet");
		placeBet.setPrefSize(100,100);
		placeBet.setStyle("-fx-font-size: 14px;");
		
		player.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				betOnWho = "Player";
				player.setDisable(true);
				banker.setDisable(false);
				draw.setDisable(false);
			}
		});
		
		banker.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				betOnWho = "Banker";
				player.setDisable(false);
				banker.setDisable(true);
				draw.setDisable(false);
			}
		});
		
		draw.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				betOnWho = "Draw";
				player.setDisable(false);
				banker.setDisable(false);
				draw.setDisable(true);
			}
		});
		
		placeBet.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				info.betOn = betOnWho;
				info.currentBet = Integer.parseInt(betArea.getText());
				
				clientConnection.send(info); 
				betArea.clear();
				player.setDisable(false);
				banker.setDisable(false);
				draw.setDisable(false);				
			}
		});
		betArea = new TextField();
		
		ipAddress = new TextField();
		portNum = new TextField();
		
		sceneMap = new HashMap<String, Scene>();
		
		sceneMap.put("joinScene",  createJoinScene());
		
		sceneMap.put("clientInfoScene",  createClientInfo());
		
		
		
		primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent t) {
                Platform.exit();
                System.exit(0);
            }
        });
		
		
		primaryStage.setScene(sceneMap.get("joinScene"));
		primaryStage.show();
	}
	
	public Scene createJoinScene() {
		BorderPane startBPane = new BorderPane();
		
		startBPane.setLeft(new VBox(20, new HBox(5, new Label("Enter Server Address: "), ipAddress), new HBox(20, new Label("Enter Server Port: "), portNum)));
		startBPane.setRight(joinButton);
		
		return new Scene(startBPane,400,80);
	}
	
	public Scene createClientInfo() {
		BorderPane startBPane = new BorderPane();
		
		startBPane.setStyle("-fx-background-color: #35654d;");
		
		HBox holdPick = new HBox(20,player, banker, draw);		
		holdPick.setAlignment(Pos.CENTER);
		
		
		
		HBox holdPlaceBet = new HBox(placeBet);		
		holdPlaceBet.setAlignment(Pos.CENTER);		
		
		HBox holdGameInfo = new HBox(gameInfo);		
		holdGameInfo.setAlignment(Pos.CENTER);	
		
		Label betInfo = new Label("Enter bet here: ");
		betInfo.setStyle("-fx-text-fill: white;"+"-fx-font-size: 14px;");
		
		HBox holdBetArea = new HBox(betInfo,betArea);		
		holdBetArea.setAlignment(Pos.CENTER);
		
		startBPane.setCenter(new VBox(20, holdGameInfo, holdBetArea, holdPick, holdPlaceBet));
		
		return new Scene(startBPane,700,700);
	}

}
