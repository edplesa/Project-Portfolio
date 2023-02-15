//  application.cpp <Starter Code>
//  Edward Plesa, Spring 2021, CS 251, Proj 7
//
//  University of Illinois at Chicago
//  CS 251: Spring 2021
//  Project #7 - Openstreet Maps
//
//  References:
//  TinyXML: https://github.com/leethomason/tinyxml2
//  OpenStreetMap: https://www.openstreetmap.org
//  OpenStreetMap docs:
//    https://wiki.openstreetmap.org/wiki/Main_Page
//    https://wiki.openstreetmap.org/wiki/Map_Features
//    https://wiki.openstreetmap.org/wiki/Node
//    https://wiki.openstreetmap.org/wiki/Way
//    https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <limits>
#include <utility>
#include <queue>
#include <cmath>
#include <stack>

#include "tinyxml2.h"
#include "dist.h"
#include "osm.h"
#include "graph.h"

using namespace std;
using namespace tinyxml2;

#define INF numeric_limits<double>::max()  //  defining INF to use in Dijkstra

//
//  printBuilding: given the Buildings vector and a position, this hashFunction
//  will print the fullname and the coordinates. Used to clean up code.
//
void printBuilding(vector<BuildingInfo> &Buildings, int found) {
	cout << " " << Buildings[found].Fullname << endl;
    cout << " (" << Buildings[found].Coords.Lat << ", " <<
    Buildings[found].Coords.Lon << ")" << endl;
}
//
//  printNodeData: given the Nodes map and Footways vector: this function
//  will print out all the respective node information (ID, Latitude, and
//  Longitude).
//
void printNodeData(vector<FootwayInfo> &Footways,
					map<long long, Coordinates> &Nodes, int wayD, int nodeD) {
	cout << Nodes[Footways[wayD].Nodes[nodeD]].ID << endl;
    cout << " (" << Nodes[Footways[wayD].Nodes[nodeD]].Lat << ", " <<
    				Nodes[Footways[wayD].Nodes[nodeD]].Lon << ")" << endl;
}
//
//  buildGraph: given the Footways vector, the Nodes map, and our graph,
//  populate the edges and vertices of our graph
//
void buildGraph(vector<FootwayInfo> &Footways,
				map<long long, Coordinates> &Nodes,
				graph<long long, double> &G) {
	for (auto& elem : Nodes) {
  		G.addVertex(elem.first);
    }
	for (unsigned long int i = 0; i < Footways.size(); i++) {
  	for (unsigned long int j = 0; j < Footways[i].Nodes.size()-1; j++) {
  		double dist = 0;
  		dist = distBetween2Points(Nodes[Footways[i].Nodes[j]].Lat,
  											Nodes[Footways[i].Nodes[j]].Lon,
  											Nodes[Footways[i].Nodes[j+1]].Lat,
  											Nodes[Footways[i].Nodes[j+1]].Lon);
		G.addEdge(Nodes[Footways[i].Nodes[j]].ID,
						Nodes[Footways[i].Nodes[j+1]].ID, dist);
		G.addEdge(Nodes[Footways[i].Nodes[j+1]].ID,
						Nodes[Footways[i].Nodes[j]].ID, dist);
  	}
  }
}
//
//  buildingFinder: given the Buildings vector and the name of a building this
//  function will:
//
//  1. Search by abbreviation first
//  2. If not found, then search the fullname for a partial match (use .find?).
//
//  If found, return the position where it is found. If neither is found,
//  then we return a negative value.
//
int buildingFinder(vector<BuildingInfo> &Buildings, string &name, int way) {
	bool foundAbbrS = false;
    bool foundFullS = false;
    int found = 0;
    int found2 = 0;
    size_t foundpos;
    for (unsigned long int i = 0; i < Buildings.size(); i++) {
    	foundpos = Buildings[i].Fullname.find(name);
    	if (Buildings[i].Abbrev == name) {
    		foundAbbrS = true;
    		found = i;
    	}
    	if (foundpos != string::npos) {
    		foundFullS = true;
    		found2 = i;
    	}
    }
    if (foundAbbrS == true) {
    	return found;
	} else if (foundFullS == true) {
    	return found2;
    } else if (foundFullS == false && foundAbbrS == false) {
    	return -1;
    }
    return -1;
}
//
//  findSmallestNode: given the Buildings vector, Footways vector, and Nodes
//  map, and its position in the Buildings vector (foundStart): this function
//  will return the smallest node by its position in the Footways vector by the
//  references to "way" and "node".
//
void findSmallestNode(vector<BuildingInfo> &Buildings,
					vector<FootwayInfo> &Footways,
					map<long long, Coordinates> &Nodes, int& way, int& node,
					int &foundStart) {
	double smallest = INF;
	for (unsigned long int i = 0; i < Footways.size(); i++) {
    		for (unsigned long int j = 0; j < Footways[i].Nodes.size(); j++) {
    			double dist = 0;
	    		dist = distBetween2Points(Buildings[foundStart].Coords.Lat,
	    									Buildings[foundStart].Coords.Lon,
	    									Nodes[Footways[i].Nodes[j]].Lat,
	    									Nodes[Footways[i].Nodes[j]].Lon);
				if (dist < smallest) {
					smallest = dist;
					way = i;
					node = j;
				}
    		}
    	}
}

