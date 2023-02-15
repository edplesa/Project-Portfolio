//  barchart.h
//  Project 3: Author: Edward Plesa, Spring 2021
//  barchart.h: Class used to construct a singular instance of a barchart.
//	Essentially, this object is an entire chart or "frame" to be used in 
//	barchartanimate.

#include <iostream>
#include <algorithm>
#include <map>

#include <bits/stdc++.h>
#include <cmath>

#include "myrandom.h" //  used in autograder, do not remove
#include "bar.h"

using namespace std;

//  Constants used for bar chart animation.  You will primarily
//  use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

//
//  BarChart
//
class BarChart {
 private:
    //
    //  Private member variables for the abstraction.
    //  This implementation uses a low-level C array, bars, to store a list of
    //  Bars.  As a result, you must also keep track of the number of elements
    //  stored (size) and the capacity of the array (capacity).  This is not a
    //  dynamic array, so it does not expand.
    //
    Bar* bars;  //  pointer to a C-style array
    int capacity;
    int size;
    string barChartFrame;
    
 public:
    //  default constructor:
    BarChart() {
    	bars = nullptr;
    	this->capacity = 0;
    	this->size = 0;
    	this->barChartFrame = "";
    }
    
    //  parameterized constructor:
    //  Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
    	this->capacity = n;
    	this->bars = new Bar[this->capacity];
    	this->size = 0;
    	this->barChartFrame = "";
    }

    //
    //  copy constructor:
    //
    //  Called automatically by C++ to create an BarChart that contains
    //  a copy of an existing BarChart.  Example: this occurs when passing
    //  BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {
    	this->bars = new Bar[other.capacity];
        this->size = other.size;
        this->capacity = other.capacity;
        this->barChartFrame = other.barChartFrame;
        for (int i = 0; i < other.size; ++i) {
        	this->bars[i] = other.bars[i];
        }
    }
    //
    //  copy operator=
    //
    //  Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {
    	if (this == &other) {
    		return *this;
    	}
	    delete[] bars;
	    this->bars = new Bar[other.capacity];
	    this->size = other.size;
    	this->capacity = other.capacity;
    	this->barChartFrame = other.barChartFrame;
        for (int i = 0; i < other.size; ++i) {
	      this->bars[i] = other.bars[i];
	    }
	    return *this;
    }

    //  clear
    //  frees memory and resets all private member variables to default values.
    void clear() {
        delete[] bars;
        bars = nullptr;
        this->size = 0;
        this->capacity = 0;
        this->barChartFrame = "";
    }
    
    //
    //  destructor:
    //
    //  Called automatically by C++ to free the memory associated by the
    //  BarChart.
    //
    virtual ~BarChart() {
    	if (bars != nullptr) {
    		delete[] bars;
    		bars = nullptr;
    	}
    }
    
    //  setFrame
    void setFrame(string frame) {
        this->barChartFrame = frame;
    }
    
    //  getFrame()
    //  Returns the frame of the BarChart oboject.
    string getFrame() {
        return this->barChartFrame;
    }

    //  addBar
    //  adds a Bar to the BarChart.
    //  returns true if successful
    //  returns false if there is not room
    bool addBar(string name, int value, string category) {
        if (this->size == this->capacity) {
        	return false;
        }
        Bar b(name, value, category);
        this->bars[size] = b;
        this->size++;
        return true;
    }
    
    //  getSize()
    //  Returns the size (number of bars) of the BarChart object.
    int getSize() {
    	return this->size;
    }
    
    //  operator[]
    //  Returns Bar element in BarChart.
    //  This gives public access to Bars stored in the Barchart.
    //  If i is out of bounds, throw an out_of_range error message:
    //  "BarChart: i out of bounds"
    Bar& operator[](int i) {
        if (i >= this->size || i < 0) {
        	throw out_of_range("BarChart: i out of bounds");
        }
        return bars[i];
    }
    
    //  dump
    //  Used for printing the BarChart object.
    //  Recommended for debugging purposes.  output is any stream (cout,
    //  file stream, or string stream).
    //  Format:
    //  "frame: 1
    //  aname 5 category1
    //  bname 4 category2
    //  cname 3 category3" <-newline here
    void dump(ostream &output) {
    	sort(bars, bars + size, greater<Bar>());
		output << "frame: "  << this->barChartFrame << endl;
		
        for (int i = 0; i < size; i++) {
        	output << bars[i].getName() << " " 
        		   << bars[i].getValue() << " "
        		   << bars[i].getCategory() << "\n";
        }
        
    }
    
    //  graph
    //  Used for printing out the bar.
    //  output is any stream (cout, file stream, string stream)
    //  colorMap maps category -> color
    //  top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	sort(bars, bars + size, greater<Bar>());
    	int lenMax = 60;  // this is number of BOXs that should be printed
    	int max = bars[0].getValue();
    	if(top > this->size) {
    		top = this->size;
    	}
    	for (int i = 0; i < top; i++) {
    		string barstr;
    		if (i == 0)
    		{
    			for (int i = 0; i < lenMax; i++) 
    			{
        			barstr += BOX;
        		}
        		string color;
        		map<string, string>::iterator it;
        		it = colorMap.find(bars[i].getCategory());
        		if (it == colorMap.end() || colorMap.empty() == true) {
        			color = COLORS[6];
        		}
        		else {
        			color = it->second;
        		}
        		output << color << barstr << " " << bars[i].getName()
        		<< " " << bars[i].getValue() << endl;
    		}
    		else {
    			float ratio = bars[i].getValue()/(float)max;
    			for (int i = 0; i < floor(ratio*lenMax); i++) {
        			barstr += BOX;
        		}
        		string color;
        		map<string, string>::iterator it;
        		it = colorMap.find(bars[i].getCategory());
        		if (it == colorMap.end() || colorMap.empty() == true) {
        			color = COLORS[6];
        		}
        		else {
        			color = it->second;
        		}
        		output << color << barstr << " " << bars[i].getName()
        		<< " " << bars[i].getValue() << endl;
    		}
    	}
    }
    
};