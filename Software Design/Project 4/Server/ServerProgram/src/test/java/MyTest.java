import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.DisplayName;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

class MyTest {

	@Test
	void testCardClassConstructor() {
		Card c1 = new Card("Diamonds", 1);		
		assertEquals(c1.suite, "Diamonds", "Card Suite Incorrect for Diamonds");
		assertEquals(c1.value, 1, "Card Value Incorrect for Diamonds");
		
		Card c2 = new Card("Clubs", 2);		
		assertEquals(c2.suite, "Clubs", "Card Suite Incorrect for Clubs");
		assertEquals(c2.value, 2, "Card Value Incorrect for Clubs");
		
		Card c3 = new Card("Hearts", 3);		
		assertEquals(c3.suite, "Hearts", "Card Suite Incorrect for Hearts");
		assertEquals(c3.value, 3, "Card Value Incorrect for Hearts");
		
		Card c4 = new Card("Spades", 4);		
		assertEquals(c4.suite, "Spades", "Card Suite Incorrect for Spades");
		assertEquals(c4.value, 4, "Card Value Incorrect for Spades");		
	}
	
	@Test
	void testBaccaratDealerConstructor() {
		BaccaratDealer d = new BaccaratDealer();		
		assertNotNull(d.deck,"BaccaratDealer did not properly initialize deck.");
	}
	
	@Test
	void testBaccaratDealerGenerateDeck1() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();
		
		assertEquals(d.deck.get(0).value, 1, "BaccaratDealer GenerateDeck value incorrect for Diamond");
		assertEquals(d.deck.get(0).suite, "Diamonds", "BaccaratDealer GenerateDeck suite incorrect for Diamond");
		
		assertEquals(d.deck.get(13).value, 1, "BaccaratDealer GenerateDeck value incorrect for Clubs");
		assertEquals(d.deck.get(13).suite, "Clubs", "BaccaratDealer GenerateDeck suite incorrect for Clubs");
		
		assertEquals(d.deck.get(26).value, 1, "BaccaratDealer GenerateDeck value incorrect for Hearts");
		assertEquals(d.deck.get(26).suite, "Hearts", "BaccaratDealer GenerateDeck suite incorrect for Hearts");
		
