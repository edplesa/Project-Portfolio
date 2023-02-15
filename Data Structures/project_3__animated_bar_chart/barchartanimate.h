//  barchartanimate.h
//  Project 3: Author: Edward Plesa, Spring 2021
//  barchartanimate.h: Class used to put together a group of barcharts.
//	Essentially, this class will piece together and animate all individual
//	frames of a barchart.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <string>

#include <unistd.h>
#include "myrandom.h" //  used in autograder, do not remove
#include "barchart.h"
  
using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    //  Private member variables for the abstraction.
    //  This implementation uses a low-level C array, bars, to store a list of
    //  BarCharts.  As a result, you must also keep track of the number of
    //  elements stored (size) and the capacity of the array (capacity).
    //  This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    string frameTitle;
    string frameSource;
    string frameLabel;
    int index;  //  index for colorMap

 public:
    //  a parameterized constructor:
    //  Like the ourvector, the barcharts C-array should be constructed here
    //  with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
        barcharts = new BarChart[4];
        size = 0;
        capacity = 4;
        frameLabel = xlabel;
        frameSource = source;
        frameTitle = title;
        index = 0;
    }
    

    //
    //  destructor:
    //
    //  Called automatically by C++ to free the memory associated
    //  by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        if (barcharts != nullptr) {
        	delete[] barcharts;
        	barcharts = nullptr;
        }
    }
    
    //  getLabel: returns the frame's label
    string getLabel() {
    	return this->frameLabel;
    }
    
    //  getLabel: returns the frame's title
    string getTitle() {
    	return this->frameTitle;
    }
    
    //  getLabel: returns the frame's source
    string getSource() {
    	return this->frameSource;
    }

    //  addFrame:
    //  adds a new BarChart to the BarChartAnimate object from the file stream.
    //  if the barcharts has run out of space, double the capacity (see
    //  ourvector.h for how to double the capacity).
    //  See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
    	//	doubles capacity of barcharts[] array
    	//
        if (size == capacity) {
        	int newCapacity = capacity * 2;
	    	BarChart* newBarChart = new BarChart[newCapacity];
	    	//  copy the elements from barcharts to the new array:
	    	for (int i = 0; i < size; ++i) {
	    		newBarChart[i] = barcharts[i];
	    	}
	    	//  now delete barcharts, and update private data members to point to new array
	    	//  and reflect new capacity:
	    	delete[] barcharts;
	    	barcharts = newBarChart;
	    	capacity = newCapacity;
	    }
        string line;
        getline(file, line); // consume empty line
        getline(file, line); //get top value
        if(line == "") { //  if the line is empty then the file has ended
        	return;
        }
        int numBars = stoi(line);
        BarChart frame(numBars);
        for (int i = 0; i < numBars; i++) {
        	getline(file, line);
        	stringstream ss(line);
	        string temp;
	        string framenum;
	        string name;
	        string tempvalue;
	        string category;
	        
	        getline(ss, framenum, ',');
	        getline(ss, name, ',');
	        getline(ss, temp, ',');
	        getline(ss, tempvalue, ',');
	        getline(ss, category, ',');
	        
	        map<string,string>::iterator it;
	        it = colorMap.find(category);
	        if (it == colorMap.end()) {
	        	colorMap.emplace(category, COLORS[this->index]);
	        	this->index++;
	        }
	        if (this->index > 6) { //  resets global index counter
	        	this->index = 0;
	        }
	        int value = stoi(tempvalue);
	        frame.setFrame(framenum);
	        frame.addBar(name, value, category);
        }
        barcharts[size] = frame;
        this->size++;
    }

    //  animate:
    //  this function plays each frame stored in barcharts.  In order to see the
    //  animation in the terminal, you must pause between each frame.  To do so,
    //  type:  usleep(3 * microsecond);
    //  Additionally, in order for each frame to print in the same spot in the
    //  terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    //  in between each frame.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
		if(endIter == -1) {
			endIter = this->size;
		}
		for (int i = 0; i < endIter; i++) {
			
			usleep(3*microsecond);
			output << CLEARCONSOLE;
			
			output << COLORS[6] << this->getTitle() << endl;
			output << COLORS[6] << this->getSource() << endl;
			
			barcharts[i].graph(output, colorMap, top);
			
			output << COLORS[6] << this->getLabel() << endl;
			output << COLORS[6] << "Frame: " << barcharts[i].getFrame() << endl;
		}
	}

    //
    //   Public member function.
    //  Returns the size of the BarChartAnimate object.
    //
    int getSize(){
        return this->size;
    }

    //
    //  Public member function.
    //  Returns BarChart element in BarChartAnimate.
    //  This gives public access to BarChart stored in the BarChartAnimate.
    //  If i is out of bounds, throw an out_of_range error message:
    //  "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i){
        if (i >= this->size || i < 0) {
        	throw out_of_range("BarChartAnimate: i out of bounds");
        }
        return barcharts[i];
    }
};