//
//  prioritize: functor for our priority queue in Dijkstra's algo.
//
class prioritize {
 public:
  bool operator()(const pair<long long, double> p1,
					const pair<long long, double> p2) {
    if (p1.second == p2.second) {
      return p1.first > p2.first;
    }
    return p1.second > p2.second;
  }
};
//
//  isVisited: given a vector of vertices and a value: if the value is
//	foundStart in the vector, then we return true else false.
//	Used in Dijkstra's algo.
//
bool isVisited(vector<long long> v, long long value) {
  for (unsigned long int i = 0; i < v.size(); i++) {
    if (v[i] == value) {
      return true;
    }
  }
  return false;
}
//
//  Dijkstra: given a graph G, a starting vertex (startV), and an empty map
//  (distances): this function will perform Dijkstra's algo. to find the
//  shortest weighted path. It will return a map of the predecessors for the
//  vertex and a map of distances containing the shortest distance to each node.
//
map<long long, long long> Dijkstra(graph<long long,double>& G,
							long long startV,
							map<long long, double>& distances) {
  vector<long long>  visited;
  priority_queue<pair<long long, double>,
					vector<pair<long long, double>>, prioritize> pq;
  map<long long, long long> predecessors;
  vector<long long> myVerts;
  myVerts = G.getVertices();  //  all the vertices in the graph
  for (double i = 0; i < myVerts.size(); i++) {
    pq.push(pair<long long, double>(myVerts[i], INF));
    distances[myVerts[i]] = INF;
    predecessors[myVerts[i]] = 0;
  }
  distances[startV] = 0;
  pq.push(pair<long long, double>(startV, 0));  // start V and 0
  while (!pq.empty()) {  //  while we haven't visited all
    //  visit vertex with the min dist
    pair<long long, double> currentV = pq.top();  //  get the min
    pq.pop();  // pop the queue
    if (distances[currentV.first] == INF) {  //  break
      break;
    } else if (isVisited(visited, currentV.first)) {  //  already visited
      continue;
    } else {  // visit
      visited.push_back(currentV.first);
      set<long long> adj;
      adj = G.neighbors(currentV.first);
      for (long long s : adj) {
        double edgeWeight;
        G.getWeight(currentV.first, s, edgeWeight);
        double altPath = currentV.second + edgeWeight;
        if (altPath < distances[s]) {
          distances[s] = altPath;
          predecessors[s] = currentV.first;
          pq.push(pair<long long, double>(s, altPath));
        }
      }
    }
  }
  return predecessors;
}
//
//  printDijkstraPath: given the Nodes map, Footways vector, the position for
//  the start node, and the position for the destination node, this function
//  will create a stack and populate it with the shortest path to the start node
//  and then print it in reverse order.
//
void printDijkstraPath(map<long long, Coordinates> &Nodes,
						vector<FootwayInfo> &Footways,
						map<long long, long long> &pred, int wayD, int nodeD,
						int wayS, int nodeS) {
	cout << "Path: ";
	stack<long long> stack;
	long long next = Nodes[Footways[wayD].Nodes[nodeD]].ID;
	while (pred[next] != 0) {  //  populate stack
		stack.push(next);
	  	next = pred[next];
	}
	cout << Nodes[Footways[wayS].Nodes[nodeS]].ID << "->";
	while(stack.size() != 1) {  //  print the nodes from stack
	   long long top = stack.top();
	   cout << top << "->";
	   stack.pop();
	}
	cout << stack.top();  //  print last node
	stack.pop();  //  pop last node
}

