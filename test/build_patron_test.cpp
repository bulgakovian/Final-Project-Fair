#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "BoothPatron.h"
#include <iostream>
#include <sstream>

using namespace std;

string ITEMS[5] = {"apple","jewelry","knicknack","shirt","toy"};
const int ITEM_TYPES = 5;

int main(){
    Node* a(new Node("a"));
    cout << "Node created" << endl;

    Patron* bob = new Patron(1, 10, 30, 1);
    cout << "bob created" << endl;

    bob->generateList(2, ITEMS, ITEM_TYPES);
    cout << "list created" << endl;
    bob->updateHistory(1);
    cout << "history updated" << endl;
    bob->updateHistory(2);
    cout << "history updated 2" << endl;
    bob->printLog();
    return 0;

    Booth* store = new Booth(a);
    cout << "booth created" << endl;


}