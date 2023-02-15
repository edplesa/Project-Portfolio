//
//  Project 1 Starter Code - Recommendations
//  Author: Edward Plesa, Spring 2021, CS251
//
//  Creative Component: command to type "similarity": the use of the dotproduct in our Code
//  matches the similarity of two users "tastes" ie: the greater the absolute value of the 
//	product means the greater the similarity. This command will check the similarity between ALL
//	users as a sort of "interpratory data" creation. 
//	
//	If taste is truly subjective we should find that the
//	product between all users should be close to 0. Given an arbitrarily large item set, this should be the case.
//	However, we may find that since we are all CS students (a subset of the general population) we may find
//	that to not be not true(as subsets of a population have similar properties). 
//	
//	The rating of 0 poses the problem of  multiplying by 0 which also results in 0.
//	For this reason we use a 1 instead. While this may not pose a perfect result: it will still be
//	interesting to see that value created.
//

#include "ourvector.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cfloat>
using namespace std;

struct Items
{
	string itemName;
	double avgRating;
	int pos;
};

struct Users
{
	string userName;
	ourvector<int> ratings;
};

//
//loadData command: input the file names for the items and the ratings files along with the 
//vector containers to store the necessary data in each respective container. containers are
//passed by reference to minimize the number of vectors created.
//
void loadData(string itemsFile, string ratingsFile, ourvector<Items> &itemsList, ourvector<Users> &usersList)
{
	int count1 = 0;
	string item;
	ifstream infile(itemsFile);
	
	if(!infile.good())
	{
		cout << "Item file not opened!" << endl;
	}
	else
	{
		cout << endl << "Reading items file..." << endl;
		while(!infile.eof())
		{
			
			Items newItem;
			getline(infile, item);
			newItem.itemName = item;
			newItem.pos = count1;
			
			if (!infile.fail())  // data was successfully input:
    		{   
    			itemsList.push_back(newItem);
    		}  
			count1++;
		}
	}
	
	infile.close();
	
	for (int i = 0; i < count1-1; i++)
	{
		cout << itemsList[i].itemName << endl;
	}
	
	ifstream infile2(ratingsFile);
	
	int count = 0;
	
	if(!infile2.good())
	{
		cout << "Ratings file not opened!" << endl;
	}
	else
	{
		cout << endl << "Reading ratings file..." << endl;
		while(!infile2.eof())
		{
			Users newUser;
			
			string name;
			string ratingLine;
			
			getline(infile2, name);
			newUser.userName = name;
			
			getline(infile2, ratingLine);
			
			istringstream streamNum(ratingLine);
			int num;
			
			while(streamNum >> num)
			{
				newUser.ratings.push_back(num);
			}
			
			if(!infile2.fail())
			{
				usersList.push_back(newUser);
			}
			
			count++;
		}
	}
	
	infile2.close();
	
	for (int i = 0; i < count-1; i++)
	{
		cout << usersList[i].userName << endl;
		
		
		for (int j = 0; j<count1-1; j++)
		{
			cout << usersList[i].ratings[j] << " ";
		}
		
		cout << endl;
	}
	
	cout << endl << "Welcome to the Recommendations App!" << endl;
}


//
// checkUser command: give the name and position of a user(with respect to the main container),
// and the container of all recorded users which checks if the user is logged in. If the user is not logged in
// the position is updated by reference and gives an error message telling the user to login.
//
//
bool checkUser(string user, ourvector<Users> &usersList, int &pos)
{
	bool foundUser = false;
	pos = 0;
	
	cout << endl;
	cout << "-----------------------------" << endl;
	cout << endl;
	
	for(int i = 0; i < usersList.size(); i++)
	{
		if (user == usersList[i].userName)
		{
			foundUser = true;
			break;
		}
		pos++;
	}
	
	if(foundUser == false)
	{
		cout << "User not found, please try again." << endl;
		cout << "Logged in as: N/A" << endl;
		return false;
	}
	else
	{
		cout << "Success." << endl;
		cout << "Logged in as: " << usersList[pos].userName << endl;
		return true;
	}
}

//
// notLoggedInMessage: creates the error message telling the user is not logged in.
// Quality of life function
//
void notLoggedInMessage()
{
	cout << "To complete the operation, you must first login." << endl;
	cout << "Type \"login username\"." << endl;
    cout << endl << "Logged in as: N/A" << endl;
}

