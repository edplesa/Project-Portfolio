import java.util.ArrayList;

public class BaccaratGameLogic {
	
	public static String whoWon(ArrayList<Card> hand1, ArrayList<Card> hand2) {
		int playerHandTotal = handTotal(hand1);
		int bankerHandTotal = handTotal(hand2);	
		
		if ( playerHandTotal == 9 && bankerHandTotal != 9) {
			return "Player";
		} else if ( playerHandTotal == 8  && bankerHandTotal != 8) {
			if (bankerHandTotal == 9) {
				return "Banker";
			} else {
				return "Player";
			}
		} else if ( bankerHandTotal == 9 && playerHandTotal != 9) {
			return "Banker";
		} else if ( bankerHandTotal == 8  && playerHandTotal != 8) {
			if (bankerHandTotal == 9) {
				return "Player";
			} else {
				return "Banker";
			}
		} else if ( playerHandTotal == bankerHandTotal ) {
			return "Draw";
		} else if ( bankerHandTotal > playerHandTotal) {
			return "Banker";
		} else if ( playerHandTotal > bankerHandTotal) {
			return "Player";
		}
		
		return "Err";
	}
	
	public static int handTotal(ArrayList<Card> hand) {
		int handTotal = 0;
		
		for (Card card: hand) {
			if (card.value == 1) {
				handTotal += 1;
			} else if (card.value == 2) {
				handTotal += 2;
			} else if (card.value == 3) {
				handTotal += 3;
			} else if (card.value == 4) {
				handTotal += 4;
			} else if (card.value == 5) {
				handTotal += 5;
			} else if (card.value == 6) {
				handTotal += 6;
			} else if (card.value == 7) {
				handTotal += 7;
			} else if (card.value == 7) {
				handTotal += 7;
			} else if (card.value == 8) {
				handTotal += 8;
			} else if (card.value == 9) {
				handTotal += 9;
			} else if (card.value == 10) {
				handTotal += 0;
			} else if (card.value == 11) {
				handTotal += 0;
			} else if (card.value == 12) {
				handTotal += 0;
			} else if (card.value == 13) {
				handTotal += 0;
			}
		}
		
		if (handTotal > 9) {
			handTotal-=10;
		}
		
		return handTotal;
		
	}
	
	public static boolean evaluateBankerDraw(ArrayList<Card> hand, Card playerCard) {
		int bankerTotal = handTotal(hand);
		
		if (hand.size() != 2) {
			return false;
		}
		
		if (bankerTotal >= 7) {
			return false;
		} else if (bankerTotal == 0 || bankerTotal == 1 || bankerTotal == 2) {
			return true;
		} else if (bankerTotal == 3 || bankerTotal == 4 || bankerTotal == 5 || bankerTotal == 6) {
			
			// Player took no card
			if (playerCard == null) {				
				if (bankerTotal <= 5) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took Ace
			if (playerCard.value == 1) {				
				if (bankerTotal <= 3) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 2
			if (playerCard.value == 2) {				
				if (bankerTotal <= 4) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 3
			if (playerCard.value == 3) {				
				if (bankerTotal <= 4) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 4
			if (playerCard.value == 4) {				
				if (bankerTotal <= 5) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 5
			if (playerCard.value == 5) {				
				if (bankerTotal <= 5) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 6
			if (playerCard.value == 6) {				
				if (bankerTotal <= 6) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 7
			if (playerCard.value == 7) {				
				if (bankerTotal <= 6) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 8
			if (playerCard.value == 8) {				
				if (bankerTotal <= 2) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 9
			if (playerCard.value == 9) {				
				if (bankerTotal <= 3) {
					return true;
				} else {
					return false;
				}				
			}
			
			// Player took 10 or face cards
			if (playerCard.value == 10 || playerCard.value == 11 || playerCard.value == 12 || playerCard.value == 13) {				
				if (bankerTotal <= 3) {
					return true;
				} else {
					return false;
				}				
			}		
			
		}
		
		return false;
	}
	
	public static boolean evaluatePlayerDraw(ArrayList<Card> hand) {
		int playerTotal = handTotal(hand);
		
		if (hand.size() != 2) {
			return false;
		}
		
		if (playerTotal <= 5) {
			return true;
		}
		
		return false;
	}
	
	
}
