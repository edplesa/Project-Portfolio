//  graph.h <Starter Code>
//  Author: Edward Plesa, CS 251, Spring 2021, Proj. 7
//
//  Basic graph class using adjacency matrix representation.  Currently
//  limited to a graph with at most 100 vertices.
//
//  University of Illinois at Chicago
//  CS 251: Spring 2021
//  Project #7 - Openstreet Maps
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;

template<typename VertexT, typename WeightT>

class graph {
 private:
  //
  //  We are using adjacency list implementation
  //
  map<VertexT, map<VertexT, WeightT>> adjList;
  set<VertexT> setOfVertices;
  vector<VertexT> Vertices;
  
  int numVertices;
  int numEdges;
  //
  //  _LookupVertex
  //
  //  Finds the vertex in the Vertices vector and returns
  //  if found, otherwise returns -1.
  //
  int _LookupVertex(VertexT v) const {
  	typename set<VertexT>::iterator it;
  	it = this->setOfVertices.find(v);
    if (it != this->setOfVertices.end()) {
    	return 1;
    }
    // if get here, not found:
    return -1;
  }
  
 public:
  //
  //  constructor:
  //
  //  Constructs an empty graph
  //
  //
  graph() {
    numVertices = 0;
	numEdges = 0;
  }
  //
  //  NumVertices
  //
  //  Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {
    return numVertices;
  }
  //
  //  NumEdges
  //
  //  Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    return numEdges;
  }
  //
  //  addVertex
  //
  //  Adds the vertex v to the graph, and if so
  //  returns true.
  //
  bool addVertex(VertexT v) {
    //
    //  is the vertex already in the graph?  If so, we do not
    //  insert again otherwise Vertices may fill with duplicates:
    //
    if (_LookupVertex(v) >= 0) {
      return false;
    }
    //
    //  if we get here, vertex does not exist so insert.
    //
    this->Vertices.push_back(v);
    this->setOfVertices.insert(v);
    this->adjList.insert(make_pair(v, map<VertexT, WeightT>()));
    numVertices++;
    return true;
  }
  //
  //  addEdge
  //
  //  Adds the edge (from, to, weight) to the graph, and returns
  //  true.  If the vertices do not exist or for some reason the
  //  graph is full, false is returned.
  //
  //  NOTE: if the edge already exists, the existing edge weight
  //  is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    typename set<VertexT>::iterator fromV;
    typename set<VertexT>::iterator toV;
    fromV = setOfVertices.find(from);
    if (fromV == setOfVertices.end()) {
    	return false;
    }
    toV = setOfVertices.find(to);
    if (toV == setOfVertices.end()) {
    	return false;
    }
    typename map<VertexT, map<VertexT, WeightT>>::iterator outitr;
	typename map<VertexT, WeightT>::iterator inneritr;
	outitr = adjList.find(from);
	if (outitr == adjList.end()) { //  check if VertexT is not in the adjList
		adjList.insert(make_pair(from, map<VertexT, WeightT>()));
		adjList[from].insert(make_pair(to, weight));
		numEdges++;
	} else {
		inneritr = adjList[from].find(to);
		if (inneritr != adjList[from].end()) {  //  if 2nd value exists->update
			inneritr->second = weight;
		} else {  //  else: simply add it
			adjList[from].insert(make_pair(to, weight));
			numEdges++;
		}
	}
	return true;
  }
  //
  //  getWeight
  //
  //  Returns the weight associated with a given edge.  If
  //  the edge exists, the weight is returned via the reference
  //  parameter and true is returned.  If the edge does not
  //  exist, the weight parameter is unchanged and false is
  //  returned.
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    typename set<VertexT>::iterator fromV;
    typename set<VertexT>::iterator toV;
    fromV = setOfVertices.find(from);
    if (fromV == setOfVertices.end()) {
    	return false;
    }
    toV = setOfVertices.find(to);
    if (toV == setOfVertices.end()) {
    	return false;
    }
	typename map<VertexT, map<VertexT, WeightT>>::const_iterator outitr;
	typename map<VertexT, WeightT>::const_iterator inneritr;
	outitr = adjList.find(from);
	if (outitr == adjList.end()) {
		return false;
	}
    inneritr = adjList.at(from).find(to);
	if (inneritr == adjList.at(from).end()) {
		return false;
	}
    //
    //  Okay, the edge exists, return the weight via the
    //  reference parameter:
    //
    weight = adjList.at(from).at(to);
    return true;
  }
  //
  //  neighbors
  //
  //  Returns a set containing the neighbors of v, i.e. all
  //  vertices that can be reached from v along one edge.
  //  Since a set is returned, the neighbors are returned in
  //  sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    set<VertexT>  S;
    typename set<VertexT>::iterator foundV;
    foundV = setOfVertices.find(v);
    if (foundV == setOfVertices.end()) {
    	return S;
    }
    for (auto& elem : adjList.at(v)) {
    	S.insert(elem.first);
    }
    return S;
  }
  //
  //  getVertices
  //
  //  Returns a vector containing all the vertices currently in
  //  the graph.
  //
  vector<VertexT> getVertices() const {
    return this->Vertices;  // returns a copy:
  }
  //
  //  dump
  //
  //  Dumps the internal state of the graph for debugging purposes.
  //
  //  Example:
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;
    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;
    output << endl;
    output << "**Vertices:" << endl;
    for (int i = 0; i < this->NumVertices(); ++i) {
      output << " " << i << ". " << this->Vertices[i] << endl;
    }
    for (auto& elem : adjList) {
        output << elem.first << ": ";
        for (auto& elem2 : elem.second) {
            output << "(" << elem.first << ", " << elem2.first <<
            ", " << elem2.second << ") ";
        }
        output << endl;
    }
    output << "**************************************************" << endl;
  }
};
