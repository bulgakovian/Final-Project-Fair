#include "Booth.h"

Booth::Booth(Node* node){
    location = node;
    return;
};


bool Booth::sellItem(string item){
    return false;
}

void Booth::updateLedger(int tick){
    string sale = "Dummy log tick: ," + to_string(tick) + ",\\n";
    ledger.push_back(sale);
    return;
}

void Booth::printLog(){
    for (int i = 0; i < ledger.size(); i++){
        cout << ledger[i]<< "\\n" << endl;
    }
    return;
}