		assertEquals(d.deck.get(39).value, 1, "BaccaratDealer GenerateDeck value incorrect for Spades");
		assertEquals(d.deck.get(39).suite, "Spades", "BaccaratDealer GenerateDeck suite incorrect for Spades");
	}
	
	@Test
	void testBaccaratDealerGenerateDeck2() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();
		
		assertEquals(d.deck.get(12).value, 13, "BaccaratDealer GenerateDeck value incorrect for Diamond");
		assertEquals(d.deck.get(12).suite, "Diamonds", "BaccaratDealer GenerateDeck suite incorrect for Diamond");
		
		assertEquals(d.deck.get(25).value, 13, "BaccaratDealer GenerateDeck value incorrect for Clubs");
		assertEquals(d.deck.get(25).suite, "Clubs", "BaccaratDealer GenerateDeck suite incorrect for Clubs");
		
		assertEquals(d.deck.get(38).value, 13, "BaccaratDealer GenerateDeck value incorrect for Hearts");
		assertEquals(d.deck.get(38).suite, "Hearts", "BaccaratDealer GenerateDeck suite incorrect for Hearts");
		
		assertEquals(d.deck.get(51).value, 13, "BaccaratDealer GenerateDeck value incorrect for Spades");
		assertEquals(d.deck.get(51).suite, "Spades", "BaccaratDealer GenerateDeck suiteincorrect for Spades");
	}

	
	@Test
	void testBaccaratDealerDealHand1() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();
		
		ArrayList<Card> hand = d.dealHand();
		
		assertEquals(hand.get(0).value, 1, "BaccaratDealer DealHand value incorrect for top card");
		assertEquals(hand.get(0).suite, "Diamonds", "BaccaratDealer suite DealHand incorrect for top card");
		
		assertEquals(hand.get(1).value, 2, "BaccaratDealer DealHand value incorrect for second card");
		assertEquals(hand.get(1).suite, "Diamonds", "BaccaratDealer suite DealHand incorrect for second card");
		
	}
	
	@Test
	void testBaccaratDealerDealHand2() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();			
		
		ArrayList<Card> hand = d.dealHand();		
		ArrayList<Card> hand2 = d.dealHand();
		
		assertEquals(hand2.get(0).value, 3, "BaccaratDealer DealHand value incorrect for top card");
		assertEquals(hand2.get(0).suite, "Diamonds", "BaccaratDealer suite DealHand incorrect for top card");
		
		assertEquals(hand2.get(1).value, 4, "BaccaratDealer DealHand value incorrect for second card");
		assertEquals(hand2.get(1).suite, "Diamonds", "BaccaratDealer suite DealHand incorrect for second card");
		
	}
	
	@Test
	void testBaccaratDealerDrawOne1() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();			
		
		Card c = d.drawOne();
		
		assertEquals(c.value, 1, "BaccaratDealer DrawOne value incorrect for top card");
		assertEquals(c.suite, "Diamonds", "BaccaratDealer DrawOne suite incorrect for top card");		
	}
	
	@Test
	void testBaccaratDealerDrawOne2() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();			
		
		Card c = d.drawOne();
		Card c2 = d.drawOne();
		
		assertEquals(c2.value, 2, "BaccaratDealer DrawOne incorrect for top card");
		assertEquals(c2.suite, "Diamonds", "BaccaratDealer DrawOne incorrect for top card");		
	}
	
	@Test
	void testBaccaratDealerShuffleCards1() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();			
		d.shuffleDeck();
		
		assertNotEquals(d.deck.get(0).value, 1, "BaccaratDealer ShuffleCard top card is the same. If top card is the same, re-run the test.");
		assertNotEquals(d.deck.get(0).suite, "Diamonds", "BaccaratDealer DealHand top card is the same. If top card is the same, re-run the test.");		
	}
	
	@Test
	void testBaccaratDealerShuffleCards2() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();			
		d.shuffleDeck();
		
		assertNotEquals(d.deck.get(51).value, 13, "BaccaratDealer ShuffleCard last card is the same. If last card is the same, re-run the test.");
		assertNotEquals(d.deck.get(51).suite, "Spades", "BaccaratDealer DealHand last card is the same. If last card is the same, re-run the test.");		
	}
	
	@Test
	void testBaccaratDealerDeckSize1() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();		
		
		ArrayList<Card> hand = d.dealHand();// -2
		hand = d.dealHand(); // -4
		
		assertEquals(d.deckSize(), 48, "BaccaratDealer DeckSize is incorrect.");			
	}
	
	@Test
	void testBaccaratDealerDeckSize2() {
		BaccaratDealer d = new BaccaratDealer();	
		d.generateDeck();			
		d.shuffleDeck();
		
		ArrayList<Card> hand = d.dealHand();// -2
		hand = d.dealHand(); // -4
		hand = d.dealHand(); // -6
		
		assertEquals(d.deckSize(), 46, "BaccaratDealer DeckSize is incorrect after shuffling.");		
	}
	
	@Test
	void testBaccaratGameLogicWhoWon1() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 5));
		hand1.add(new Card("Diamond", 4)); // 9 up to here (player)
		
		ArrayList<Card> hand2 = new ArrayList<Card>();
		hand2.add(new Card("Diamond", 1));
		hand2.add(new Card("Diamond", 9));
		hand2.add(new Card("Diamond", 3)); // 3 up to here (banker)
		
		assertEquals(BaccaratGameLogic.whoWon(hand1, hand2), "Player", "BaccaratGameLogic WhoWon wrong person winning");		
	}
	
	@Test
	void testBaccaratGameLogicWhoWon2() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 5));
		hand1.add(new Card("Diamond", 4)); // 9 up to here (player)
		
		ArrayList<Card> hand2 = new ArrayList<Card>();
		hand2.add(new Card("Diamond", 1));
		hand2.add(new Card("Diamond", 9));
		hand2.add(new Card("Diamond", 9)); // 9 up to here (banker)
		
		assertEquals(BaccaratGameLogic.whoWon(hand1, hand2), "Draw", "BaccaratGameLogic WhoWon wrong person winning");		
	}
	
	@Test
	void testBaccaratGameLogicWhoWon3() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 5)); // 5 up to here (player)
		
		ArrayList<Card> hand2 = new ArrayList<Card>();
		hand2.add(new Card("Diamond", 1));
		hand2.add(new Card("Diamond", 9));
		hand2.add(new Card("Diamond", 9)); // 9 up to here (banker)
		
		assertEquals(BaccaratGameLogic.whoWon(hand1, hand2), "Banker", "BaccaratGameLogic WhoWon wrong person winning");		
	}
	
	@Test
	void testBaccaratGameLogicWhoWon4() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 4)); // 5 up to here (player)
		
		ArrayList<Card> hand2 = new ArrayList<Card>();		
		hand2.add(new Card("Diamond", 9)); // 9 up to here (banker)
		
		assertEquals(BaccaratGameLogic.whoWon(hand1, hand2), "Banker", "BaccaratGameLogic WhoWon wrong person winning");		
	}
	
	@Test
	void testBaccaratGameLogicWhoWon5() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 5)); // 5 up to here (player)
		
		ArrayList<Card> hand2 = new ArrayList<Card>();	
		hand2.add(new Card("Diamond", 4)); // 4 up to here (banker)
		
		assertEquals(BaccaratGameLogic.whoWon(hand1, hand2), "Player", "BaccaratGameLogic WhoWon wrong person winning");		
	}
	
	@Test
	void testBaccaratGameLogicHandTotal1() {
		ArrayList<Card> hand1 = new ArrayList<Card>();		
		hand1.add(new Card("Diamond", 5));		
		
		assertEquals(BaccaratGameLogic.handTotal(hand1), 5, "BaccaratGameLogic HandTotal wrong value");		
	}
	
	@Test
	void testBaccaratGameLogicHandTotal2() {
		ArrayList<Card> hand1 = new ArrayList<Card>();	
		
		hand1.add(new Card("Diamond", 10));		
		assertEquals(BaccaratGameLogic.handTotal(hand1), 0, "BaccaratGameLogic HandTotal wrong value");		
		
		hand1.add(new Card("Diamond", 5));			
		assertEquals(BaccaratGameLogic.handTotal(hand1), 5, "BaccaratGameLogic HandTotal wrong value");	
		
		hand1.add(new Card("Diamond", 13));			
		assertEquals(BaccaratGameLogic.handTotal(hand1), 5, "BaccaratGameLogic HandTotal wrong value");	
	}
	
	@Test
	void testBaccaratGameLogicEvaluateBankerDraw1() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 7));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 3)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		
		hand1 = new ArrayList<Card>();		
		hand1.add(new Card("Diamond", 8));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 6)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 9));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 9)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
	}
	
	@Test
	void testBaccaratGameLogicEvaluateBankerDraw2() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 10));	
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 3)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		
		hand1 = new ArrayList<Card>();		
		hand1.add(new Card("Diamond", 1));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 6)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 2));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");	
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 9)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");		
	}
	
	@Test
	void testBaccaratGameLogicEvaluateBankerDraw3() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		
		hand1.add(new Card("Diamond", 3));	
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 7)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 8)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 9)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		
		hand1 = new ArrayList<Card>();		
		hand1.add(new Card("Diamond", 4));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 10)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 1)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 2)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 7)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 8)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 9)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 5));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");	
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 10)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");	
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 1)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 2)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 3)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 4)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 7)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 8)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 9)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 6));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,null), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");	
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 10)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 1)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 2)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 3)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 4)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 5)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 6)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 7)), true, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 8)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
		assertEquals(BaccaratGameLogic.evaluateBankerDraw(hand1,new Card("Diamond", 9)), false, "BaccaratGameLogic EvaluateBankerDraw incorrect");
	}
	
	@Test
	void testBaccaratGameLogicEvaluatePlayerDraw1() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		
		hand1.add(new Card("Diamond", 6));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), false, "BaccaratGameLogic EvaluatePlayerDraw incorrect");
		
		
		hand1 = new ArrayList<Card>();		
		hand1.add(new Card("Diamond", 7));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), false, "BaccaratGameLogic EvaluatePlayerDraw incorrect");
		
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 8));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), false, "BaccaratGameLogic EvaluatePlayerDraw incorrect");	
			
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 9));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), false, "BaccaratGameLogic EvaluatePlayerDraw incorrect");		
	}
	
	@Test
	void testBaccaratGameLogicEvaluatePlayerDraw2() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		
		hand1.add(new Card("Diamond", 5));	
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), true, "BaccaratGameLogic EvaluatePlayerDraw incorrect");
		
		
		hand1 = new ArrayList<Card>();		
		hand1.add(new Card("Diamond", 4));
		hand1.add(new Card("Diamond", 11));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), true, "BaccaratGameLogic EvaluatePlayerDraw incorrect");
		
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 3));
		hand1.add(new Card("Diamond", 12));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), true, "BaccaratGameLogic EvaluatePlayerDraw incorrect");	
			
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 2));
		hand1.add(new Card("Diamond", 13));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), true, "BaccaratGameLogic EvaluatePlayerDraw incorrect");	
		
		hand1 = new ArrayList<Card>();
		hand1.add(new Card("Diamond", 1));
		hand1.add(new Card("Diamond", 10));
		assertEquals(BaccaratGameLogic.evaluatePlayerDraw(hand1), true, "BaccaratGameLogic EvaluatePlayerDraw incorrect");	
	}
	
	@Test
	void testBaccaratGameConstructor() {
		BaccaratGame game = new BaccaratGame();
		
		assertNotNull(game.playerHand, "BaccaratGame playerHand is not initialized for some reason.");
		assertNotNull(game.bankerHand, "BaccaratGame bankerHand is not initialized for some reason.");
		assertNotNull(game.theDealer, "BaccaratGame theDealer is not initialized for some reason." );	
		
		assertEquals(game.currentBet, 0, "BaccaratGame currentBet is not initialized for some reason.");
		assertEquals(game.totalWinnings, 0, "BaccaratGame totalWinnings is not initialized for some reason.");		
		assertEquals(game.betOn, "", "BaccaratGame bettOn is not initialized for some reason.");		
	}
	
	@Test
	void testBaccaratGameEvaluateWinnings1() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		
		hand1.add(new Card("Diamond", 9));	
		hand1.add(new Card("Diamond", 10));
		
		ArrayList<Card> hand2 = new ArrayList<Card>();
		
		hand2.add(new Card("Diamond", 4));	
		hand2.add(new Card("Diamond", 10));
		
		BaccaratGame game = new BaccaratGame();
		
		game.betOn = "Player";
		game.playerHand = hand1;
		game.bankerHand = hand2;
		
		game.currentBet = 10;
		
		assertEquals(game.evaluateWinnings(), 10, "BaccaratGame wrong evaluate winnings value");		
	}
	
	@Test
	void testBaccaratGameEvaluateWinnings2() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		
		hand1.add(new Card("Diamond", 9));	
		hand1.add(new Card("Diamond", 10));
		
		ArrayList<Card> hand2 = new ArrayList<Card>();
		
		hand2.add(new Card("Diamond", 9));	
		hand2.add(new Card("Diamond", 10));
		
		BaccaratGame game = new BaccaratGame();
		
		game.betOn = "Draw";
		game.playerHand = hand1;
		game.bankerHand = hand2;		
		game.currentBet = 10;
		
		assertEquals(game.evaluateWinnings(), 80, "BaccaratGame wrong evaluate winnings value");		
	}
	
	@Test
	void testBaccaratGameEvaluateWinnings3() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		
		hand1.add(new Card("Diamond", 6));	
		hand1.add(new Card("Diamond", 10));
		
		ArrayList<Card> hand2 = new ArrayList<Card>();
		
		hand2.add(new Card("Diamond", 9));	
		hand2.add(new Card("Diamond", 10));
		
		BaccaratGame game = new BaccaratGame();
		
		game.betOn = "Banker";
		game.playerHand = hand1;
		game.bankerHand = hand2;		
		game.currentBet = 10;
		
		assertEquals(game.evaluateWinnings(), 10, "BaccaratGame wrong evaluate winnings value");		
	}
	
	@Test
	void testBaccaratGameEvaluateWinnings4() {
		ArrayList<Card> hand1 = new ArrayList<Card>();
		
		hand1.add(new Card("Diamond", 6));	
		hand1.add(new Card("Diamond", 10));
		
		ArrayList<Card> hand2 = new ArrayList<Card>();
		
		hand2.add(new Card("Diamond", 9));	
		hand2.add(new Card("Diamond", 10));
		
		BaccaratGame game = new BaccaratGame();
		
		game.betOn = "Player";
		game.playerHand = hand1;
		game.bankerHand = hand2;		
		game.currentBet = 10;
		
		assertEquals(game.evaluateWinnings(), -10, "BaccaratGame wrong evaluate winnings value");		
	}	
	
}
