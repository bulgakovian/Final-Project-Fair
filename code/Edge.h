#ifndef EDGE_H__
#define EDGE_H__

#include "Node.h"
#include <memory>

using namespace std;

// Edge types are described in the README.
#define UNDISCOVERED_EDGE 9
#define TREE_EDGE 10
#define BACK_EDGE 11
#define FORWARD_EDGE 12
#define CROSS_EDGE 13

class Edge {
private:
  Node* a;  // start node
  Node* b;  // end node
  int type; // one of the edge types defined in graph.hpp
  int weight; // weight of graph edge
public:
  Edge(Node* n1, Node* n2, int weight);
  ~Edge();
  int getType();
  Node* getStart();
  Node* getEnd();
  Node* getOther(Node* current);
  int getWeight();
  friend std::ostream& operator<<(std::ostream& out, Edge edge);

  // Set the edge type to the given value (see edge type #define
  // statements).
  void setType(int edge_type);
};

#endif // EDGE
