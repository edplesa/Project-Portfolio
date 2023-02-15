#include "Island.h"

	Island::Island() {
		adj = new MyList();
		visited = -1;
	}

	void Island::insertEdge(int edge) {
		if (adj->search(edge) == false) {
			adj->pushBack(edge);
		}		
		else {
			cout << "Ferry ride already added!\n";
		}
	}

	void Island::removeEdge(int edge) {
		if (adj->search(edge) == true) {
			adj->deleteValue(edge);
		}
		else {
			cout << "Ferry ride does not exist\n";
		}
	}

	void Island::printEdges() {
		adj->printList();
	}

	void Island::resetAdj() {
		adj->resetList();
		delete adj;
		adj = nullptr;
	}

	void Island::setVisited(int val) {
		this->visited = val;
	}

	int Island::getVisited() {
		return visited;
	}

	int Island::getEdges() {
		return adj->getNumberOfCurrentValues();
	}

	int Island::getNthIsland(int val) {
		return adj->getNthValue(val);
	}
