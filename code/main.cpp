#include "BoothPatron.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "SimClock.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>


using namespace std;

// Declare simulation parameter constants
// Fair parameters
const int FAIR_SIZE = 7;      // Fair size in nodes
const int MIN_WEIGHT = 1;     // Edge weight range
const int MAX_WEIGHT = 5;
const int NUM_BOOTHS = 7;     // For now 1 booth per node, may change eventually 
const int MAX_BOOTHS = 1;     // Maximum booths per node, for future extension


// Booth parameters
string ITEMS[5] = {"apple","jewelry","knicknack","shirt","toy"};
const int ITEM_TYPES = 5;
const int MIN_PRICE = 1;      // Price range for shops
const int MAX_PRICE = 5;
const int MAX_QTY = 3;

// Patron parameters
// Note that patron shopping lists also use the "items" from the booth parameters.
const int NUM_PATRONS = 1;
const int MIN_STEPS = 15;      // Range of steps a patron can have
const int MAX_STEPS = 30;
const int MIN_WALLET = 5;      // Range of money a patron can have
const int MAX_WALLET = 12;
const int MIN_LIST = 1;        // Size of shopping list
const int MAX_LIST = 2;

// Helper functions

// Seed functions
Graph* mkgraph(){
    // For testing purposes, we're making a static graph with 7 nodes
    // Future work may include procedurally generated graphs
    Graph* ret(new Graph());

    Node* a(new Node("a"));
    Node* b(new Node("b"));
    Node* c(new Node("c"));
    Node* d(new Node("d"));
    Node* e(new Node("e"));
    Node* f(new Node("f"));
    Node* g(new Node("g"));

    Edge* ab(new Edge(a,b,2));
    Edge* bc(new Edge(b,c,5));
    Edge* bd(new Edge(b,d,1));
    Edge* ce(new Edge(c,e,4));
    Edge* cf(new Edge(c,f,1));
    Edge* cg(new Edge(c,g,3));
    Edge* ed(new Edge(e,d,2));
    Edge* fg(new Edge(f,g,3));

    ret->addNode(a);
    ret->addNode(b);
    ret->addNode(c);
    ret->addNode(d);
    ret->addNode(e);
    ret->addNode(f);
    ret->addNode(g);

    ret->addEdge(ab);
    ret->addEdge(bc);
    ret->addEdge(bd);
    ret->addEdge(ce);
    ret->addEdge(cf);
    ret->addEdge(cg);
    ret->addEdge(ed);
    ret->addEdge(fg);

    ret->setDirected(false);
    ret->clear();

    return ret; 
}

vector<Booth*> constructBooths(vector<Node*> nodes){
    vector<Booth*> booths;
    for (int i = 0; i < nodes.size(); i++){
        Booth* booth(new Booth(nodes[i], ITEMS, ITEM_TYPES, MIN_PRICE, MAX_PRICE, MAX_QTY));
        booths.push_back(booth);
        nodes[i]->setBooth(booth);
    }
    return booths;
}


vector<Patron*> constructPatrons(int qty){
    vector<Patron*> patrons;
    for (int i = 0; i < qty; i++){
        int wallet = rand() % MAX_WALLET + MIN_WALLET;
        int steps = rand() % MAX_STEPS + MIN_STEPS;
        int strategy = rand() % NUM_STRATS;
        Patron* patron(new Patron(i, wallet, steps, strategy));
        patrons.push_back(patron);
    }
    return patrons;
}

// Output functions
// Prints Overall stats and graph of fair
void printFair(Graph* fair){
    fair->tick("Fair Print");
    return;
}

// Prints all booth ledgers
string exportLedgers(){
    string ret = "";
    return ret;
}

// Prints a patron log
string printLog(Patron* patron){
    string ret = "";
    return ret;
}

int main() {
    // Declare simulation variables
    srand(time(NULL));
    int clock;
    bool patrons_done_shopping = false; // true if all patrons are done.
    int max_ticks = 10;                  // Number of ticks in the simulation.
                                        // Low for now due to testing
    
    // Create fair
    Graph* fair = mkgraph();
    vector<Node*> nodes = fair->getNodes();

    // Seed fair with booths
    // Again for now we are just building one booth per node
    vector<Booth*> booths = constructBooths(fair->getNodes());

    // Create patrons and establish initial positions
    vector<Patron*> patrons = constructPatrons(NUM_PATRONS);
    for (int i = 0; i < patrons.size(); i++){
        int node_seed = rand() % nodes.size();
        patrons[i]->setLocation(nodes[node_seed]);

        // Test print of initial locations
        patrons[i]->updateHistory(0);
        patrons[i]->printLog();
    }

    // Run the simulation
    while ((clock < max_ticks)){
        clock++;
        // Advance each patron based upon strategy
        for (int i = 0; i < patrons.size(); i++){
            set<Edge*> adjacent = fair->getAdjacentEdges(patrons[i]->getLocation());
            patrons[i]->movePatron(fair, adjacent, clock);
        }
        cout << "Tick #" << clock << endl;
    }

    // Write output
    cout << "Simulation complete!" << endl;
    fair->tick("Fair Graph");
    // Write general stats
    // Write booth list and ledgers
    for (int i = 0; i < booths.size(); i++){
        booths[i]->printLog();
    }
    // Write patron activities
    for (int i = 0; i < patrons.size(); i++){
        patrons[i]->printLog();
    }

    
    
    return 0;
}