//
// formatLine: creates the formatting between the lines of consecutive commands
// Quality of life function
//
void formatLine()
{
	cout << endl;
	cout << "-----------------------------" << endl;
	cout << endl;
}

//
// sort: given a vector and its size, the function sorts the items in the container from largest to smallest
// and returns the updated  vector back to the user.
//
//
ourvector<Items> &sort(ourvector<Items> &avgRatingTop, int size)
{
	Items temp;
	
	for(int i = 0; i < size; i++)
	{
		for(int j = i+1; j<size; j++)
		{
			if(avgRatingTop[i].avgRating < avgRatingTop[j].avgRating)
			{
				
				temp = avgRatingTop[i];
				avgRatingTop[i] = avgRatingTop[j];
				avgRatingTop[j] = temp;
				
			}
		}
	}
	return avgRatingTop;
}


//
// sortByPos: given a vector and its size, the function sorts the items in the already sorted container 
// by its position (smallest to largest) so as to group elements with equal ratings by their position in the main container
// and returns the update vector back to the user. Call this after the inital "sort" command
//
//
ourvector<Items> &sortByPos(ourvector<Items> &avgRatingTop, int size, ourvector<Items> &itemsList)
{
	Items temp;
	
	for(int i = 0; i < size; i++)
	{
		for(int j = i+1; j<size; j++)
		{
			if(avgRatingTop[i].avgRating == avgRatingTop[j].avgRating && avgRatingTop[i].pos > avgRatingTop[j].pos)
			{
				
				temp = avgRatingTop[i];
				avgRatingTop[i] = avgRatingTop[j];
				avgRatingTop[j] = temp;
				
			}
		}
	}
	
	return avgRatingTop;
}

//
// basicRecommendations: give the main containers for the items and their ratings along with the 
// position of the user respective to the ratings container. The function will then create two vectors:
// 1. containing all of the calculated averages for the items in the list and 2. containing the highest averages
// that the specified user has not already seen. Calls sort and sortByPos to update the vector specific to the 
// user. Then prints the top 5 recommendations to the user.
//
//
//
void basicRecommendations(ourvector<Items> &itemsList, ourvector<Users> &usersList, int userPos)
{
	int sum;
	
	ourvector<Items> avgRatingTop;
	ourvector<Items> avgRatingAll;
	
	for(int i = 0; i < itemsList.size(); i++)
	{
		sum = 0;
		for(int j = 0; j < usersList.size(); j++)
		{
			sum+=usersList[j].ratings[i];
		}
		
		double avg = 0.0;
		avg = (double)sum / itemsList.size();
		
		Items newItem;
		
		newItem.itemName = itemsList[i].itemName;
		newItem.avgRating = avg;
		
		avgRatingAll.push_back(newItem);
	}
	
	for(int i = 0; i < avgRatingAll.size(); i++)
	{
		if(usersList[userPos].ratings[i]==0)
		{
			Items newItem;
			newItem.itemName = avgRatingAll[i].itemName;
			newItem.avgRating = avgRatingAll[i].avgRating;
			newItem.pos = i;
			
			avgRatingTop.push_back(newItem);
		}
	}
	
	sort(avgRatingTop, avgRatingTop.size());
	sortByPos(avgRatingTop, avgRatingTop.size(), itemsList);
	
	cout << "Basic recommendations:" << endl;
	
	if(avgRatingTop.size() > 5)
	{
		for(int i = 0; i < 5; i++)
		{
			cout << avgRatingTop[i].itemName << endl;
		}
	}
	else
	{
		for(int i = 0; i < avgRatingTop.size(); i++)
		{
			cout << avgRatingTop[i].itemName << endl;
		}
	}
	
	cout << endl << "Logged in as: " << usersList[userPos].userName << endl;
}


//
// closestMatchPosition: given a vector, this function will find the position of the highest value
// and return it back to the user.
//
//
int closestMatchPosition(ourvector<int> &dotProducts)
{
	int max = dotProducts[0];
	
	for(int i = 1; i < dotProducts.size(); i++)
	{
		if(dotProducts[i]>max)
		{
			max = dotProducts[i];
		}
	}
	
	for(int i = 0; i < dotProducts.size(); i++)
	{
		if(max == dotProducts[i])
		{
			return i;
		}
	}
	return -1;
}

