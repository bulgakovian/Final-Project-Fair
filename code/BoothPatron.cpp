#include "BoothPatron.h"


/*
//  Patron Class
// 
*/
const int MINSTEPS = 9999; // Change this if your line weights go above 9999
const int MAXPRICE = 9999; // Change this if your items cost more than 9999 


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
    purchase << tick << "," << location->getData() << ", bought " << item << "," << price << "," << location;
    history.push_back(purchase.str());
}

// Creates a shopping list for a patron
// TODO if time - incorporate this into constructor function.
map<string,bool> Patron::generateList(int list_size, string items[], int items_size){
    map<string,bool> ret;
    for (int i = 0; i < list_size; i++){
        bool next = false;
        while (!next){
             // Select an item from the list
             // Right now patrons cannot have duplicate items on list.
            int item = rand() % items_size; 
            if (ret.find(items[item]) == ret.end()){
                ret[items[item]] = false;
                next = true;
            }
        }
    }
    return ret;
}

int Patron::getWallet(){
    return wallet;
}


// Movement selector function. 
// Performs a move and shopping action.
void Patron::movePatron(Graph* graph, set<Edge*>  adjacent, int tick){
    // If done or exhausted do nothing
    if (state > 0) {return;}

    Node* move;
    
    // Move following strategy
    if (strategy == 0)          {move = moveLazy(adjacent);}
    else if (strategy == 1)     {move = moveGreedy(adjacent);}
    
    else if (strategy == 2)     {move = movePeek(adjacent);}
    
    // Move patron, exhaust if needed, update log.
    previous = location;
    location = move;
    if (steps <= 0){
        state = 2;
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
               cout << "Got past sellItem" << endl;
               // One sale unless strategy is Greedy
               if (sold && (strategy != 1)){break;}
            }
        }
    }

    // Update history and state if list completed
    bool list_finished = true;
    for (auto it = list.begin(); it != list.end(); it++){
        if (it->second == false) {list_finished = false;}
    }
    if (list_finished) {state = 1;}
    updateHistory(tick);
    return;
}

Node* Patron::getLocation(){
    return location;
}

void Patron::setLocation(Node* node){
    location = node;
}

void Patron::printLog(){
    cout << "Patron list: "<< endl;
    for (auto it : list){
        cout << it.first << ": " << it.second << endl;
    }
    for (int i = 0; i < history.size(); i++){
        cout << history[i]<< "\\n" << endl;
    }
    return;
}



//  Movement Functions

// Lazy moves to the easiest edge that is not an immediate backtrack.
Node* Patron::moveLazy(set<Edge*>  adjacent){
    // find the smallest edge
    Node* ret = location;
    // Start us with a weight larger than possible in the map.
    int minsteps = MINSTEPS;
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

Node* Patron::movePeek(set<Edge*>  adjacent){
    // Make tracking map
    // Key: item, value:pair of node and price at location
    Node* bargain_node = nullptr;
    int bargain_price = MAXPRICE;
    int bargain_weight;
    // For each edge
    for (auto it = adjacent.begin(); it != adjacent.end(); it++){
        // Look at shop on other side
        Edge* curr_edge = *it;;
        Node* neighbor = curr_edge->getOther(location);
        Booth* booth = neighbor->getBooth();
        booth->printLog();
        map<string,pair<int,int>> curr_inventory = booth->getInventory();

        int curr_weight = curr_edge->getWeight();


        for(auto j = curr_inventory.begin(); j != curr_inventory.end(); j++){        
            // If shop has an item on our list
            if(list.find(j->first) != list.end()){
                // Renaming for clarity
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


void Patron::updateHistory(int tick){
    string loc = "null";
    if(location) {loc = location->getData();}
    stringstream activity;
    activity << tick <<"," << loc << "," << wallet << "," << steps << ","<< P_STRATS[strategy];
    history.push_back(activity.str());
    return;
}


/*
//  Booth Class
// 
*/


Booth::Booth(Node* node, string items[], int size, int min_price, 
                int max_price, int max_qty){
    location = node;
    for (int i = 0; i < size; i++){
        int price = rand() % max_price + min_price;
        int qty = rand() % (max_qty + 1);
        inventory[items[i]] = make_pair(price, qty);
        cout << items[i] << ": $" << price<< ", " << qty << endl;
    }
    return;
};

map<string,pair<int,int>> Booth::getInventory(){
    return inventory;
}


bool Booth::sellItem(Patron* patron, string item, int tick){
    // Item in stock
    if (inventory[item].second > 0){
        // Patron has enough money to buy
        if (patron->getWallet() >= inventory[item].first){
            // Update patron list
            patron->buyItem(item, inventory[item].first, tick);

            // Update shop variables
            income += inventory[item].first;
            inventory[item].second--;
            updateLedger(item,inventory[item].first, inventory[item].second, income, tick);

            return true;
        }
    }
    return false;
}

void Booth::updateLedger(string item, int price, int remain, int reg, int tick){
    stringstream sale;
    sale << tick<< "," << item << "," << price <<"," << remain << ","<< reg;
    ledger.push_back(sale.str());
    return;
}

void Booth::printLog(){
    for (int i = 0; i < ledger.size(); i++){
        cout << ledger[i]<< "\\n" << endl;
    }
    return;
}
