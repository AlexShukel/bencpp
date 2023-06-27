//
// Created by alexs on 2023-06-27.
//

#include "Timer.h"

void Timer::start() {
    if (computing) {
        throw std::logic_error("Cannot start a timer when it is already started.");
    }

    startTime = std::chrono::high_resolution_clock::now();
    computing = true;
}

void Timer::end() {
    if (!computing) {
        throw std::logic_error("Cannot end a timer when it is already ended.");
    }

    endTime = std::chrono::high_resolution_clock::now();
    computing = false;
}

double Timer::getSeconds() {
    std::chrono::duration<double> diff = endTime - startTime;

    double ans = diff.count();

    return ans;
}
