//  bar.h
//  Project 3: Author: Edward Plesa, Spring 2021
//  bar.h: Class used to construct a singular instance of a bar.

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    //  Private member variables for a Bar object
    //  
    string barName;
    long int barValue;
    string barCategory;

 public:
    // default constructor:
    Bar() {
        this->barName = "";
        this->barValue = 0;
        this->barCategory = "";
    }

    //
    //  a second constructor:
    //
    //  Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
        this->barName = name;
        this->barValue = value;
        this->barCategory = category;
    }

    //  destructor:
    virtual ~Bar() {
    }

    //  getName: returns name of this object
	string getName() {
        return this->barName;
	}

    //  getValue: returns value of this object
	int getValue() {
        return this->barValue;
	}

    //  getCategory: returns category of this object
	string getCategory() {
        return this->barCategory;
	}

	//  operators
    //  This allows you to compare two Bar
    //  objects.  Comparison is based on the Bar's value.
	bool operator<(const Bar &other) const {
		if (this->barValue < other.barValue) {
			return true;
		}
        return false;
	}

	bool operator<=(const Bar &other) const {
        if (this->barValue < other.barValue || 
        	this->barValue == other.barValue) {
			return true;
		}
        return false;
	}

	bool operator>(const Bar &other) const {
        if (this->barValue > other.barValue) {
			return true;
		}
        return false;
	}

	bool operator>=(const Bar &other) const {
        if (this->barValue < other.barValue || 
        	this->barValue == other.barValue) {
			return true;
		}
        return false;
	}
};