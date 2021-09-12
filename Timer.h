#ifndef PACMAN_TIMER_H
#define PACMAN_TIMER_H

#include <chrono>

using namespace std;

class Timer {
public:
    Timer();

    void startTimer();

    void stopTimer();

    double getElapsedTime();

    ~Timer();

private:
    chrono::time_point<chrono::steady_clock> start;
    chrono::time_point<chrono::steady_clock> end;
};


#endif //PACMAN_TIMER_H
