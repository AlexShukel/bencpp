//
// Created by alexs on 2023-04-13.
//

#ifndef BENCPP_TIMER_H
#define BENCPP_TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    bool computing = false;

public:
    void start();

    void end();

    double getSeconds();
};

#endif //BENCPP_TIMER_H
