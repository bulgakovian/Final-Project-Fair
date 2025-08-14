#ifndef BOOTH_H__
#define BOOTH_H__

#include "Node.h"
#include "Graph.h"
#include "Edge.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <vector>


/*
//  Booth Class
// 
*/
class Patron;


class Booth {
public:
    Booth(Node* node, string items[], int size, int min_price, 
                int max_price, int max_qty);
    // Returns true if shop has an item and patron can afford the price,
    // false otherwise
    bool sellItem(Patron* patron, string item, int tick);
   
    // Prints a log of every sale at the location.
    void printLog();

    // Get and set functions
    map<string,pair<int,int>> getInventory()    {return inventory;}
    Node* getLocation()                         {return location;}


private:
    int id;
    Node* location;                        // The location of the shop.
    int income;                            // Amount of money made.
    map<string,pair<int,int>> inventory;   // String is item, first int price, second int qty.
    vector<string> ledger;                 // A listing of the shop's sales.
    
    // Logs every successful sale
    void updateLedger(string item, int price, int remain, int reg, int tick);
};

#endif