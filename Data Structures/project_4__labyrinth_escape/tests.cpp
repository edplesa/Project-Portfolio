#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"


TEST(grid, defaultConstructor) {
    Grid<int> Grid1;
    ASSERT_EQ(Grid1.numrows(), 4);
    ASSERT_EQ(Grid1.numcols(0), 4);
    ASSERT_EQ(Grid1.numcols(1), 4);
    ASSERT_EQ(Grid1.numcols(2), 4);
    ASSERT_EQ(Grid1.numcols(3), 4);
    ASSERT_EQ(Grid1.size(), 16);
    
    Grid<char> Grid2;
    ASSERT_EQ(Grid1.numrows(), 4);
    ASSERT_EQ(Grid1.numcols(0), 4);
    ASSERT_EQ(Grid1.numcols(1), 4);
    ASSERT_EQ(Grid1.numcols(2), 4);
    ASSERT_EQ(Grid1.numcols(3), 4);
    ASSERT_EQ(Grid1.size(), 16);
    
    Grid<string> Grid3;
    ASSERT_EQ(Grid3.numrows(), 4);
    ASSERT_EQ(Grid3.numcols(0), 4);
    ASSERT_EQ(Grid3.numcols(1), 4);
    ASSERT_EQ(Grid3.numcols(2), 4);
    ASSERT_EQ(Grid3.numcols(3), 4);
    ASSERT_EQ(Grid3.size(), 16);
    
    Grid<float> Grid4;
    ASSERT_EQ(Grid4.numrows(), 4);
    ASSERT_EQ(Grid4.numcols(0), 4);
    ASSERT_EQ(Grid4.numcols(1), 4);
    ASSERT_EQ(Grid4.numcols(2), 4);
    ASSERT_EQ(Grid4.numcols(3), 4);
    ASSERT_EQ(Grid4.size(), 16);
    
    Grid<double> Grid5;
    ASSERT_EQ(Grid5.numrows(), 4);
    ASSERT_EQ(Grid5.numcols(0), 4);
    ASSERT_EQ(Grid5.numcols(1), 4);
    ASSERT_EQ(Grid5.numcols(2), 4);
    ASSERT_EQ(Grid5.numcols(3), 4);
    ASSERT_EQ(Grid5.size(), 16);
    
}


TEST(grid, paramConstructor) {
    Grid<int> Grid1(5,6);
    ASSERT_EQ(Grid1.numrows(), 5);
    ASSERT_EQ(Grid1.numcols(0), 6);
    ASSERT_EQ(Grid1.numcols(1), 6);
    ASSERT_EQ(Grid1.numcols(2), 6);
    ASSERT_EQ(Grid1.numcols(3), 6);
    ASSERT_EQ(Grid1.numcols(4), 6);
    ASSERT_EQ(Grid1.size(), 30);
    
    Grid<char> Grid2(3,6);
    ASSERT_EQ(Grid2.numrows(), 3);
    ASSERT_EQ(Grid2.numcols(0), 6);
    ASSERT_EQ(Grid2.numcols(1), 6);
    ASSERT_EQ(Grid2.numcols(2), 6);
    ASSERT_EQ(Grid2.size(), 18);
    
    Grid<string> Grid3(2,1);
    ASSERT_EQ(Grid3.numrows(), 2);
    ASSERT_EQ(Grid3.numcols(0), 1);
    ASSERT_EQ(Grid3.numcols(1), 1);
    ASSERT_EQ(Grid3.size(), 2);
    
    Grid<float> Grid4(1,1);
    ASSERT_EQ(Grid4.numrows(), 1);
    ASSERT_EQ(Grid4.numcols(0), 1);
    ASSERT_EQ(Grid4.size(), 1);
    
    Grid<double> Grid5(3,7);
    ASSERT_EQ(Grid5.numrows(), 3);
    ASSERT_EQ(Grid5.numcols(0), 7);
    ASSERT_EQ(Grid5.numcols(1), 7);
    ASSERT_EQ(Grid5.numcols(2), 7);
    ASSERT_EQ(Grid5.size(), 21);
}


