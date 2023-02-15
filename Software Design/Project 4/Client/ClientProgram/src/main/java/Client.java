import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.Socket;
import java.util.function.Consumer;



public class Client extends Thread{

	
	Socket socketClient;
	
	ObjectOutputStream out;
	ObjectInputStream in;
	
	String ipAddress;
	int portNum;
	
	BaccaratInfo info;
	
	private Consumer<Serializable> callback;
	
	Client(Consumer<Serializable> call, String ip, int port){
		
		callback = call;
		ipAddress = ip;
		portNum = port;
	}
	
	public void run() {
		
		try {
		socketClient= new Socket(ipAddress,portNum);
	    out = new ObjectOutputStream(socketClient.getOutputStream());
	    in = new ObjectInputStream(socketClient.getInputStream());
	    socketClient.setTcpNoDelay(true);
		}
		catch(Exception e) {}
		
		while(true) {
			 
			try {
			BaccaratInfo message = (BaccaratInfo)in.readObject();
			//callback.accept(message);
			//info = message;
			}
			catch(Exception e) {}
		}
	
    }
	
	public void send(BaccaratInfo data) {
		
		try {
			out.writeObject(data);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


}
