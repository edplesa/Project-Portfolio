//
// Homework 1
// Spring 2021
// << Edward Plesa >>
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readFromFile() {
    string filename;    
    getline(cin, filename);    

    ifstream infile(filename);

    if (!infile.good()) {
        cout << "File not found..." << endl;
        return;
    }

    string temp;
    while (getline(infile, temp)) {
		cout << temp << "\n";  	
    }

    infile.close();
}

int main()
{
    readFromFile();    
}