TEST(grid, copyConstructor) {
    Grid<int> Grid1(5,6);
    Grid<int> Grid2(Grid1);
    ASSERT_EQ(Grid2.numrows(), 5);
    ASSERT_EQ(Grid2.numcols(0), 6);
    ASSERT_EQ(Grid2.numcols(1), 6);
    ASSERT_EQ(Grid2.numcols(2), 6);
    ASSERT_EQ(Grid2.numcols(3), 6);
    ASSERT_EQ(Grid2.numcols(4), 6);
    ASSERT_EQ(Grid2.size(), 30);
    
    Grid<string> Grid3(5,6);
    Grid<string> Grid4(Grid3);
    ASSERT_EQ(Grid4.numrows(), 5);
    ASSERT_EQ(Grid4.numcols(0), 6);
    ASSERT_EQ(Grid4.numcols(1), 6);
    ASSERT_EQ(Grid4.numcols(2), 6);
    ASSERT_EQ(Grid4.numcols(3), 6);
    ASSERT_EQ(Grid4.numcols(4), 6);
    ASSERT_EQ(Grid4.size(), 30);
    
    Grid<char> Grid5(5,6);
    Grid<char> Grid6(Grid5);
    ASSERT_EQ(Grid6.numrows(), 5);
    ASSERT_EQ(Grid6.numcols(0), 6);
    ASSERT_EQ(Grid6.numcols(1), 6);
    ASSERT_EQ(Grid6.numcols(2), 6);
    ASSERT_EQ(Grid6.numcols(3), 6);
    ASSERT_EQ(Grid6.numcols(4), 6);
    ASSERT_EQ(Grid6.size(), 30);
    
    Grid<float> Grid7(5,6);
    Grid<float> Grid8(Grid7);
    ASSERT_EQ(Grid8.numrows(), 5);
    ASSERT_EQ(Grid8.numcols(0), 6);
    ASSERT_EQ(Grid8.numcols(1), 6);
    ASSERT_EQ(Grid8.numcols(2), 6);
    ASSERT_EQ(Grid8.numcols(3), 6);
    ASSERT_EQ(Grid8.numcols(4), 6);
    ASSERT_EQ(Grid8.size(), 30);
    
    Grid<double> Grid9(5,6);
    Grid<double> Grid10(Grid9);
    ASSERT_EQ(Grid10.numrows(), 5);
    ASSERT_EQ(Grid10.numcols(0), 6);
    ASSERT_EQ(Grid10.numcols(1), 6);
    ASSERT_EQ(Grid10.numcols(2), 6);
    ASSERT_EQ(Grid10.numcols(3), 6);
    ASSERT_EQ(Grid10.numcols(4), 6);
    ASSERT_EQ(Grid10.size(), 30);
}

