//	Author: Edward Plesa, Spring 2021, Project 4
//

#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

const string kYourName = "Edward Plesa";

const string kPathOutOfRegularMaze = "ESWSESENNENW";
const string kPathOutOfTwistyMaze = "SEEEWNNWSSW";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    bool Potion = false;
    bool Spellbook = false;
    bool Wand = false;
    for (unsigned i = 0; i < moves.size(); ++i) {
    	if (moves[i] != 'N' && moves[i] != 'W'
    		&& moves[i] != 'S' && moves[i] != 'E') {
    		return false;
    	}
    }
    MazeCell* cur = start;
    for (unsigned i = 0; i < moves.size()+1; ++i) {
    	if (cur->whatsHere == "Potion") {
    		Potion = true;
    	}
    	else if (cur->whatsHere == "Spellbook") {
    		Spellbook = true;
    	}
    	else if (cur->whatsHere == "Wand" ) {
    		Wand = true;
    	}
    	
    	if (moves[i] == 'N' && cur->north != nullptr) {
    		cur = cur->north;
    	}
    	else if (moves[i] == 'S' && cur->south != nullptr) {
    		cur = cur->south;
    	}
    	else if (moves[i] == 'E' && cur->east != nullptr) {
    		cur = cur->east;
    	}
    	else if (moves[i] == 'W' && cur->west != nullptr) {
    		cur = cur->west;
    	}
    	else if (moves[i] == 'N' && cur->north == nullptr) {
    		return false;
    	}
    	else if (moves[i] == 'E' && cur->east == nullptr) {
    		return false;
    	}
    	else if (moves[i] == 'S' && cur->south == nullptr) {
    		return false;
    	}
    	else if (moves[i] == 'W' && cur->west == nullptr) {
    		return false;
    	}
    }
    if (Potion && Spellbook && Wand) {
    	return true;
    }
    else {
    	return false;
    }
}
