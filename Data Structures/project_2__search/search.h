//	Author: Edward Plesa, Project2, Spring 2021
//
//	Program overview: Using the map and set data abstractions, this Program
//	process and indexes a url and its body content in a way which can be used
//	to quickly search for and even specify which words to add to the search
//	or filter out.
//
//
//	Creative component: Stop words removal. Using the list found at
//	:https://github.com/kavgan/stop-words/blob/master/minimal-stop.txt,
//	the command "!removestop" will clear all stop words from the index
//	to better optimize searching and querying.
//
//

#include <iostream>
#include <fstream>
#include <sstream>

#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

//
//	cleanToken takes in a whitespace separated string of characters that appears
//	in the body text and returns a "cleaned" version of that token, ready to be 
//	stored in the index. The cleaned version has trimmed off any leading or
//	trailing punctuation characters and has been converted to lowercase. If the
//	token contains no letters whatsoever, cleanToken returns an empty string to
//	indicate this token is to be discarded entirely.
//
string cleanToken(string s) 
{
    while (ispunct(s[0])) //  remove all leading punct
    {
    	s.erase(0,1);
    }
    
    while (ispunct(s[s.length() - 1])) //  remove all trailing punct
    {
    	s.erase(s.length() - 1, 1);
    }
    
    int count = 0;
    for (unsigned int i = 0; i < s.length(); i++) //  checks if at least one 
   	{											  //  char is alpha
    	if (isalpha(s[i]))
    	{
    		count++;
    	}
    }
    
    if (count == 0) //  return empty string if no alphas in string
    {
    	return "";
    }
    
    string newStr;
    for (unsigned int i = 0; i < s.length(); i++) //  lower case the whole
    {											  //  string
    	newStr += tolower(s[i]);
    }
    return newStr; 
}

//
//  gatherTokens: upon given a line of text containing all keywords for all
//  particular url, the function processes this line using string stringstream
//  and creates a set with these words. This set is then returned.
//
set<string> gatherTokens(string text) 
{
    set<string> tokens;
    stringstream ss(text);
    string str;
    
    while (ss >> str)
    {
    	string newStr = cleanToken(str);
    	if (newStr != "")
    	{
    		tokens.insert(newStr);
    	}
    }
    return tokens; 
}

//  buildIndex: given a filename and an empty map, the function populates
//  the map in the style (keyword, set of urls containing keyword). The number
//	of urls counted is then returned.
//
int buildIndex(string filename, map<string, set<string>>& index)
{
	ifstream infile(filename);
	int urlCount = 0;
    if (!infile.good())
	{
		return 0;
	}
	else
	{
		while (!infile.eof())
		{
			string urlName;
			string keywords;
			
			getline(infile, urlName);
			getline(infile, keywords);
			
			if (!infile.fail())  //  data was successfully input:
    		{
    			set<string> inputData = gatherTokens(keywords); //  tokenize all
    			
    			for (auto keyword : inputData)
    			{
    				index[keyword].insert(urlName); //  insert or add keyword 
    												//  and the url into the set
    			}
				urlCount++;
    		}
		}
	}
    return urlCount;
}

//
//	makeSet: given an index, a user "sentence" to search:
//	this function will go through each first element of the index and check for 
//	any instances of "sentence". If found, then for each of the elements in the 
//	corresponding set is added to the resulting set.
//
set<string> makeSet(map<string, set<string>>& index, string sentence)
{
	set<string> newSet;
	for (auto elem : index)
	{
		if (elem.first == sentence)
		{
			for (auto elem2 : elem.second)
			{
				newSet.insert(elem2);
			}
		}
	}
	return newSet;
}

// 
//	findQueryMatches: given the index and a user input sentence:
//	this function function has 2 cases: 1. If sentence is one wordFound
//	it will build the query and return it immediately. 2. It will parse the
//	sentence and build the query according to the following rules:
//
//	By default when not prefaced with a + or -, the matches are unioned across 
//	search terms. (any result matching either term is included)
//
//	If the user prefaces a search term with +, then matches for this term 
//	are intersected with the existing results. (results must match both terms)
//
//	If the user prefaces a search term with -, then matches for this term are
//	removed from the existing result. (results must match one term without 
//	matching the other)
//
//
set<string> findQueryMatches(map<string, set<string>>& index, string sentence)
{
    set<string> result;
    
    if (!sentence.find(" "))
    {
    	result = makeSet(index, sentence);
    }
    else
    {
    	stringstream ss(sentence);
    	string str;
    	
    	ss >> str;
    	string cleanFirst = cleanToken(str);
    	
    	result = makeSet(index, cleanFirst);
    	
    	while (ss >> str)
    	{
    		string cleanWord = cleanToken(str);
    		set<string> wordFound = makeSet(index, cleanWord);
    		
    		set<string> temp;
    		
    		if (str[0] == '+')
    		{
    			set_intersection(result.begin(), result.end(), 
    						   	 wordFound.begin(), wordFound.end(), 
    							 inserter(temp, temp.begin()));
    		}
    		else if (str[0] == '-')
    		{
    			set_difference(result.begin(), result.end(), 
    						   wordFound.begin(), wordFound.end(), 
    						   inserter(temp, temp.begin()));
    		}
    		else
    		{
    			set_union(result.begin(), result.end(), 
    					  wordFound.begin(), wordFound.end(), 
    					  inserter(temp, temp.begin()));
    		}
    		result = temp;
    	}
    }
    return result;  
}

//
//	removeStop: When give the index that needs to be cleared of stop words:
//	this function will open a file containing a condensed list of common
//	stop words and if found in the index: will clear them from index.
//
void removeStop(map<string, set<string>>& index)
{
	ifstream infile("stopwords.txt");
	if (!infile.good())
	{
		return;
	}
	
	int count = 0;
	while (!infile.eof())
	{
		string stopWord;
		infile >> stopWord;
		
		if (!infile.fail())
		{
			map<string, set<string>>::iterator it;
			it = index.find(stopWord);
			
			if (it != index.end())
			{
				index.erase(it);
				count++;
			}
		}
	}
	cout << "Removed all stop words." << endl;
	cout << "Terms removed from index: " << count << endl;
}

// 
//	searchEngine: This function pulls everything together. Upon receiving
//	user input filename: the function will buildIndex and allow the user 
//	to enter search commands which call findQueryMatches to create the set
//	of urls that correspond to the search. If the user presses enter then
//	we leave the function and the program terminates.
//
void searchEngine(string filename) 
{
    map<string, set<string>> index;
    
    cout << "Stand by while building index..." << endl;
    int urlsFound = buildIndex(filename, index);
    cout << "Indexed " << urlsFound << " pages containing " <<
    		index.size() << " unique terms" << endl << endl;
    
    string command;
    
    while (true)
    {
    	cout << "Enter query sentence (press enter to quit): ";
    	getline(cin, command);
    	
    	if (command == "")
    	{
    		cout << "Thank you for searching!"<< endl;
    		return;
    	}
    	else if (command == "!removestop")
    	{
    		removeStop(index);
    	}
    	else
    	{
    		set<string> query = findQueryMatches(index, command);
    		cout << "Found " << query.size() << " matching pages" << endl;
    		for (auto elem : query)
    		{
    			cout << elem << endl;
    		}
    	}
    	cout << endl;
    }
}