TEST(grid, copyOperator) {
    Grid<int> Grid1(5,6);
    Grid<int> Grid2(10,30);
    ASSERT_EQ(Grid1.numrows(), 5);
    ASSERT_EQ(Grid1.numcols(0), 6);
    ASSERT_EQ(Grid1.numcols(1), 6);
    ASSERT_EQ(Grid1.numcols(2), 6);
    ASSERT_EQ(Grid1.numcols(3), 6);
    ASSERT_EQ(Grid1.numcols(4), 6);
    ASSERT_EQ(Grid1.size(), 30);
    ASSERT_EQ(Grid2.numrows(), 10);
    ASSERT_EQ(Grid2.numcols(0), 30);
    ASSERT_EQ(Grid2.numcols(1), 30);
    ASSERT_EQ(Grid2.numcols(2), 30);
    ASSERT_EQ(Grid2.numcols(3), 30);
    ASSERT_EQ(Grid2.numcols(4), 30);
    ASSERT_EQ(Grid2.numcols(5), 30);
    ASSERT_EQ(Grid2.numcols(6), 30);
    ASSERT_EQ(Grid2.numcols(7), 30);
    ASSERT_EQ(Grid2.numcols(8), 30);
    ASSERT_EQ(Grid2.numcols(9), 30);
    ASSERT_EQ(Grid2.size(), 300);
    Grid2 = Grid1;
    ASSERT_EQ(Grid2.numrows(), 5);
    ASSERT_EQ(Grid2.numcols(0), 6);
    ASSERT_EQ(Grid2.numcols(1), 6);
    ASSERT_EQ(Grid2.numcols(2), 6);
    ASSERT_EQ(Grid2.numcols(3), 6);
    ASSERT_EQ(Grid2.numcols(4), 6);
    ASSERT_EQ(Grid2.size(), 30);
    
    Grid<char> Grid3(5,6);
    Grid<char> Grid4(10,30);
    ASSERT_EQ(Grid3.numrows(), 5);
    ASSERT_EQ(Grid3.numcols(0), 6);
    ASSERT_EQ(Grid3.numcols(1), 6);
    ASSERT_EQ(Grid3.numcols(2), 6);
    ASSERT_EQ(Grid3.numcols(3), 6);
    ASSERT_EQ(Grid3.numcols(4), 6);
    ASSERT_EQ(Grid3.size(), 30);
    ASSERT_EQ(Grid4.numrows(), 10);
    ASSERT_EQ(Grid4.numcols(0), 30);
    ASSERT_EQ(Grid4.numcols(1), 30);
    ASSERT_EQ(Grid4.numcols(2), 30);
    ASSERT_EQ(Grid4.numcols(3), 30);
    ASSERT_EQ(Grid4.numcols(4), 30);
    ASSERT_EQ(Grid4.numcols(5), 30);
    ASSERT_EQ(Grid4.numcols(6), 30);
    ASSERT_EQ(Grid4.numcols(7), 30);
    ASSERT_EQ(Grid4.numcols(8), 30);
    ASSERT_EQ(Grid4.numcols(9), 30);
    ASSERT_EQ(Grid4.size(), 300);
    Grid4 = Grid3;
    ASSERT_EQ(Grid4.numrows(), 5);
    ASSERT_EQ(Grid4.numcols(0), 6);
    ASSERT_EQ(Grid4.numcols(1), 6);
    ASSERT_EQ(Grid4.numcols(2), 6);
    ASSERT_EQ(Grid4.numcols(3), 6);
    ASSERT_EQ(Grid4.numcols(4), 6);
    ASSERT_EQ(Grid4.size(), 30);
    
    Grid<string> Grid5(5,6);
    Grid<string> Grid6(10,30);
    ASSERT_EQ(Grid5.numrows(), 5);
    ASSERT_EQ(Grid5.numcols(0), 6);
    ASSERT_EQ(Grid5.numcols(1), 6);
    ASSERT_EQ(Grid5.numcols(2), 6);
    ASSERT_EQ(Grid5.numcols(3), 6);
    ASSERT_EQ(Grid5.numcols(4), 6);
    ASSERT_EQ(Grid5.size(), 30);
    ASSERT_EQ(Grid6.numrows(), 10);
    ASSERT_EQ(Grid6.numcols(0), 30);
    ASSERT_EQ(Grid6.numcols(1), 30);
    ASSERT_EQ(Grid6.numcols(2), 30);
    ASSERT_EQ(Grid6.numcols(3), 30);
    ASSERT_EQ(Grid6.numcols(4), 30);
    ASSERT_EQ(Grid6.numcols(5), 30);
    ASSERT_EQ(Grid6.numcols(6), 30);
    ASSERT_EQ(Grid6.numcols(7), 30);
    ASSERT_EQ(Grid6.numcols(8), 30);
    ASSERT_EQ(Grid6.numcols(9), 30);
    ASSERT_EQ(Grid6.size(), 300);
    Grid6 = Grid5;
    ASSERT_EQ(Grid6.numrows(), 5);
    ASSERT_EQ(Grid6.numcols(0), 6);
    ASSERT_EQ(Grid6.numcols(1), 6);
    ASSERT_EQ(Grid6.numcols(2), 6);
    ASSERT_EQ(Grid6.numcols(3), 6);
    ASSERT_EQ(Grid6.numcols(4), 6);
    ASSERT_EQ(Grid6.size(), 30);
    
    Grid<float> Grid7(5,6);
    Grid<float> Grid8(10,30);
    ASSERT_EQ(Grid7.numrows(), 5);
    ASSERT_EQ(Grid7.numcols(0), 6);
    ASSERT_EQ(Grid7.numcols(1), 6);
    ASSERT_EQ(Grid7.numcols(2), 6);
    ASSERT_EQ(Grid7.numcols(3), 6);
    ASSERT_EQ(Grid7.numcols(4), 6);
    ASSERT_EQ(Grid7.size(), 30);
    ASSERT_EQ(Grid8.numrows(), 10);
    ASSERT_EQ(Grid8.numcols(0), 30);
    ASSERT_EQ(Grid8.numcols(1), 30);
    ASSERT_EQ(Grid8.numcols(2), 30);
    ASSERT_EQ(Grid8.numcols(3), 30);
    ASSERT_EQ(Grid8.numcols(4), 30);
    ASSERT_EQ(Grid8.numcols(5), 30);
    ASSERT_EQ(Grid8.numcols(6), 30);
    ASSERT_EQ(Grid8.numcols(7), 30);
    ASSERT_EQ(Grid8.numcols(8), 30);
    ASSERT_EQ(Grid8.numcols(9), 30);
    ASSERT_EQ(Grid8.size(), 300);
    Grid7 = Grid8;
    ASSERT_EQ(Grid7.numrows(), 10);
    ASSERT_EQ(Grid7.numcols(0), 30);
    ASSERT_EQ(Grid7.numcols(1), 30);
    ASSERT_EQ(Grid7.numcols(2), 30);
    ASSERT_EQ(Grid7.numcols(3), 30);
    ASSERT_EQ(Grid7.numcols(4), 30);
    ASSERT_EQ(Grid7.numcols(5), 30);
    ASSERT_EQ(Grid7.numcols(6), 30);
    ASSERT_EQ(Grid7.numcols(7), 30);
    ASSERT_EQ(Grid7.numcols(8), 30);
    ASSERT_EQ(Grid7.numcols(9), 30);
    ASSERT_EQ(Grid7.size(), 300);
    
    Grid<double> Grid9(5,6);
    Grid<double> Grid10(10,30);
    ASSERT_EQ(Grid9.numrows(), 5);
    ASSERT_EQ(Grid9.numcols(0), 6);
    ASSERT_EQ(Grid9.numcols(1), 6);
    ASSERT_EQ(Grid9.numcols(2), 6);
    ASSERT_EQ(Grid9.numcols(3), 6);
    ASSERT_EQ(Grid9.numcols(4), 6);
    ASSERT_EQ(Grid9.size(), 30);
    ASSERT_EQ(Grid10.numrows(), 10);
    ASSERT_EQ(Grid10.numcols(0), 30);
    ASSERT_EQ(Grid10.numcols(1), 30);
    ASSERT_EQ(Grid10.numcols(2), 30);
    ASSERT_EQ(Grid10.numcols(3), 30);
    ASSERT_EQ(Grid10.numcols(4), 30);
    ASSERT_EQ(Grid10.numcols(5), 30);
    ASSERT_EQ(Grid10.numcols(6), 30);
    ASSERT_EQ(Grid10.numcols(7), 30);
    ASSERT_EQ(Grid10.numcols(8), 30);
    ASSERT_EQ(Grid10.numcols(9), 30);
    ASSERT_EQ(Grid10.size(), 300);
    Grid9 = Grid10;
    ASSERT_EQ(Grid9.numrows(), 10);
    ASSERT_EQ(Grid9.numcols(0), 30);
    ASSERT_EQ(Grid9.numcols(1), 30);
    ASSERT_EQ(Grid9.numcols(2), 30);
    ASSERT_EQ(Grid9.numcols(3), 30);
    ASSERT_EQ(Grid9.numcols(4), 30);
    ASSERT_EQ(Grid9.numcols(5), 30);
    ASSERT_EQ(Grid9.numcols(6), 30);
    ASSERT_EQ(Grid9.numcols(7), 30);
    ASSERT_EQ(Grid9.numcols(8), 30);
    ASSERT_EQ(Grid9.numcols(9), 30);
    ASSERT_EQ(Grid9.size(), 300);
}

