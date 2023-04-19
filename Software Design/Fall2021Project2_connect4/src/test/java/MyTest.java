import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.DisplayName;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertEquals;

class MyTest {
	public boolean checkWinTest(int playerNum, int[][] turnArr) {
		// horizontal
		for (int c = 0; c < 4; c++) {
			for (int r = 0; r < 6; r++) {
				if (turnArr[r][c] == playerNum && turnArr[r][c+1] == playerNum && turnArr[r][c+2] == playerNum && turnArr[r][c+3] == playerNum ) {
					
					return true;
				}
			}
		}
		//vertical
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 7; c++) {
				if (turnArr[r][c] == playerNum && turnArr[r+1][c] == playerNum && turnArr[r+2][c] == playerNum && turnArr[r+3][c] == playerNum ) {
					
					return true;
				}
			}
		}
		//diagonal1
		for (int r = 3; r < 6; r++) {
			for (int c = 0; c < 4; c++) {
				if (turnArr[r][c] == playerNum && turnArr[r-1][c+1] == playerNum && turnArr[r-2][c+2] == playerNum && turnArr[r-3][c+3] == playerNum ) {
					
					return true;
				}
			}
		}		
		//diagonal2		
		for (int r = 3; r < 6; r++) {
			for (int c = 3; c < 7; c++) {
				if (turnArr[r][c] == playerNum && turnArr[r-1][c-1] == playerNum && turnArr[r-2][c-2] == playerNum && turnArr[r-3][c-3] == playerNum ) {
					System.out.println("We have a winner! " + playerNum);
					
					return true;
				}
			}
		}
		return false;
	}

	@Test
	void testHorizontalWin() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,1,1,1,1}
		};
		assertEquals(true, checkWinTest(1, arr), "Horizontal not working");
	}
	void testVerticalWin() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,1},
				{0,0,0,0,0,0,1},
				{0,0,0,0,0,0,1},
				{0,0,0,0,0,0,1}
		};
		assertEquals(true, checkWinTest(1, arr), "Horizontal not working");
	}
	void testDiagonal1Win() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,1,0,0,0},
				{0,0,1,0,0,0,0},
				{0,1,0,0,0,0,0},
				{1,0,0,0,0,0,0}
		};
		assertEquals(true, checkWinTest(1, arr), "Diagonal1 not working");
	}
	void testDiagonal2Win() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,1,0,0,0},
				{0,0,0,0,1,0,0},
				{0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1}
		};
		assertEquals(true, checkWinTest(1, arr), "Diagonal2 not working");
	}	
	

	void testNoWinHorizontal() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{1,1,1,0,0,0,0}
		};
		assertEquals(false, checkWinTest(1, arr), "Player is winning for no reason horizontally!");
	}
	
	void testNoWinVertical() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{1,0,0,0,0,0,0},
				{1,0,0,0,0,0,0},
				{1,0,0,0,0,0,0}
		};
		assertEquals(false, checkWinTest(1, arr), "Player is winning for no reason veritcally!");
	}
	
	void testNoWinDiagonal1() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,1,0,0,0,0},
				{0,1,0,0,0,0,0},
				{1,0,0,0,0,0,0}
		};
		assertEquals(false, checkWinTest(1, arr), "Player is winning for no reason (diagonal 1)!");
	}
	
	void testNoWinDiagonal2() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,1,0,0},
				{0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1}
		};
		assertEquals(false, checkWinTest(1, arr), "Player is winning for no reason (diagonal 2)!");
	}
	
	void testNoWinNoPiece() {
		int[][] arr = {
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,1,0,0},
				{0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1}
		};
		assertEquals(false, checkWinTest(1, arr), "Player is winning for no reason!");
	}
}
