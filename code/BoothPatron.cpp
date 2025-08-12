#include "BoothPatron.h"

/*
//  Patron Class
// 
*/

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

void Patron::movePatron(Graph* graph, set<Node*> adjacent){
    // If done or exhausted do nothing
    if (state > 0) {return;}
    
    // Move following strategy
    if (strategy == 0)          {location = moveExit(graph, adjacent);}
    else if (strategy == 2)     {location = moveLazy(adjacent);}
    else if (strategy == 3)     {location = moveGreedy(adjacent);}
    else if (strategy == 4)     {location = movePeek(adjacent);}
    else                        {location = moveBargain(graph, adjacent);}
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

Node* Patron::moveExit(Graph* graph, set<Node*> adjacent){
    // TODO
    return nullptr;
}

Node* Patron::moveLazy(set<Node*> adjacent){
    // TODO
    return nullptr;
}

Node* Patron::moveGreedy(set<Node*> adjacent){
    // TODO
    return nullptr;
}

Node* Patron::movePeek(set<Node*> adjacent){
    // TODO
    return nullptr;
}

Node* Patron::moveBargain(Graph* graph, set<Node*> adjacent){
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