TEST(grid, parenOperatorDefault) {
	Grid<int> g1;
	Grid<char> g2;
	Grid<string> g3;
	Grid<float> g4;
	Grid<double> g5;
	
	ASSERT_EQ(g1(0,0), 0);
	ASSERT_EQ(g2(0,0), '\0');
	ASSERT_EQ(g3(0,0), "");
	ASSERT_EQ(g4(0,0), 0.0);
	ASSERT_EQ(g5(0,0), 0.0);
}

TEST(grid, parenOperatorParameterized) {
	Grid<int> g1(10,10);
	Grid<char> g2(10,10);
	Grid<string> g3(10,10);
	Grid<float> g4(10,10);
	Grid<double> g5(10,10);
	
	ASSERT_EQ(g1(9,9), 0);
	ASSERT_EQ(g2(9,9), '\0');
	ASSERT_EQ(g3(9,9), "");
	ASSERT_EQ(g4(9,9), 0.0);
	ASSERT_EQ(g5(9,9), 0.0);
}

TEST(grid, parenOperatorOutOfBounds) {
	Grid<int> g1(10,10);
	Grid<char> g2(10,10);
	Grid<double> g3(10,10);
	Grid<float> g4(10,10);
	Grid<string> g5(10,10);

	
	try {
		g1(-1, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g1(0, -1);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g1(0, 10);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    try {
		g1(10, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    //////
    try {
		g2(-1, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g2(0, -1);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g2(0, 10);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    try {
		g2(10, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g3(-1, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g3(0, -1);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g3(0, 10);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    try {
		g3(10, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g4(-1, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g4(0, -1);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g4(0, 10);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    try {
		g4(10, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g5(-1, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g5(0, -1);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    
    try {
		g5(0, 10);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
    try {
		g5(10, 0);
		
		EXPECT_TRUE(false);
	}
	catch(...) {
        EXPECT_TRUE(true);
    }
}

//  TO DO:  As you get to each milestone, you can comment out these provided
//  tests.  They currently use grid.h and will segfault until you implement
//  grid correctly.  

//  Provided Test: sample maze from handout, make lots more yourself!

TEST(maze, basic) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);

    MazeCell* start = m.getStart(2, 2);

    // These paths are the ones in the handout. They all work.
    EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
    EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
    EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));

    // These paths don't work, since they don't pick up all items. 
    EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNE"));

    // These paths don't work, since they aren't legal paths. 
    EXPECT_FALSE(isPathToFreedom(start, "WW"));
    EXPECT_FALSE(isPathToFreedom(start, "NN"));
    EXPECT_FALSE(isPathToFreedom(start, "EE"));
    EXPECT_FALSE(isPathToFreedom(start, "SS"));
}
//
// Provided Test: don't allow going through walls
TEST(maze, tryingToGoThroughWalls) {
    vector<string> textMaze;

    textMaze.push_back("* S *");
    textMaze.push_back("     ");
    textMaze.push_back("W * P");
    textMaze.push_back( "     ");
    textMaze.push_back( "* * *");

    Maze m(textMaze);

    MazeCell* start = m.getStart(1, 1);

    EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
    EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
    EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
    EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

// Provided Test: Works when starting on an item
TEST(maze, startOnItem) {
    vector<string> textMaze;

    textMaze.push_back("P-S-W");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    EXPECT_TRUE(isPathToFreedom(start, "EE"));
    start = m.getStart(0, 1);
    EXPECT_TRUE(isPathToFreedom(start, "WEE"));
    start = m.getStart(0, 2);
    EXPECT_TRUE(isPathToFreedom(start, "WW"));

}

//  Provided Test: Reports errors if given illegal characters.
TEST(maze, invalidChar) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    /* These paths contain characters that aren't even close to permissible. */
    EXPECT_FALSE(isPathToFreedom(start, "Q"));
    EXPECT_FALSE(isPathToFreedom(start, "X"));
    EXPECT_FALSE(isPathToFreedom(start, "!"));
    EXPECT_FALSE(isPathToFreedom(start, "?"));

    EXPECT_FALSE(isPathToFreedom(start, "n"));
    EXPECT_FALSE(isPathToFreedom(start, "s"));
    EXPECT_FALSE(isPathToFreedom(start, "e"));
    EXPECT_FALSE(isPathToFreedom(start, "w"));

    //  These are tricky - they're legal paths that happen to have an unexpected
    //  character at the end.
    start = m.getStart(2, 2);
    EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES??"));

}

//  Provided Test: This tests your personalized regular maze to see if you were
//  able to escape.
TEST(maze, escapeRegularMaze) {
    Maze m(4, 4);
    MazeCell* start = m.mazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}

//  Provided Test: This tests your personalized twisty maze to see if you were
//  able to escape.
TEST(maze, escapeTwistyMaze) {
    Maze m(4, 4);
    MazeCell* start = m.twistyMazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}

