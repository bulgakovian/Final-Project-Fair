

#include "../code/include/Booth.h"
#include "../code/include/Patron.h"
#include "../code/include/Graph.h"
#include "../code/include/Node.h"
#include "../code/include/Edge.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>


using namespace std;

// Declare simulation parameter constants
// Note: there are additional weight and price constants in the Patron source file
// These may need to be updated if you take prices or edge weights to extremes.

// Fair parameters
const int FAIR_SIZE = 7;      // Fair size in nodes
const int MIN_WEIGHT = 1;     // Edge weight range. Reccomend to stay positive
const int MAX_WEIGHT = 5;
const int NUM_BOOTHS = 7;     // For now 1 booth per node, may change eventually 
const int MAX_BOOTHS = 1;     // Maximum booths per node, for future extension
const int TICKS = 15;         // Number of ticks the simulation will run


// Booth parameters
string ITEMS[5] = {"apple","jewelry","knicknack","shirt","toy"};
const int ITEM_TYPES = 5;
const int MIN_PRICE = 1;      // Price range for shops
const int MAX_PRICE = 5;
const int MAX_QTY = 2;        // Maximum inventory of an item

// Patron parameters
// Note that patron shopping lists also use the "items" from the booth parameters.
const int NUM_PATRONS = 20;
const int MIN_STEPS = 12;      // Range of steps a patron can have
const int MAX_STEPS = 20;
const int MIN_WALLET = 5;      // Range of money a patron can have
const int MAX_WALLET = 12;
const int MIN_LIST = 1;        // Size of shopping list
const int MAX_LIST = 3;

// Helper functions

// Seed functions
Graph* mkgraph(){
    // For testing purposes, we're making a static graph with 10 nodes
    // Future work may include procedurally generated graphs
    Graph* ret(new Graph());

    Node* a(new Node("a"));
    Node* b(new Node("b"));
    Node* c(new Node("c"));
    Node* d(new Node("d"));
    Node* e(new Node("e"));
    Node* f(new Node("f"));
    Node* g(new Node("g"));
    Node* h(new Node("h"));
    Node* i(new Node("i"));
    Node* j(new Node("j"));

    Edge* ab(new Edge(a,b,2));
    Edge* ai(new Edge(a,i,3));
    Edge* bc(new Edge(b,c,5));
    Edge* bd(new Edge(b,d,1));
    Edge* bi(new Edge(b,i,1));
    Edge* ce(new Edge(c,e,4));
    Edge* cf(new Edge(c,f,1));
    Edge* cg(new Edge(c,g,3));
    Edge* ch(new Edge(c,h,2));
    Edge* ed(new Edge(e,d,2));
    Edge* fg(new Edge(f,g,3));
    Edge* gh(new Edge(g,h,1));
    Edge* hi(new Edge(h,i,3));
    Edge* hj(new Edge(h,j,2));
    Edge* ij(new Edge(i,j,4));


    ret->addNode(a);
    ret->addNode(b);
    ret->addNode(c);
    ret->addNode(d);
    ret->addNode(e);
    ret->addNode(f);
    ret->addNode(g);
    ret->addNode(h);
    ret->addNode(i);
    ret->addNode(j);


    ret->addEdge(ab);
    ret->addEdge(ai);
    ret->addEdge(bc);
    ret->addEdge(bd);
    ret->addEdge(bi);
    ret->addEdge(ce);
    ret->addEdge(cf);
    ret->addEdge(cg);
    ret->addEdge(ch);
    ret->addEdge(ed);
    ret->addEdge(fg);
    ret->addEdge(gh);
    ret->addEdge(hi);
    ret->addEdge(hj);
    ret->addEdge(ij);

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
        int list_size = rand() % MAX_LIST + 1;
        patron->generateList(list_size, ITEMS, ITEM_TYPES);
        patrons.push_back(patron);
    }
    return patrons;
}


int main() {
    // Declare simulation variables
    srand(time(NULL));
    int clock = 0;
    
    // Create fair
    Graph* fair = mkgraph();
    vector<Node*> nodes = fair->getNodes();

    // Seed fair with booths
    // For now we are just building one booth per node
    cout << endl << "#### INITIAL BOOTH CONDITIONS ####" << endl << endl;
    vector<Booth*> booths = constructBooths(fair->getNodes());

    // Create patrons and establish initial positions
    cout << endl << endl << "#### INITIAL PATRON CONDITIONS ####" << endl << endl;
    vector<Patron*> patrons = constructPatrons(NUM_PATRONS);
    for (int i = 0; i < patrons.size(); i++){
        int node_seed = rand() % nodes.size();
        patrons[i]->setLocation(nodes[node_seed]);

        // Print of initial locations
        patrons[i]->updateHistory(0);
        cout << patrons[i]->printLog();
        cout << endl;
    }

    // Run the simulation
    cout << endl << endl << "#### STARTING SIMULATION ####" << endl << endl;
    while ((clock < TICKS)){
        clock++;
        cout << "Tick " << clock << endl;
        // Advance each patron based upon strategy
        for (int i = 0; i < patrons.size(); i++){
            set<Edge*> adjacent = fair->getAdjacentEdges(patrons[i]->getLocation());
            patrons[i]->movePatron(fair, adjacent, clock);
        }
    }

    // Write output
    cout << endl << "#### SIMULATION COMPLETE! ####" << endl << endl;
    fair->tick("Fair Graph");
    // Write general stats

    // Write booth list and ledgers
    ofstream boothstream("booths.csv");
    for (int i = 0; i < booths.size(); i++){
        boothstream << booths[i]->printLog();
    }
    boothstream.close();

    // Write patron activities
    ofstream patronstream("patrons.csv");
    for (int i = 0; i < patrons.size(); i++){
        patronstream << patrons[i]->printLog();
    }
    patronstream.close();

    
    
    return 0;
}
