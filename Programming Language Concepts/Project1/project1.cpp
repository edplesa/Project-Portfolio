#include <iostream>
#include <vector>
#include <utility>
#include "grader.h"

/*
	Author: Edward Plesa
	Fall 2021
	Project 1
*/

using namespace std;


class chessboard {
private:
	pair<int, int> Board[8][8];

public:
	
	// need xy, derefernce, !=, increment for iterator
	class Iterator {	
	public:				
		using value_type = pair<int, int>;
		using pointer = pair<int, int>*;
		using reference = pair<int, int>&;

		Iterator(pointer ptr) : CB(ptr) {			
		}

		reference operator*() const {
			return *CB; 
		}
		pointer operator->() {
			return CB; 
		}

		Iterator& operator++() { 			
			CB++; 
			return *this; 
		}
		Iterator operator++(int) { 
			Iterator tmp = *this; 
			++(*this); 
			return tmp;
		}
		bool operator== (const Iterator& b) {
			return CB == b.CB; 
		};
		bool operator!= (const Iterator& b) {
			return CB != b.CB; 
		};
		Iterator xy(int x, int y) {

		}

	private:
		pointer CB;
	};


	Iterator begin() {
		return Iterator(&Board[0][0]);
	}

	Iterator end() {
		return Iterator(&Board[8][0]);
	}

	chessboard() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Board[i][j] = make_pair(-1, -1);
			}
		}
	}

	int place(int x, int y, testcolor c, testpiece p) {
		if (x < 0 || x > 7) {
			return -1;
		}

		if (y < 0 || y > 7) {
			return -2;
		}

		if (c != Black && c != White) {
			return -4;
		}

		if (p != Rook && p != Knight && p != Bishop && p != Queen && p != King && p != Pawn) {
			return -5;
		}

		pair<int, int> pos = Board[x][y];
		if (pos.first != -1 && pos.second != -1) {
			return -3;
		}


		Board[x][y] = make_pair(c,p);
		return 1;		
	}

	int get(int x, int y, testcolor &c, testpiece &p) {
		if (x < 0 || x > 7) {
			return -1;
		}

		if (y < 0 || y > 7) {
			return -2;
		}

		pair<int, int> pos = Board[x][y];
		if (pos.first == -1 && pos.second == -1) {
			return -3;
		}

		c = (testcolor)pos.first;
		p = (testpiece)pos.second;

		return 1;		
	}

	int testPlace(int x, int y, testcolor c, testpiece p) {
		return place(x,y,c,p);
	}

	int testGet(int x, int y, testcolor &c, testpiece &p) {
		return get(x, y, c, p);
	}
};