//
//
// advancedRecommendations: given the containers with all items and their ratings, along with
// the position of the user with resepct to the main ratings list: the function will create 2 vectors
// 1. containing all the dot products between the specified user and all others. 2. containing 
// the highest rated items based on the match with the highest similarity. calls the closestMatchPosition
// to find in which position the highest similarity user is found and then sort and sortByPos to finalized
// and return the sorted vector. Finally, we print the top 5 advanced recommendations out of the sorted vector.
// (if the vector contains more than five elements then print the first five, else print how ever many 
// elements there are)
//
//
void advancedRecommendations(ourvector<Items> &itemsList, ourvector<Users> &usersList, int userPos)
{
	ourvector<int> dotProdList;
	
	int dotProdValue;
	
	for(int i = 0; i < usersList.size(); i++)
	{
		dotProdValue = 0;
		
		for(int j = 0; j < itemsList.size(); j++)
		{
			if(i != userPos)
			{
				dotProdValue += usersList[userPos].ratings[j] * usersList[i].ratings[j];
			}
		}
		dotProdList.push_back(dotProdValue);
	}
	
	int highestMatchPos = closestMatchPosition(dotProdList);
	
	ourvector<Items> dotProdTop;
	
	//int pos = 0;
	
	for(int i = 0; i < itemsList.size(); i++)
	{
		if(usersList[userPos].ratings[i]==0)
		{
			Items newItem;
			newItem.itemName = itemsList[i].itemName;
			newItem.avgRating = usersList[highestMatchPos].ratings[i];
			newItem.pos = i;
			dotProdTop.push_back(newItem);
		}
	}
	
	sort(dotProdTop, dotProdTop.size());
	sortByPos(dotProdTop, dotProdTop.size(), itemsList);

	cout << "Advanced recommendations:" << endl;
	
	if(dotProdTop.size() > 5)
	{
		for(int i = 0; i < 5; i++)
		{
			cout << dotProdTop[i].itemName << endl;
		}
	}
	else
	{
		for(int i = 0; i < dotProdTop.size(); i++)
		{
			cout << dotProdTop[i].itemName << endl;
		}
	}
	
	cout << endl << "Logged in as: " << usersList[userPos].userName << endl;
}

//	
//	similarityBetweenAll: creates one vector to hold the similarity for each Items
//	the sum is then calculated, returning the global similary of the users vector.
//	In the case of 0 rating, we multiply by 1
//
int similarityBetweenAll(ourvector<Users> &usersList, ourvector<Items> &itemsList)
{
	int similarityValue = 1;
	
	ourvector<int> temp;
	
	for(int i = 0; i < itemsList.size(); i++)
	{
		similarityValue = 1;
		
		for(int j = 0; j < usersList.size(); j++)
		{
			if(usersList[j].ratings[i] == 0)
			{
				
			}
			else
			{
				similarityValue *= usersList[j].ratings[i];
			}
		}
		temp.push_back(similarityValue);
	}
	
	similarityValue = 0;
	
	for(int i = 0; i < temp.size(); i++)
	{
		similarityValue += temp[i];
	}
	
	return similarityValue;
}


