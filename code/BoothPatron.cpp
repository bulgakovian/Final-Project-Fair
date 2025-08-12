#include "BoothPatron.h"

/*
//  Patron Class
// 
*/
const int MINSTEPS = 9999; // Change this if your line weights go above 9999 


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

// Spends money to pay for an item, adds a special line for purchase
void Patron::buyItem(string item, int price, int tick){
    wallet -= price;
    list[item] = true;
    stringstream purchase;
    purchase << tick << "," << location->getData() << ", bought " << item << "," << price << "," << location;
    history.push_back(purchase.str());
}

int Patron::getWallet(){
    return wallet;
}

void Patron::movePatron(Graph* graph, set<Edge*>  adjacent){
    // If done or exhausted do nothing
    if (state > 0) {return;}
    Node* move;
    
    // Move following strategy
    if (strategy == 0)          {move = moveExit(graph, adjacent);}
    else if (strategy == 2)     {move = moveLazy(adjacent);}
    else if (strategy == 3)     {move = moveGreedy(adjacent);}
    else if (strategy == 4)     {move = movePeek(adjacent);}
    else                        {move = moveBargain(graph, adjacent);}
    previous = location;
    location = move;
    if (steps <= 0){
        state = 2;
    }

    // Review shop at location. 


    // Purchase an item conistent with strategy
    return;
}

void Patron::setLocation(Node* node){
    location = node;
}

void Patron::strategize(Booth* currentBooth){
    //TODO
    return;
}

void Patron::updateHistory(int tick){
    string loc = "null";
    if(location) {loc = location->getData();}
    stringstream activity;
    activity << tick <<"," << loc << "," << wallet << "," << steps << ","<< P_STRATS[strategy];
    history.push_back(activity.str());
    return;
}

void Patron::printLog(){
    for (int i = 0; i < history.size(); i++){
        cout << history[i]<< "\\n" << endl;
    }
    return;
}

map<string,bool> Patron::generateList(int list_size, string items[], int items_size){
    map<string,bool> ret;
    for (int i = 0; i < list_size; i++){
        int item = rand() % items_size;
        ret[items[item]] = false; 
    }
    return ret;
}

//  Movement Functions

Node* Patron::moveExit(Graph* graph, set<Edge*>  adjacent){
    // TODO
    return nullptr;
}

// Lazy moves to the easiest edge that is not an immediate backtrack.
Node* Patron::moveLazy(set<Edge*>  adjacent){
    // find the smallest edge
    Node* ret = location;
    // Start us with a weight larger than we know.
    int minsteps = MINSTEPS; // Constant declared above.
    for (auto it: adjacent){

        // Don't backtrack.
        if (it->getOther(location) != previous){
            // Update node. Lazy takes the first instance of a minimum
            if (it->getWeight() < minsteps)
            {
                ret = it->getOther(location);
                minsteps = it->getWeight();
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
    // TODO
    return nullptr;
}

Node* Patron::moveBargain(Graph* graph, set<Edge*> adjacent){
    // TODO
    return nullptr;
}


/*
//  Booth Class
// 
*/


Booth::Booth(Node* node){
    location = node;
    return;
};


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
