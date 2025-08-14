#ifndef PATRON_H__
#define PATRON_H__

#include "Node.h"
#include "Graph.h"
#include "Edge.h"
#include "Booth.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;



/*
//  Patron Class
// 
*/


/* 
// Patrons can be in one of 3 states during the simulation:
// 0 - Active    (Will execute strategy on the next step)
// 1 - Done      (Successfuly finished list)
// 2 - Exhausted (Out of steps, failed state)
*/
const string P_STATES[] = {"Active","Done","Exhausted"};
const int NUM_STATES = 3;

/* 
// Patrons can have one of 3 strategies:
// 0 - Lazy    (Will take the shortest edge with no backtracking)
// 1 - Greedy  (Moves randomly. Will purchase any items on list if can afford)
// 2 - Peek    (Will comparison shop with all adjacent nodes and move to best price)
*/

const string P_STRATS[] = {"Lazy","Greedy","Peek"};
const int NUM_STRATS = 3;

class Patron {
public:
    Patron(int id, int wallet, int steps, int strategy);

    // Spend money and log sale
    void buyItem(string item, int price, int tick);

    // Create a randomized shopping list for patron
    void generateList(int list_size, string items[], int items_size);

    // The heart of the simulation. Controls patron movement.
    void movePatron(Graph* graph, set<Edge*> adjacent, int tick);

    // logging functions
    void printLog();
    void updateHistory(int tick);

    // Get and set functions
    Node* getLocation()             {return location;}
    int getWallet()                 {return wallet;}
    void setLocation(Node* node)    {location = node;}

    
private:
    int id;       
    int wallet;             // Money patron has to spend
    int steps;              // Remaining steps patron will take. 0 or less == exhausted
    Node* location;         // Current location on the map
    Node* previous;         // Last location on the map (used to avoid backtracks)
    int state;              // Current state
    int strategy;           // Shopping strategy
    map<string, bool> list; // List of items the patron wants to buy.
    map<Node*,pair<string,int>> pricemap; //Used only in "Bargain" strategy
    vector<string> history;

    // Movement functions. One for each strategy
    // Strategy steps are detailed in source file comments
    // Each strategy returns a node where the Patron moves
    Node* moveLazy(set<Edge*>  adjacent);
    Node* moveGreedy(set<Edge*>  adjacent);
    Node* movePeek(set<Edge*>  adjacent);
};

#endif