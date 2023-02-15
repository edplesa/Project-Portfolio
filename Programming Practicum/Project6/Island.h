#pragma once
#include <iostream>
#include "MyList.h"

class Island {
private:
	MyList* adj;
	int visited;

public:

	Island();
	void insertEdge(int edge);
	void removeEdge(int edge);
	void printEdges();
	void resetAdj();
	void setVisited(int val);
	int getVisited();
	int getEdges();
	int getNthIsland(int val);
};
