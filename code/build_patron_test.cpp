#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Patron.h"
#include "Booth.h"
#include <iostream>
#include <sstream>

using namespace std;

string ITEMS[5] = {"apple","jewelry","knicknack","shirt","toy"};
const int ITEM_TYPES = 5;

int main(){
    Patron* bob = new Patron(1, 10, 30, 1);
    bob->generateList(2, ITEMS, ITEM_TYPES);
    bob->updateHistory(1);
    bob->updateHistory(2);
    bob->print_log();
    return 0;

}