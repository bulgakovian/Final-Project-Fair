#ifndef GRAPH_H__
#define GRAPH_H__

#include "LinkedList.h"
#include "GraphNode.h"
#include <string>
#include <set>
#include <vector>

using namespace std;

class Graph {
public:
    // Basic implementation
    Graph();
    ~Graph();
    vector<LinkedList*> getNodes();
    vector<LinkedList*> getEdges();
    
    // Will not need to remove in this simulation, but consider future extensibility.
    void addNode(GraphNode* node);
    void addEdge(GraphNode* first, Node* second, int weight);
    bool isDirected();
    set<GraphNode*> getAdjacentNodes(GraphNode* node);  // Useful for "peek ahead" and random walk strategies.
    friend std::ostream& operator<<(std::ostream& out, Graph graph);  // overloading << operator to print graph details
    
    // Searching functions
    // Ends current search and resets graph
    void clear();
    // Optional debug after clock ticks
    void tick(string message);
    // Searching for a specific item
    void dfs(GraphNode* start, string item);       
    void bfs(GraphNode* start, string item);       // Searching for a specific item
          
private:
    bool directed;               // This simulation project is always unweighted, but adding for future extensibility
    vector<LinkedList*> nodes;   // All nodes in the graph
    int clock;                   // Used for searching
}

#endif