#include "Graph.h"
#include "Node.h"
#include "Edge.h"

using namespace std;

// FWD Declaration
Graph* mkgraph();

int main() {

    Graph* buddy = mkgraph();
    cout << "Hello, world" << endl;
    buddy->tick("Outside creation");





    return 0;
}

Graph* mkgraph() {
  Graph* ret(new Graph());
  Node* a(new Node("a"));
  Node* b(new Node("b"));
  Node* c(new Node("c"));
  Node* d(new Node("d"));
  Node* e(new Node("e"));
  Node* f(new Node("f"));
  Node* g(new Node("g"));

  Edge* ab(new Edge(a, b, 1));
  Edge* ac(new Edge(a, c, 2));
  Edge* bc(new Edge(b, c, 3));
  Edge* ae(new Edge(a, e, 1));
  Edge* ce(new Edge(c, e, 2));
  Edge* cd(new Edge(c, d, 3));
  Edge* dg(new Edge(d, g, 1));
  Edge* eg(new Edge(e, g, 2));
  Edge* df(new Edge(d, f, 3));
  Edge* fb(new Edge(f, b, 1));


  ret->addNode(a);
  ret->addNode(b);
  ret->addNode(c);
  ret->addNode(d);
  ret->addNode(e);
  ret->addNode(f);
  ret->addNode(g);

  ret->addEdge(ab);
  ret->addEdge(ac);
  ret->addEdge(bc);
  ret->addEdge(ae);
  ret->addEdge(ce);
  ret->addEdge(cd);
  ret->addEdge(dg);
  ret->addEdge(eg);
  ret->addEdge(df);
  ret->addEdge(fb);

  ret->setDirected(false);
  ret->clear();
  ret->tick("Graph Constructed");
  return ret;
}