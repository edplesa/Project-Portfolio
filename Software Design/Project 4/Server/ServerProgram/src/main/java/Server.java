import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.function.Consumer;

public class Server{

	int count = 1;	
	ArrayList<ClientThread> clients = new ArrayList<ClientThread>();
	TheServer server;
	private Consumer<Serializable> callback;
	int portNum;
	BaccaratGame game;
	
	
	Server(Consumer<Serializable> call, int port){
	
		callback = call;
		server = new TheServer();
		portNum = port;
		server.start();
	}
	
	
	public class TheServer extends Thread{
		
		public void run() {
		
			try(ServerSocket mysocket = new ServerSocket(portNum);){
				
		    System.out.println("Server is waiting for a client!");
		  
			
		    while(true) {
		
				ClientThread c = new ClientThread(mysocket.accept(), count);
				callback.accept("Player " + count + " connnected!");
				clients.add(c);
				c.start();
				
				count++;
				
			    }
			}//end of try
				catch(Exception e) {
					callback.accept("Server socket did not launch");
				}
			}//end of while
		}
	

		class ClientThread extends Thread{
			
		
			Socket connection;
			int count;
			ObjectInputStream in;
			ObjectOutputStream out;
			
			ClientThread(Socket s, int count){
				this.connection = s;
				this.count = count;	
			}
			
			public void updateClient(BaccaratInfo message) {
				
					ClientThread t = clients.get(count);
					
					try {
					 t.out.writeObject(message);
					}
					
					catch(Exception e) {}
				
			}
			
			public void run(){
					
				try {
					in = new ObjectInputStream(connection.getInputStream());
					out = new ObjectOutputStream(connection.getOutputStream());
					connection.setTcpNoDelay(true);	
					
					
					game = new BaccaratGame();
			    	game.theDealer.generateDeck();
			    	game.theDealer.shuffleDeck();
			    	
			    	
			    	System.out.println(game.theDealer.deckSize());
			    	
				}
				catch(Exception e) {
					System.out.println("Streams not open");
				}
				
				//updateClient("new client on server: client #"+count);
					
				 while(true) {
					    try {
					    	BaccaratInfo data = (BaccaratInfo)in.readObject();
					    	callback.accept("Player " + count + " bet " + data.currentBet + " on " + data.betOn);
					    	
					    	game.bankerHand = game.theDealer.dealHand();
					    	game.bankerHand = game.theDealer.dealHand();					    	
					    	
					    	int playerTotal = BaccaratGameLogic.handTotal(game.bankerHand);					    	
					    	int bankerTotal = BaccaratGameLogic.handTotal(game.bankerHand);	
					    	
					    	game.currentBet = data.currentBet;
					    	game.betOn = data.betOn;		
					    	
					    	double outCome;
					    	
					    	if (playerTotal == 8 || playerTotal == 9 || bankerTotal == 8 || bankerTotal == 9) {
					    		outCome = game.evaluateWinnings();
					    		data.moneyLeft += outCome;
					    	} else {
					    		Card playerDraw = null;
					    		
					    		if (BaccaratGameLogic.evaluatePlayerDraw(game.playerHand)) {
					    			playerDraw = game.theDealer.drawOne();
						    		game.playerHand.add(playerDraw);
						    	}
					    		
					    		if (BaccaratGameLogic.evaluateBankerDraw(game.bankerHand, playerDraw)) {
						    		game.bankerHand.add(game.theDealer.drawOne());
						    	}
					    		
					    		outCome = game.evaluateWinnings();
					    		data.moneyLeft += outCome;
					    	}
					    	
					    	
					    	
					    	
					    	callback.accept("Outcome of Player " + count + ": " + outCome + ". Money left is: " + data.moneyLeft);
					    	
					    	
					    	//updateClient(data);
					    	
					    	
					    	}
					    catch(Exception e) {
					    	callback.accept("Player " + count + " disconnected from the server!");
					    	//updateClient("Client #"+count+" has left the server!");
					    	clients.remove(this);	
					    	count--;
					    	System.out.println(count);
					    	break;
					    }
					}
				}//end of run
			
			
		}//end of client thread
}


	
	

	
