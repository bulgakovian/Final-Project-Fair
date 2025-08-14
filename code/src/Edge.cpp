#include "../include/Edge.h"


Edge::Edge(Node* n1, Node* n2, int weight) {
  // DONE FOR YOU
  a = n1;
  b = n2;
  this->weight = weight;
}

Edge::~Edge() {
  // "DONE" FOR YOU
}

Node* Edge::getStart() {
  // DONE FOR YOU
  return a;
}

Node* Edge::getEnd() {
  // DONE FOR YOU
  return b;
}

Node* Edge::getOther(Node* current) {
  // Returns self if passed node is not on this edge (also handles self-loops).
  if (a == current){
    return b;
  }
  else if (b == current) {
    return a;
  }
  return current;
}

// Extended for weighted graphs
int Edge::getWeight(){
  return weight;
}


int Edge::getType() {
  // DONE FOR YOU
  return type;
}

void Edge::setType(int edge_type) {
  this->type = edge_type;
}

// overloading operator << lets you put an Edge object into an output stream.
ostream& operator<<(std::ostream& out, Edge edge) {
  // DONE FOR YOU
  out << *edge.a << " -- " << *edge.b;
  return out;
}