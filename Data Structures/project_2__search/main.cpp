//	Author: Edward Plesa, Project2, Spring 2021
//
//	Program overview: Using the map and set data abstractions, this Program
//	process and indexes a url and its body content in a way which can be used
//	to quickly search for and even specify which words to add to the search
//	or filter out.

#include <iostream>

#include <map>
#include <set>
#include <string>
#include <algorithm>

#include "search.h"

using namespace std;

int main()
{
    cout << "Enter file name to process: ";
    string fname;
    getline(cin, fname);
    
    cout << endl;
    
    searchEngine(fname);
    
    return 0;
}

