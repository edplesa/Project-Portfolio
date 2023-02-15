//  application.cpp <Starter Code>
//  Edward Plesa, Spring 2021, Proj 7
//
//  University of Illinois at Chicago
//  Spring 2021
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

#define INF numeric_limits<double>::max()

void printBuilding(vector<BuildingInfo> &Buildings, int found) {
	cout << " " << Buildings[found].Fullname << endl;
    cout << " (" << Buildings[found].Coords.Lat << ", " << Buildings[found].Coords.Lon << ")" << endl;
}

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
    } else if ( foundFullS == false && foundAbbrS == false) {
    	return -1;
    }
    return -1;
}

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

bool isVisited(vector<long long> v, long long value) {
  for (unsigned long int i = 0; i < v.size(); i++) {
    if (v[i] == value) {
      return true;
    }
  }
  return false;
}

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
  //  add nodes as vertices in our graph
  for (auto& elem : Nodes) {
  	G.addVertex(elem.first);
  }
  //  add edges in our graph
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
  //  outputting stats:
  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;
  //
  // Navigation from building to building
  //
  string startBuilding, destBuilding;
  cout << "Enter start (partial name or abbreviation), or #> ";
  getline(cin, startBuilding);
  while (startBuilding != "#") {
    cout << "Enter destination (partial name or abbreviation)> ";
    getline(cin, destBuilding);
	int foundStart = buildingFinder(Buildings, startBuilding, 0);
    int foundDest = buildingFinder(Buildings, destBuilding, 1);
    if (foundStart < 0) {
    	cout << "Start building not found" << endl;
    } else if (foundDest < 0) {
    	cout << "Destination building not found" << endl;
    } else {
    	cout << "Starting point:" << endl;
    	printBuilding(Buildings, foundStart);
    	cout << "Destination point:" << endl;
    	printBuilding(Buildings, foundDest);
    	cout << endl << "Nearest start node:" << endl << " ";
    	int wayS = -1;
    	int nodeS = -1;
    	findSmallestNode(Buildings, Footways, Nodes, wayS, nodeS, foundStart);
    	cout << Nodes[Footways[wayS].Nodes[nodeS]].ID << endl;
    	cout << " (" << Nodes[Footways[wayS].Nodes[nodeS]].Lat << ", " <<
    				Nodes[Footways[wayS].Nodes[nodeS]].Lon << ")" << endl;
		cout << "Nearest destination node:" << endl << " ";
		int wayD = -1;
    	int nodeD = -1;
    	findSmallestNode(Buildings, Footways, Nodes, wayD, nodeD, foundDest);
    	cout << Nodes[Footways[wayD].Nodes[nodeD]].ID << endl;
    	cout << " (" << Nodes[Footways[wayD].Nodes[nodeD]].Lat << ", " <<
    				Nodes[Footways[wayD].Nodes[nodeD]].Lon << ")" << endl;
		map<long long, double> distances;
		cout << endl << "Navigating with Dijkstra..." << endl;
		if ( Nodes[Footways[wayS].Nodes[nodeS]].ID ==
										Nodes[Footways[wayD].Nodes[nodeD]].ID) {
			cout << "Distance to dest: 0 miles" << endl << "Path: " <<
					Nodes[Footways[wayD].Nodes[nodeD]].ID<< endl;
		} else {
			map<long long, long long> pred = Dijkstra(G,
							  Nodes[Footways[wayS].Nodes[nodeS]].ID, distances);
			if (distances[Nodes[Footways[wayD].Nodes[nodeD]].ID] == INF) {
				cout << "Sorry, destination unreachable" << endl;
			} else {
				cout << "Distance to dest: ";
				cout << distances[Nodes[Footways[wayD].Nodes[nodeD]].ID] <<
															" miles" << endl;
				cout << "Path: ";
				stack<long long> stack;
				long long next = Nodes[Footways[wayD].Nodes[nodeD]].ID;
				while (pred[next] != 0) {
					stack.push(next);
				  	next = pred[next];
				}
				cout << Nodes[Footways[wayS].Nodes[nodeS]].ID << "->";
				while(stack.size() != 1) {
				   long long top = stack.top();
				   cout << top << "->";
				   stack.pop();
				}
				cout << stack.top();
				stack.pop();
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
