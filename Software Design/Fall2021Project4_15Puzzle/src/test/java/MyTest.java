import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.DisplayName;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

class MyTest {
	int[][] puzzles = {
						{2,6,10,3,1,4,7,11,8,5,9,15,12,13,14,0},//
						{2,6,10,3,1,4,7,11,8,5,9,15,12,13,0,14},//
						{2,6,10,3,1,4,7,11,8,5,9,15,0,13,14,12},//					
						{0,6,10,3,1,4,7,11,8,5,9,15,2,13,14,12},//
						{1,6,10,3,0,4,7,11,8,5,9,15,2,13,14,12},//
						{1,6,10,3,11,4,7,0,8,5,9,15,2,13,14,12},//
						{1,6,10,3,11,4,7,5,8,0,9,15,2,13,14,12},//
						{1,6,10,3,11,4,7,5,8,9,0,15,2,13,14,12},//
						{1,6,10,3,11,4,7,5,8,9,2,15,0,13,14,12},//
						{0,6,10,3,11,4,7,5,8,9,2,15,1,13,14,12} //
	                  };

	@Test
	void testPuzzle1() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[0]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 1 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[0]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 1 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle2() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[1]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 2 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[1]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 2 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle3() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[2]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 3 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[2]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 3 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle4() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[3]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 4 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[3]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 4 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle5() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[4]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 5 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[4]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 5 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle6() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[5]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 6 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[5]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 6 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle7() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[6]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 7 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[6]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 7 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle8() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[7]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 8 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[7]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 8 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle9() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[8]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 9 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[8]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 9 should have a solution for heuristicTwo");
	}
	@Test
	void testPuzzle10() {
		DB_Solver2 solver = new DB_Solver2(new Node(puzzles[9]),"heursiticOne");
		assertNotNull(solver.findSolutionPath(), "Puzzle 10 should have a solution for heuristicOne");
		
		solver = new DB_Solver2(new Node(puzzles[9]),"heursiticTwo");
		assertNotNull(solver.findSolutionPath(), "Puzzle 10 should have a solution for heuristicTwo");
	}

}
