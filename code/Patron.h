#ifndef PATRON_H__
#define PATRON_H__

#include "Node.h"
#include "Booth.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/* 
// Patrons can be in one of 3 states during the simulation:
// 0 - Active    (Will execute strategy on the next step)
// 1 - Done      (Successfuly finished list and exited fair)
// 2 - Exhausted (Out of steps, failed state)
*/
const string P_STATES[] = {"Active","Done","Exhausted"};
const int NUM_STATES = 3;

/* 
// Patrons can have one of 5 strategies:
// 0 - Leaving (All items on list purchased, Patron is leaving fair)
// 1 - Lazy    (Will take the shortest edge with no backtracking)
// 2 - Greedy  (Will purchase any items on list if affordable, cheapest to most expensive)
// 3 - Peek    (Will comparison shop with all adjacent nodes and move to best price)
// 4 - Bargain (Will browse items until they find a price where they can afford entire list)
*/

const string P_STRATS[] = {"Leaving","Lazy","Greedy","Peek","Bargain"};
const int NUM_STRATS = 5;

class Patron {
public:
    Patron(int id, int wallet, int steps, int strategy);
    map<string, bool> generateList(int list_size, string items[], int items_size);
    void movePatron();
    void setLocation(Node* node);
    void strategize(Booth* currentBooth);
    void updateHistory(int tick);
    void print_log();
    
private:
    int id;
    int wallet;
    int steps;
    Node* location;
    Node* previous;
    int state;  
    int strategy;
    map<string, bool> list;
    map<Node*,pair<string,int>> pricemap; //Used only in "Bargain" strategy
    vector<string> history;
    
};

#endif