#include "SimClock.h"



SimClock::SimClock() {
    ticks = 0;
    return;
}

int SimClock::getTick(){
    return ticks;
}

void SimClock::tick(int num_ticks){
    ticks += num_ticks;
    return;
}

void SimClock::reset(){
    ticks = 0;
}
