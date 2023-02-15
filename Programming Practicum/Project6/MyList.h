#pragma once

#include <iostream>
using namespace std;


class MyList
{
private:

	class MyNode {
	public:
		int value;
		MyNode* next;
	
		MyNode(int v) {
			value = v;
			next = nullptr;
		}
	};


	MyNode* head;	

public:

	MyList() {
		head = nullptr;		
	}
	~MyList() {
		while (head != nullptr) {
			MyNode* tempPtr = head;
			head = head->next;
			delete tempPtr;
		}
	}

	void resetList() {
		while (head != nullptr) {
			MyNode* tempPtr = head;
			head = head->next;
			delete tempPtr;
		}
	}

	void pushBack(int val) {
		MyNode* newN = new MyNode(val);
		MyNode* cur = head;

		if (head == nullptr) {
			head = newN;
		}
		else {
			while (cur->next != nullptr) {
				cur = cur->next;
			}
			cur->next = newN;
		}
	}

	void pushFront(int val) {
		MyNode* newN = new MyNode(val);

		if (head == nullptr) {
			head = newN;
		}
		else {
			newN->next = head;
			head = newN;
		}
	}

	void popFront() {
		if (head != nullptr) {
			MyNode* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void popBack() {
		if (head != nullptr) {
			MyNode* cur = head;
			MyNode* prev = nullptr;
			while (cur->next != nullptr) {
				prev = cur;
				cur = cur->next;
			}
			prev->next = nullptr;
			delete cur;
		}
	}

	void deleteValue(int val) {
		MyNode* cur = head;
		MyNode* prev = nullptr;

		if (cur && cur->value == val) {
			head = cur->next;
			delete cur;
			return;
		}
		else {
			while (cur && cur->value != val) {
				prev = cur;
				cur = cur->next;
			}
			if (!cur) {
				return;
			}
			prev->next = cur->next;
			delete cur;
		}
	}

	int top() {		
		if (head != nullptr) {
			return head->value;
		}
	}

	int getNumberOfCurrentValues() {
		if (head == nullptr) {
			return 0;
		}
		else {
			MyNode* cur = head;
			int count = 1;

			while (cur->next != nullptr) {
				cur = cur->next;
				count++;
			}
			return count;
		}
	}

	int getNthValue(int pos) {
		int count = 0;
		MyNode* cur = head;

		while (cur != nullptr) {
			if (count == pos) {
				return cur->value;
			}
			count++;
			cur = cur->next;
		}
	}

	void printList() {
		MyNode* cur = head;

		while (cur != nullptr) {
			cout << "  " << cur->value;
			cur = cur->next;
		}
		//cout << cur->value;
	}
	
	void printBFS() {
		MyNode* cur = head;
		
		if (cur != nullptr) {
			cout << cur->value;
			
			cur = cur->next;
			while (cur != nullptr) {
				cout << " - " << cur->value;
				cur = cur->next;
			}
		}
	}

	bool search(int val) {
		MyNode* cur = head;
		while (cur != nullptr) {
			if (cur->value == val) {
				return true;
			}
			cur = cur->next;
		}
		return false;
	}

	bool isEmpty() {
		if (head == nullptr) {
			return true;
		}
		return false;
	}
};
