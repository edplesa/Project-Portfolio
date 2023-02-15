import java.util.ArrayList;
import java.util.Collections;

public class BaccaratDealer {
	ArrayList<Card> deck;
	
	BaccaratDealer() {
		deck = new ArrayList<Card>();
	}
	
	public void generateDeck() {
		for (int i = 1; i <= 13; i++) {
			Card c = new Card("Diamonds", i);
			deck.add(c);
		}
		
		for (int i = 1; i <= 13; i++) {
			Card c = new Card("Clubs", i);
			deck.add(c);
		}
		
		for (int i = 1; i <= 13; i++) {
			Card c = new Card("Hearts", i);
			deck.add(c);
		}
		
		for (int i = 1; i <= 13; i++) {
			Card c = new Card("Spades", i);
			deck.add(c);
		}
	}
	
	public ArrayList<Card> dealHand() {
		ArrayList<Card> hand = new ArrayList<Card>();
		
		Card c1 = deck.get(0);
		deck.remove(0);
		hand.add(c1);
		
		Card c2 = deck.get(0);
		deck.remove(0);
		hand.add(c2);
		
		return hand;		
	}
	
	public Card drawOne() {
		Card c = deck.get(0);
		deck.remove(0);
		return c;
	}
	
	public void shuffleDeck() {
		Collections.shuffle(deck);
	}
	
	public int deckSize() {
		return deck.size();
	}
	
	
}
