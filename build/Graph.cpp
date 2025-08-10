#include "Graph.h"


void Graph::Graph(int size){
    this->size = size;
    nodes = new vector<LinkedList>[size];
    
}

void Graph::~Graph(){
    delete nodes;
}

void Graph::addEdge(int x, int y){
    nodes[x].push_back(y);
    nodes[y].push_back(x);
}