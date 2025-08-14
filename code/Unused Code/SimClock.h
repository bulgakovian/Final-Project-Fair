#ifndef SIMCLOCK_H__
#define SIMCLOCK_H__

using namespace std;

// SimClock is just a simple object to track ticks in the simluation.
// Mainly written for clarity in the Main function and for future extensibility
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