#include "BoothPatron.h"

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

void Patron::buyItem(string item, int tick){

}

int Patron::getWallet(){
    return wallet;
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

