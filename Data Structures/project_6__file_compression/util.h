//
//  Author: Edward Plesa, Spring 2021, Proj6
//

#pragma once

#include <math.h>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <vector>
#include "hashmap.h"
#include "bitstream.h"

typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

struct HuffmanNode {
    int character;
    int count;
    int order;
    HuffmanNode* zero;
    HuffmanNode* one;
};

//  Helper function which creates a HuffmanNode and returns it
HuffmanNode* getNode(int character, int count, int order,
						HuffmanNode* zero, HuffmanNode* one) {
	HuffmanNode* node = new HuffmanNode();
	node->character = character;
	node->count = count;
	node->order = order;
	node->zero = zero;
	node->one = one;
	return node;
}
//  Helper function which adds each character to the hashmapF
void addToMap(char &found, hashmapF &map) {
	if ( map.containsKey(found) ) {
    	int freq = map.get(found);
    	freq++;
    	map.put(found, freq);
    } else {
    	map.put(found, 1);
    }
}
//
//  *This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) {
    if (node == NULL) return;
    /* first delete both subtrees */
    freeTree(node->zero); 
    freeTree(node->one);
    //  then delete the actual node
    delete node;
}
//
//  *This function build the frequency map.  If isFile is true, then it reads
//  from filename.  If isFile is false, then it reads from a string filename.
//
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
    if (isFile == true) {
    	ifstream infile(filename);
    	if (infile.good()) {
    		char found;
    		while ( infile.get(found) ) {
    			addToMap(found, map);
    		}
    		map.put(PSEUDO_EOF, 1);
    	}
    } else {
    	for (unsigned i = 0; i < filename.length(); i++) {
    		char found = filename.at(i);
    		addToMap(found, map);
    	}
    	map.put(PSEUDO_EOF, 1);
    }
}
//
//  Functor for creating priority queues
//
struct compare {
	bool operator()(HuffmanNode* zero, HuffmanNode* one) {
		if( zero->count == one->count ) {
			return zero->order > one->order;
		} else {
			return zero->count > one->count;
		}
	}
};

//
//  *This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmapF &map) {
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> pq;
	vector<int> keys = map.keys();
    int order = 0;
    for (auto elem : keys) {
    	pq.push(getNode(elem, map.get(elem), order, nullptr, nullptr));
    	order++;
    }
    while (pq.size() != 1) {
    	HuffmanNode* zero = pq.top();
    	pq.pop();
    	HuffmanNode* one = pq.top();
    	pq.pop();
    	int sum = zero->count + one->count;
    	order++;
    	pq.push(getNode(NOT_A_CHAR, sum, order, zero, one));
    }
    HuffmanNode* root = pq.top();
    pq.pop();
    return root;
}

//
//  *Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str,
                       HuffmanNode* prev) {
    if (node == nullptr) {
    	return;
    }
    if (!node->zero && !node->one) {
    	encodingMap[node->character] = str;
    }
    _buildEncodingMap(node->zero, encodingMap, str + "0", nullptr);
    _buildEncodingMap(node->one, encodingMap, str + "1", nullptr);
}

//
//  *This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap;
    _buildEncodingMap(tree, encodingMap, "", nullptr);
    return encodingMap;
}

//
//  *This function encodes the data in the input stream into the output stream
//  using the encodingMap.  This function calculates the number of bits
//  written to the output stream and sets result to the size parameter, which is
//  passed by reference.  This function also returns a string representation of
//  the output file, which is particularly useful for testing.
//
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    string encoded;
    char found;
    while ( input.get(found) ) {
    	encoded+=encodingMap.find(found)->second;
    }
    encoded+=encodingMap.find(PSEUDO_EOF)->second;
    if (makeFile == true) {
    	for (unsigned i = 0; i < encoded.length(); i++) {
    		int bit = 0;
    		bit = (int)encoded[i] - 48;
    		output.writeBit(bit);
    	}
    }
    size = encoded.length();
    return encoded;
}
//
//  *This function decodes the input stream and writes the result to the output
//  stream using the encodingTree.  This function also returns a string
//  representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    string str;
    HuffmanNode* curr = encodingTree;
    int bit = 0;
    while ( !input.eof() ) {
    	bit = input.readBit();
    	if (bit == 0) {
    		curr = curr->zero;
    	} else {
    		curr = curr->one;
    	}
    	if (curr->character == PSEUDO_EOF) {
	    	break;
	    }
    	if (!curr->zero && !curr->one) {
    		str += curr->character;
    		curr = encodingTree;
    	}
    }
    output << str;
    return str;
}
//
//  *This function completes the entire compression process.  Given a file,
//  filename, this function (1) builds a frequency map; (2) builds an encoding
//  tree; (3) builds an encoding map; (4) encodes the file (don't forget to
//  include the frequency map in the header of the output file).  This function
//  should create a compressed file named (filename + ".huf") and should also
//  return a string version of the bit pattern.
//
string compress(string filename) {
    hashmapF frequencyMap;
    HuffmanNode* encodingTree = nullptr;
    hashmapE encodingMap;
    buildFrequencyMap(filename, true, frequencyMap);
    encodingTree = buildEncodingTree(frequencyMap);
    encodingMap = buildEncodingMap(encodingTree);
    ofbitstream output(filename + ".huf");
    ifstream input(filename);
    stringstream ss;
    //  note: << is overloaded for the hashmap class.  super nice!
    ss << frequencyMap;
    output << frequencyMap;  //  add the frequency map to the file
    int size = 0;
    string codeStr = encode(input, encodingMap, output, size, true);
    //  count bytes in frequency map header
    size = ss.str().length() + ceil((double)size / 8);
    output.close();
    ostringbitstream fileContent;
    ifbitstream infile(filename+".huf");
    int count = 1;
    while ( !infile.eof() ) {
    	if (count%9 == 0) {
    		fileContent << " ";
    		count = 1;
    	}
    	int bit = 0;
    	bit = infile.readBit();
    	if (bit == -1) {
    		infile.close();
    		break;
    	}
    	fileContent << bit;
    	count++;
    }
    cout << endl;
    freeTree(encodingTree);
    return fileContent.str();
}
//
//  *This function completes the entire decompression process.  Given the file,
//  filename (which should end with ".huf"), (1) extract the header and build
//  the frequency map; (2) build an encoding tree from the frequency map; (3)
//  using the encoding tree to decode the file.  This function should create a
//  compressed file using the following convention.
//  If filename = "example.txt.huf", then the uncompressed file should be named
//  "example_unc.txt".  The function should return a string version of the
//  uncompressed file.  Note: this function should reverse what the compress
//  function did.
//
string decompress(string filename) {
    hashmapF frequencyMap;
    HuffmanNode* encodingTree = nullptr;
    hashmapE encodingMap;
    size_t pos = filename.find(".huf");
    if ((int)pos >= 0) {
        filename = filename.substr(0, pos);
    }
    pos = filename.find(".");
    string ext = filename.substr(pos, filename.length() - pos);
    filename = filename.substr(0, pos);
    ifbitstream input(filename + ext + ".huf");
    ofstream output(filename + "_unc" + ext);
    input >> frequencyMap;  // get rid of frequency map at top of file
    encodingTree = buildEncodingTree(frequencyMap);
    encodingMap = buildEncodingMap(encodingTree);
    string decodeStr = decode(input, encodingTree, output);
    freeTree(encodingTree);
    return decodeStr;
}