int main() {
  //  maps a Node ID to it's coordinates (lat, lon)
  map<long long, Coordinates>  Nodes;
  //  info about each footway, in no particular order
  vector<FootwayInfo>          Footways;
  //  info about each building, in no particular order
  vector<BuildingInfo>         Buildings;
  XMLDocument                  xmldoc;
  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);
  string def_filename = "map.osm";
  string filename;
  cout << "Enter map filename> ";
  getline(cin, filename);
  if (filename == "") {
    filename = def_filename;
  }
  //
  //  Load XML-based map file
  //
  if (!LoadOpenStreetMap(filename, xmldoc)) {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }
  //
  //  Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);
  //
  //  Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);
  //
  //  Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);
  //
  //  Stats
  //
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());
  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;
  //
  //  Building the graph:
  //
  graph<long long, double> G;
  //
  //  building our graph:
  //
  buildGraph(Footways, Nodes, G);
  //
  //  outputting stats:
  //
  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;
  //
  //  Navigation from building to building
  //
  string startBuilding, destBuilding;
  cout << "Enter start (partial name or abbreviation), or #> ";
  getline(cin, startBuilding);
  while (startBuilding != "#") {
    cout << "Enter destination (partial name or abbreviation)> ";
    getline(cin, destBuilding);
	int foundStart = buildingFinder(Buildings, startBuilding, 0);
    int foundDest = buildingFinder(Buildings, destBuilding, 1);
    if (foundStart < 0) {  //  Start not found
    	cout << "Start building not found" << endl;
    } else if (foundDest < 0) {  //  Destination not found
    	cout << "Destination building not found" << endl;
    } else {  //  Found both
    	cout << "Starting point:" << endl;
    	printBuilding(Buildings, foundStart);
    	cout << "Destination point:" << endl;
    	printBuilding(Buildings, foundDest);
    	cout << endl << "Nearest start node:" << endl << " ";
    	int wayS = -1;
    	int nodeS = -1;
    	//
    	//  Print the full name and Coordinates of the nearest start node
    	//
    	findSmallestNode(Buildings, Footways, Nodes, wayS, nodeS, foundStart);
    	printNodeData(Footways, Nodes, wayS, nodeS);
		cout << "Nearest destination node:" << endl << " ";
		int wayD = -1;
    	int nodeD = -1;
    	//
    	//  Print the full name and Coordinates of the nearest destination node
    	//
    	findSmallestNode(Buildings, Footways, Nodes, wayD, nodeD, foundDest);
    	printNodeData(Footways, Nodes, wayD, nodeD);
		//
		//  Start performing Dijkstra's algo:
		//
		map<long long, double> distances;
		cout << endl << "Navigating with Dijkstra..." << endl;
		if ( Nodes[Footways[wayS].Nodes[nodeS]].ID ==
										Nodes[Footways[wayD].Nodes[nodeD]].ID) {
			//
			//  if start and end node are the same: do not perform Dijkstra
			//  and simply output 0 miles as the shorest distance and path
			//
			cout << "Distance to dest: 0 miles" << endl << "Path: " <<
					Nodes[Footways[wayD].Nodes[nodeD]].ID<< endl;
		} else {
			map<long long, long long> pred = Dijkstra(G,
							  Nodes[Footways[wayS].Nodes[nodeS]].ID, distances);
			if (distances[Nodes[Footways[wayD].Nodes[nodeD]].ID] == INF) {
				//
				//  if the distances map is INF at the desired node: then we
				//  there is no shortest path.
				//
				cout << "Sorry, destination unreachable" << endl;
			} else {  //  else distances does have a shortest path
				cout << "Distance to dest: ";
				cout << distances[Nodes[Footways[wayD].Nodes[nodeD]].ID] <<
															" miles" << endl;
				//
				//  Print the path to the destination
				//
				printDijkstraPath(Nodes, Footways, pred,
									wayD, nodeD, wayS, nodeS);
			}
		}
    }
    cout << endl;
    cout << "Enter start (partial name or abbreviation), or #> ";
    getline(cin, startBuilding);
  }
  cout << "** Done **" << endl;
  return 0;
}
