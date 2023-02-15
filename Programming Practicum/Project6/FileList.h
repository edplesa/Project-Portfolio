#pragma once

#include <iostream>
using namespace std;


class FileList
{
private:

	class MyNodeF {
	public:
		string value;
		MyNodeF* next;

		MyNodeF(string v) {
			value = v;
			next = nullptr;
		}
	};


	MyNodeF* head;

public:

	FileList() {
		head = nullptr;
	}
	~FileList() {
		while (head != nullptr) {
			MyNodeF* tempPtr = head;
			head = head->next;
			delete tempPtr;
		}
	}

	void resetFiles() {
		while (head != nullptr) {
			MyNodeF* tempPtr = head;
			head = head->next;
			delete tempPtr;
		}
	}

	void pushBackFile(string val) {
		MyNodeF* newN = new MyNodeF(val);
		MyNodeF* cur = head;

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

	string topFile() {
		if (head != nullptr) {
			return head->value;
		}
	}	

	bool searchFile(string val) {
		MyNodeF* cur = head;
		while (cur != nullptr) {
			if (cur->value == val) {
				return true;
			}
			cur = cur->next;
		}
		return false;
	}

	bool isEmptyFile() {
		if (head == nullptr) {
			return true;
		}
		return false;
	}

	void deleteFile(string val) {
		MyNodeF* cur = head;
		MyNodeF* prev = nullptr;

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
};
