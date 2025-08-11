#include "Patron.h"
#include <iostream>
#include <string>
#include <utility>


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

void Patron::movePatron(){
    //TODO
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
    
    string activity = "Tick " + to_string(tick) + ": ," 
    + loc + ","
    + to_string(wallet) + ","
    + to_string(steps) + ","
    + P_STRATS[strategy] + ",";

    history.push_back(activity);
    return;
}

void Patron::print_log(){
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

