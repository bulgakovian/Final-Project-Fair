#include "../include/Patron.h"


/*
//  Patron Class
// 
*/
const int MAXWEIGHT = 9999; // Change this if your line weights go above 9999
const int MAXPRICE = 9999; // Change this if your items cost more than 9999 

// Patron strategies. Add or alter as needed.
const int LAZY = 0;
const int GREEDY = 1;
const int PEEK = 2;

// Patron states.
const int ACTIVE = 0;
const int DONE = 1;
const int EXHAUSTED = 2;

Patron::Patron(int id, int wallet, int steps, int strategy){
    this->id = id;
    this->wallet = wallet;
    this->steps = steps;
    this->location = nullptr;
    this->previous = nullptr;
    this->state = 0;
    this->strategy = strategy;
    return;
}

// Spends money to pay for an item, adds a special history line for purchase
void Patron::buyItem(string item, int price, int tick){
    wallet -= price;           // we have already confirmed that the patron can afford the purchase. 
    list[item] = true;
    stringstream purchase;
    purchase << tick << "," << location->getData() << ", bought " << item << "," << price << "," << location->getData();
    history.push_back(purchase.str());
}

// Creates a shopping list for a patron
void Patron::generateList(int list_size, string items[], int items_size){
    for (int i = 0; i < list_size; i++){
        bool next = false;
        while (!next){
            // Select an item from the list
            // Right now patrons cannot have duplicate items on list.
            int item = rand() % items_size; 
            if (list.find(items[item]) == list.end()){
                list[items[item]] = false;
                next = true;
            }
        }
    }
    return;
}



// Movement selector function. 
// This is the "main" patron function and the heart of the simulation.
// It performs a move action first based on strategy. 
// Once the patron has moved, it performs a shopping action.
// Right now this structure means that patrons do not shop at their seed node.
// May decouple these in future versions.
void Patron::movePatron(Graph* graph, set<Edge*>  adjacent, int tick){
    // If done or exhausted do nothing
    if (state > ACTIVE) {return;}
    Node* move;
    
    // Move following strategy
    if (strategy == LAZY)            {move = moveLazy(adjacent);}
    else if (strategy == GREEDY)     {move = moveGreedy(adjacent);}
    else if (strategy == PEEK)       {move = movePeek(adjacent);}
    
    // Move patron, exhaust if needed, update log.
    previous = location;
    location = move;
    if (steps <= 0){
        state = EXHAUSTED;
    }

    // Review shop at location
    // Attempt to purchase an item if available
    // Update state if the Patron's list is finished
    Booth* booth = location->getBooth();
    map<string, pair<int,int>> inventory = booth->getInventory();
    for (auto it = list.begin(); it != list.end(); it++ ){

        // Item needs to be purchased
        if (!it->second){
        
            // Shop has item
            if (inventory.find(it->first) != inventory.end()){
               // Attempt to sell the item
               bool sold = booth->sellItem(this, it->first, tick);

               // Greedy will make multiple purchases
               // Lazy and Peek will only make one purchase
               if (sold && (strategy != GREEDY)){break;}
            }
        }
    }

    // Update history and state if list completed
    bool list_finished = true;
    for (auto it = list.begin(); it != list.end(); it++){
        if (it->second == false) {list_finished = false;}
    }
    if (list_finished) {state = DONE;}
    updateHistory(tick);
    return;
}


// Prints out the patron history as well as identifying statistics
string Patron::printLog(){
    stringstream out;
    out << "Patron #" << id <<"." << endl;
    out << "Strategy: " << P_STRATS[strategy] << "." << endl;
    out << "List: " << endl;
    for (auto it : list){
        out << it.first << ": " << it.second << endl;
    }
    out << "Activity: " << endl;
    out << "Tick,Node,Wallet,Steps" << endl;
    for (int i = 0; i < history.size(); i++){
        out << history[i]<< endl;
    }
    out << "End state: "; 
    if (state == ACTIVE) {out << "ACTIVE" << endl;}
    if (state == DONE) {out << "DONE" << endl;}
    if (state == EXHAUSTED) {out << "EXHAUSTED" << endl;}
    out << endl;
    return out.str();
}



//  MOVEMENT STRATEGY FUNCTIONS

// Lazy moves to the easiest edge that is not an immediate backtrack.
Node* Patron::moveLazy(set<Edge*>  adjacent){
    Node* ret = location;

    // Start us with a weight larger than possible in the map.
    int minsteps = MAXWEIGHT;
    for (auto it: adjacent){
        Edge* edge = it;
        // Don't backtrack.
        if (edge->getOther(location) != previous){

            // Update node. Lazy takes the first instance of a minimum
            if (edge->getWeight() < minsteps)
            {
                ret = edge->getOther(location);
                minsteps = edge->getWeight();
            }
        }
    }
    steps -= minsteps;
    return ret;
}

// Greedy moves randomly.
Node* Patron::moveGreedy(set<Edge*> adjacent){
    // select a random edge
    auto it = adjacent.begin();
    advance(it, rand() % adjacent.size());
    Edge* selected = *it;

    // Find next location  and update steps
    Node* ret = selected->getOther(location);
    steps -= selected->getWeight();
    return ret;
}

// Peek patrons review the inventory 
Node* Patron::movePeek(set<Edge*>  adjacent){
    // Make tracking variables to find best deal
    Node* bargain_node = nullptr;
    int bargain_price = MAXPRICE;
    int bargain_weight;

    // For each edge
    for (auto it = adjacent.begin(); it != adjacent.end(); it++){
        // Look at shop on other side
        Edge* curr_edge = *it;
        Node* neighbor = curr_edge->getOther(location);
        Booth* booth = neighbor->getBooth();
        map<string,pair<int,int>> curr_inventory = booth->getInventory();
        int curr_weight = curr_edge->getWeight();

        //Iterate through shop's inventory
        for(auto j = curr_inventory.begin(); j != curr_inventory.end(); j++){        
           
            // If shop sells an item on our ilist and it is in stock
            if((list.find(j->first) != list.end()) && (j->second.second > 0) ){
                int booth_price = j->second.first;
            
                // Check its price and log location/price if lower
                if (booth_price < bargain_price){
                    bargain_node = neighbor;
                    bargain_price = booth_price;
                    bargain_weight = curr_weight;
                }
            }
        }
    }

    // Fallback, move randomly if no items on list available
    if (bargain_node == nullptr){
        return moveGreedy(adjacent);
    }
    // Otherwise move to the bargain node
    steps -= bargain_weight;
    return bargain_node;
}

// Records the history of each move for the patron.
void Patron::updateHistory(int tick){
    string loc = "null";
    if(location) {loc = location->getData();}
    stringstream activity;
    activity << tick <<"," << loc << "," << wallet << "," << steps;
    history.push_back(activity.str());
    return;
}


