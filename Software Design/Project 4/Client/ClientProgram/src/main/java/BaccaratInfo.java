import java.io.Serializable;

public class BaccaratInfo implements Serializable{
	
	private static final long serialVersionUID = 1L;
	
	String betOn;
	
	double currentBet;
	
	double moneyLeft = 1000;
	
	BaccaratInfo(String betOn, double currentBet) {
		this.betOn = betOn;
		this.currentBet = currentBet;	
	}

}
