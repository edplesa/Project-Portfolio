import java.util.HashMap;


import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundImage;
import javafx.scene.layout.BackgroundPosition;
import javafx.scene.layout.BackgroundRepeat;
import javafx.scene.layout.BackgroundSize;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import javafx.scene.control.ListView;

public class JavaFXTemplate extends Application {
	Button startServerButton;
	HashMap<String, Scene> sceneMap;
	TextField portNum;
	EventHandler<ActionEvent> myHandler;
	
	ListView<String> serverLog;
	
	Server serverConnection;
	
	Label playersConnected;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Start Server");		
		
		
		serverLog = new ListView<>();
		serverLog.setMaxHeight(250);
		portNum = new TextField();			
		playersConnected = new Label();
		
		startServerButton = new Button("Start Server");
		startServerButton.setOnAction(e->{ primaryStage.setScene(sceneMap.get("serverInfoScene"));
										   primaryStage.setTitle("Baccarat Server");
				serverConnection = new Server(data -> {
					Platform.runLater(()->{
						serverLog.getItems().add(data.toString());
						playersConnected.setText("Players Connected: " + (serverConnection.count-1));
				   	});
					
				}, Integer.parseInt(portNum.getText()));
				
		});
		
		//startServerButton.setStyle("-fx-color: lightGray;");
		startServerButton.setPrefSize(100,60);
		
		sceneMap = new HashMap<String, Scene>();
		
		sceneMap.put("startScene",  createStartScene());
		sceneMap.put("serverInfoScene",  createServerInfo());
		
		primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent t) {
                Platform.exit();
                System.exit(0);
            }
        });
		
		
		
		 
		
		primaryStage.setScene(sceneMap.get("startScene"));
		primaryStage.show();
	}
	
	
	public Scene createStartScene() {
		BorderPane startBPane = new BorderPane();	
		
		
		Label enterPortMSG = new Label("Enter Server Port");		
		
		
		HBox holdPort = new HBox(enterPortMSG);
		holdPort.setAlignment(Pos.CENTER);
		
		HBox holdText = new HBox(portNum);
		holdText.setAlignment(Pos.CENTER);
		
		HBox holdButton = new HBox(startServerButton);
		holdButton.setAlignment(Pos.CENTER);			
		
		
		startBPane.setCenter(new VBox(20, holdPort, holdText, holdButton));
		
		return new Scene(startBPane,200,150);
	}

	public Scene createServerInfo() {
		BorderPane startBPane = new BorderPane();
		
		startBPane.setTop(playersConnected);
		
		startBPane.setBottom(serverLog);
		
		return new Scene(startBPane,700,700);
	}
}
