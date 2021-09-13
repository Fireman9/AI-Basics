#include "Timer.h"

Timer::Timer() = default;

void Timer::startTimer() {
    start = chrono::steady_clock::now();
}

void Timer::stopTimer() {
    end = chrono::steady_clock::now();
}

double Timer::getElapsedTime() {
    chrono::duration<double> elapsedTime = end - start;
    return elapsedTime.count();
}

Timer::~Timer() = default;
