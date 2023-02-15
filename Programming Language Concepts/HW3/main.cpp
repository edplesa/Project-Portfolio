// Edward Plesa 
// Fall 2021
#include <iostream>
#include "InfInt.h" // Using the InfInt int class from
					// https://github.com/sercantutar/infint/blob/master/InfInt.h
using namespace std;
  
// Driver Code
int main()
{
    InfInt myBigInt = "1";
	
	for (int i = 1; i < 101; i++) {
		myBigInt *= i;
	}

	cout << myBigInt.toString();
}
