#pragma once
using namespace std;

class Stack {
private:
	int* darr;
	int size;
	int inUse;
public:
	//  default constructor
	Stack() {
		this->size = 2;
		this->darr = new int[size];
		this->inUse = 0;
	}
	//  pushback: pushes an integer element into the stack
	void push(int element) {
		if (size == inUse) {
			int newSize = size + 2;
			int* newDarr = new int[newSize];

			for (int i = 0; i < inUse; ++i) {
				newDarr[i] = darr[i];
			}

			delete[] darr;
			darr = newDarr;
			size = newSize;
		}
		darr[inUse] = element;
		inUse++;
	}
	//  pop: pops an element of the top of the stack
	void pop() {		
		inUse = inUse - 1;
	}
	//  top: returns the element on the top of the stack without modifying the stack
	int top() {
		return darr[inUse - 1];
	}
	//  isEmpty: returns if the current stack is empty or not
	bool isEmpty()
	{
		if (inUse == 0)
			return true;
		else
			return false;
	}
	//  reset: frees memory
	void reset() {
		delete[] darr;
		inUse = 0;
		size = 2;
	}
};
