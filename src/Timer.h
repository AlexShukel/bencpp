//
// Created by alexs on 2023-04-13.
//

#ifndef BENCPP_TIMER_H
#define BENCPP_TIMER_H

#include <chrono>

// TODO: move implementation in cpp file
class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    bool computing = false;

public:
    void start() {
        if (computing) {
            throw std::logic_error("Cannot start a timer when it is already started.");
        }

        startTime = std::chrono::high_resolution_clock::now();
        computing = true;
    }

    void end() {
        if (!computing) {
            throw std::logic_error("Cannot end a timer when it is already ended.");
        }

        endTime = std::chrono::high_resolution_clock::now();
        computing = false;
    }

    double getSeconds() {
        std::chrono::duration<double> diff = endTime - startTime;

        double ans = diff.count();

        return ans;
    }
};

#endif //BENCPP_TIMER_H
