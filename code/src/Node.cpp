#include "../include/Node.h"



Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

void Node::clear() {
  this->color = WHITE;
  this->discovery_time = -1;
  this->completion_time = -1;
  this->rank = -1;
  this->predecessor = nullptr;
}

void Node::setColor(int search_color, int time) {

  if (search_color == WHITE){
    this->clear();
  }
  else if (search_color == BLACK){
    this->color = BLACK;
    this->completion_time = time;
  }
  else if (search_color == GRAY){
    this->color = GRAY;
    this->discovery_time = time;
  }
}

void Node::getDiscoveryInformation(int& thecolor, int& disco_time,
                                   int& finish_time, int& bfs_rank) {
  thecolor = this->color;
  disco_time = this->discovery_time;
  finish_time = this->completion_time;
  bfs_rank = this->rank;
}

int Node::getRank() {
  return this->rank;
}

bool Node::isAncestor(Node* other) {
  if (this->predecessor != nullptr){
    Node* cursor = this->predecessor;
    while (cursor != nullptr){
      if (cursor == other){
        return true;
      }
      cursor = cursor->predecessor;
    }

  }
  return false;
}

void Node::setPredecessor(Node* other) {
  this->predecessor = other;
}



// overloading operator << lets you put a Node object into an output
// stream.
ostream& operator<<(std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}


