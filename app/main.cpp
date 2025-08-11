#include "../code/BoothPatron.h"
#include "../code/Graph.h"
#include "../code/Node.h"
#include "../code/Edge.h"
#include "../code/Patron.h"
#include "../code/SimClock.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


using namespace std;

// Helper functions

// Seed functions


// Output functions
// Prints Overall stats and graph of fair
void printFair(Graph* fair){
    return;
}

// Prints a booth ledger
void printLedger(Booth* booth){
    return;
}

// Prints a patron log
void printLog(Patron* patron){
    return;
}

int main() {
    // Declare simulation parameter constants
    // Fair parameters
    const int FAIR_SIZE = 6;      // Fair size in nodes
    const int EXITS = 2;          // Number of fair exits
    const int MIN_WEIGHT = 1;     // Edge weight range
    const int MAX_WEIGHT = 5;
    const int NUM_BOOTHS = 6;     // For now 1 booth per node, may change eventually 
    const int MAX_BOOTHS = 1;     // Maximum booths per node, for future extension
    
    // Booth parameters
    string ITEMS[5] = {"apple","jewelry","knicknack","shirt","toy"};
    const int ITEM_TYPES = 5;
    const int MIN_PRICE = 1;      // Price range for shops
    const int MAX_PRICE = 5;
    const int QTY_MAX = 3;
    
    // Patron parameters
    // Note that patron shopping lists also use the "items" from the booth parameters.
    const int MIN_STEPS = 15;      // Range of steps a patron can have
    const int MAX_STEPS = 30;
    const int MIN_WALLET = 5;      // Range of money a patron can have
    const int MAX_WALLET = 12;
    const int MIN_LIST = 1;        // Size of shopping list
    const int MAX_LIST = 2;
    
    // Declare simulation variables
    int max_ticks = 50;            // Number of ticks in the simulation.
    
    // Create fair
    
    // Seed fair with booths
    
        // create shop inventory
    
    // Create patrons and establish initial positions
    
        // Create wallet, steps, and shopping list
        // Create state and strategy
        // Seed initial position
    
    // Run the simulation
        // For each tick
        // Advance each patron based upon strategy
        // Shop if needed
    
    // Write output
        // Write general stats
        // Write fair graph
        // Write booth list and ledgers
        // Write patron activities
    
    return 0;
}
