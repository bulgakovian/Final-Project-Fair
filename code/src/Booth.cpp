#include "../include/Booth.h"
#include "../include/Patron.h"


/*
//  Booth Class
// 
*/


Booth::Booth(Node* node, string items[], int size, int min_price, 
                int max_price, int max_qty){
    location = node;
    cout << "Booth " << location->getData() << ":" << endl;
    for (int i = 0; i < size; i++){
        int price = rand() % max_price + min_price;
        int qty = rand() % (max_qty + 1);
        inventory[items[i]] = make_pair(price, qty);
        cout << items[i] << ": $" << price<< ", " << qty << endl;
    }
    cout << endl;
    return;
};

// Checks that a requested item is in stock and that the patron can afford it
// If they can, asks the patron to buy the item and updates shop variables.
bool Booth::sellItem(Patron* patron, string item, int tick){
    // Item in stock
    if (inventory[item].second > 0){
        // Patron has enough money to buy
        if (patron->getWallet() >= inventory[item].first){
            // Update patron list and shop varibles
            patron->buyItem(item, inventory[item].first, tick);
            income += inventory[item].first;
            inventory[item].second--;
            updateLedger(item,inventory[item].first, inventory[item].second, income, tick);

            return true;
        }
    }
    return false;
}

// Records sales ledger for history
void Booth::updateLedger(string item, int price, int remain, int reg, int tick){
    stringstream sale;
    sale << tick << "," << item << "," << price <<"," << remain << ","<< reg;
    string final = sale.str();
    ledger.push_back(final);
    return;
}

// Prints out the Booth sale history as well as identifying statistics
string Booth::printLog(){
    stringstream out;
    out << "Booth at node " << getLocation()->getData() << endl;
    out << "Final income: " << income << endl;
    out << "Tick,Item,Price,Remaining,Income" << endl;
    for (int i = 0; i < ledger.size(); i++){
        out << ledger[i]<< endl;
    }
    out << endl;
    return out.str();
}