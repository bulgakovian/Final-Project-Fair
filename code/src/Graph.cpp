#include "../include/Graph.h"


// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<Node*> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<Edge*> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(Node* n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(Edge* e) {
  // DONE FOR YOU
  edges.push_back(e);
}

void Graph::removeNode(Node* n) {
  // DONE FOR YOU
  for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}

void Graph::removeEdge(Edge* e) {
  // DONE FOR YOU
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node* n) {
  // DONE FOR YOU
  set<Edge*> ret;
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    Edge* edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
  vector<Node*> nodes = this->getNodes();
  for (unsigned int i = 0; i < nodes.size(); i++)
  {
    nodes[i]->clear();
  }
  vector<Edge*> edges = this->getEdges();
  for (unsigned int i = 0; i < edges.size(); i++)
  {
    edges[i]->setType(UNDISCOVERED_EDGE);
  }
  this->clock = 0;
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.

    cout << "// " << message << endl << make_dot(this) << endl;

}

void Graph::dfs(Node* start) {
  start->setColor(GRAY, clock);
  clock++;
  set<Edge*> adjacent = getAdjacentEdges(start);
  for (auto it: adjacent){
    Node* other = it->getEnd();
    int color, dt, ct, r;
    other->getDiscoveryInformation(color,dt,ct,r);
    if (color == WHITE){
      it->setType(TREE_EDGE);
      other->setPredecessor(start);
      dfs(other);
    }
    else if (color == GRAY){it->setType(BACK_EDGE);}
    else if (color == BLACK){
      if (other->isAncestor(start))  {it->setType(FORWARD_EDGE);}
      else                           {it->setType(CROSS_EDGE);}
    }
  }
  start->setColor(BLACK, clock);
  clock++;
}

void Graph::bfs(Node* start) {
  clear();
  start->setColor(GRAY, clock);
  start->setRank(0);
  clock++;
  queue<Node*> to_visit;
  to_visit.push(start);
  while (!to_visit.empty()){
    Node* current = to_visit.front();
    to_visit.pop();
    current->setColor(BLACK, clock);
    clock++;
    set<Edge*> adjacent = getAdjacentEdges(current);
    for (auto it: adjacent){
      Node* other = it->getEnd();
      int color, dt, ct, r;
      other->getDiscoveryInformation(color,dt,ct,r);
      if (color == WHITE){
        other->setColor(GRAY, clock);
        other->setRank(current->getRank() + 1);
        clock++;
        to_visit.push(other);
      }
    }
  }
}

void Graph::bfs(Node* start, Node* finish) {
  clear();
  start->setColor(GRAY, clock);
  start->setRank(0);
  clock++;
  queue<Node*> to_visit;
  to_visit.push(start);
  while (!to_visit.empty()){
    Node* current = to_visit.front();
    to_visit.pop();
    // cout << "Visiting: " << current->getData() << endl;
    if (current == finish){
      current->setColor(BLACK, clock);
      // cout << "Found finish!" << endl << endl;
      clock++;
      return;
    }
    current->setColor(BLACK, clock);
    clock++;
    set<Edge*> adjacent = getAdjacentEdges(current);
    for (auto it: adjacent){
      // cout << "Edge: " << *it << endl;
      Node* other; 
      if (!directed)  {other = it->getOther(current);}
      else            {other = it->getEnd();}
      int color, dt, ct, r;
      other->getDiscoveryInformation(color,dt,ct,r);
      if (color == WHITE){
        other->setColor(GRAY, clock);
        other->setRank(current->getRank() + 1);
        clock++;
        to_visit.push(other);
      }
    }
  }
}


// overloading operator << lets you put a Graph object into an output
// stream.
ostream& operator<<(ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<Node*>::iterator it = graph.nodes.begin();
       it != graph.nodes.end(); it++) {
    Node* n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<Edge*>::iterator it = graph.edges.begin();
       it != graph.edges.end(); it++) {
    Edge* e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness.
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<Node*> nodes = g->getNodes();
  vector<Edge*> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " Fair {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    Node* n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\""
       << textColor << "\" fillcolor=\"" << what(c) << "\""
       << " ]" << endl;
  }

  string edgeColor = "black";
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    Edge* e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData()
       << " [color=\"" << edgeColor << "\" label=\"" << e->getWeight() << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}