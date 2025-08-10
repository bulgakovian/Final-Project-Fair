#ifndef GRAPH_H__
#define GRAPH_H__

#include <iostream>
#include <map>
#include <vector>
#include "LinkedList.h"

using namespace std;

class Graph{
public:
    void addEdge(int x, int y);

private:
 int size;
 vector<LinkedList>* nodes;
};

endif //GRAPH_H__