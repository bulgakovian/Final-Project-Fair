#ifndef BOOTH_H__
#define BOOTH_H__

#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include "Node.h"

using namespace std;


class Booth {
public:
    Booth(Node* node);
    bool sellItem(string item);
    void updateLedger(int tick);
    void printLog();


private:
    int id;
    Node* location;                       // The location of the shop.
    map<string,pair<int,int>> inventory;  // String is item, first int price, second int qty.
    vector<string> ledger;                 // A listing of the shop's sales.
};

#endif