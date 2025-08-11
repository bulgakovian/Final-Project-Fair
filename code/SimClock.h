#ifndef SIMCLOCK_H__
#define SIMCLOCK_H__

using namespace std;

class SimClock {
public:
    SimClock();
    int getTick();
    void tick(int num_ticks = 1);
    void reset();

private:
    int ticks;
};

#endif