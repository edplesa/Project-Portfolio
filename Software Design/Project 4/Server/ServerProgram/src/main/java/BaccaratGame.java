import java.util.ArrayList;

public class BaccaratGame {
	ArrayList<Card> playerHand;
	ArrayList<Card> bankerHand;
	BaccaratDealer theDealer;
	double currentBet;
	double totalWinnings;
	
	String betOn;
	
	BaccaratGame() {
		playerHand = new ArrayList<>();
		bankerHand = new ArrayList<>();		
		theDealer = new BaccaratDealer();
		currentBet = 0;
		totalWinnings = 0;
		betOn = "";
	}
	
	public double evaluateWinnings() {	
		
		String roundWinner = BaccaratGameLogic.whoWon(playerHand, bankerHand);
		
		if (betOn == roundWinner && roundWinner == "Banker") {
			totalWinnings+=currentBet;
			return currentBet;
		} else if (betOn == roundWinner && roundWinner == "Player") {
			totalWinnings+=currentBet;
			return currentBet;
		} else if (betOn == roundWinner && roundWinner == "Draw") {
			totalWinnings+=currentBet*8;
			return currentBet*8;
		} else {
			totalWinnings+=currentBet*(-1);
			return currentBet*(-1);
		}
	}
	
}