int main() {
    
    cout << "To start the app, load the data." << endl 
    	 << "Type \"load itemsFile ratingsFile\" and press enter." << endl << endl;
    
    string command;
    
    ourvector<Items> itemsList;
    ourvector<Users> usersList;
	
	bool loggedIn = false;
	int position;
    
    while(true)
    {
    	cout << "Enter command or # to quit: ";
    	getline(cin, command);
    	
    	if(command.front() == 'l')
    	{
    		if(command.substr(0, 4) == "load") //load command: loads all data into the vectors
    		{
    			command.erase(0,5);
    			int split = command.find(" ");
    			string itemsFile = command.substr(0, split);
    			string ratingsFile = command.substr(split+1);
    			loadData(itemsFile, ratingsFile, itemsList, usersList);
    		}
    		else //login command: logs a user in if name is found in the main Users vector
    		{
    			command.erase(0, 6);
    			loggedIn = checkUser(command, usersList, position);
    		}
    		
    	}
    	else if(command == "show")//show command: shows the ratings of all items for the logged in user. 
    	{
    		formatLine();
    		
    		if(loggedIn == true)
    		{
    			cout << usersList[position].userName << "'s Ratings:" << endl;
    			for(int i = 0; i<itemsList.size(); i++)
    			{
    				if(usersList[position].ratings[i] != 0)
    				{
    					cout << itemsList[i].itemName << ", " << usersList[position].ratings[i] << "/5" << endl;
    				}
    			}
    			cout << endl << "Logged in as: " << usersList[position].userName << endl;
    		}
    		else
    		{
    			notLoggedInMessage();
    		}
    		
    	}
    	else if(command == "basic")//basic recommendations command: calls the basicRecommendations function
    	{
    		formatLine();
			
			if(loggedIn == true)
			{
				basicRecommendations(itemsList, usersList, position);
			}
			else
			{
				notLoggedInMessage();
			}
    	}
    	else if(command == "advanced")//advanced recommendations: calls the advancedRecommendations function
    	{
    		formatLine();
			
			if(loggedIn == true)
			{
				advancedRecommendations(itemsList, usersList, position);
			}
			else
			{
				notLoggedInMessage();
			}
    	}
    	else if(command.front() == 'p') //start of print command
    	{
    		command.erase(0,6);
    		
    		formatLine();
    		
    		if(command == "users") //print users command: prints all users cotained in the usersList vector
    		{
    			for(int i = 0; i < usersList.size(); i++)
    			{
    				cout << usersList[i].userName << endl;
    				
    			}
    			cout << endl;
    			if(loggedIn == false)
    			{
    				cout << "Logged in as: N/A" << endl;
    			}
    			else
    			{
    				cout << "Logged in as: " << usersList[position].userName << endl;
    			}
    		}
    		else if(command == "items")//print items command: prints all items cotained in the itemsList vector
    		{
    			for(int i = 0; i < itemsList.size(); i++)
    			{
    				cout << i << ". " << itemsList[i].itemName << endl;
    			}
    			cout << endl;
    			if(loggedIn == false)
    			{
    				cout << "Logged in as: N/A" << endl;
    			}
    			else
    			{
    				cout << "Logged in as: " << usersList[position].userName << endl;
    			}
    		}
    	}
    	else if(command.front() == 'a') //start of add command
    	{
    		command.erase(0,4);
    		
    		formatLine();
    		
    		if(command == "user") //add user command: adds a new user to the main usersList vector
    		{
    			string userName;
    			cout << "Please enter the username: ";
    			getline(cin, userName);
    			
    			Users newUser;
    			
    			newUser.userName = userName;
    			
    			for(int i = 0; i < itemsList.size(); i++)
    			{
    				newUser.ratings.push_back(0);
    			}
    			
    			usersList.push_back(newUser);
    			
    			loggedIn = true;
    			position = usersList.size() - 1;
    			cout << "Logged in as: " << userName << endl;
    		}
    		else if(command == "rating") //add rating: gives the user an option to pick which item they want to rate
    		{
    			if(loggedIn == true)
    			{
    				int itemNum;
    				int rating;
    				
    				string temp;
    				
    				cout << "Item number to add/change rating: ";
    				
    				getline(cin, temp);
    				
    				itemNum = stoi(temp);
    				
    				cout << "Add the rating for " << itemsList[itemNum].itemName << ": ";
    				
    				getline(cin, temp);
    				
    				rating = stoi(temp);
    				
    				usersList[position].ratings[itemNum] = rating;
    				
    				cout << endl << "Logged in as: " << usersList[position].userName << endl;
    				
    			}
    			else
    			{
    				notLoggedInMessage();
    			}
    		}
    		cout << endl;
    		
    	}
    	else if(command == "similarity")
    	{
    		formatLine();
    		
    		int similarity = similarityBetweenAll(usersList, itemsList);
    		
    		cout << "The global similarity given the data is: " << similarity << endl;
    		cout << "For reference a value close to zero means low or no similarity at all." << endl;
    		cout << endl;
    	}
    	else if(command == "#") //exit command: use "#" symbol to exit the program
    	{
    		formatLine(); 
    		cout << endl;
    		cout << "Thank you for using the Recommendations app!" << endl;
    		break;
    	}
    }
    
    return 0;
}
