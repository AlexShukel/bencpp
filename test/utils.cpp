//
// Created by alexs on 2023-04-13.
//

#include "utils.h"

void generateRandomArray(std::vector<int> &arr) {
    srand(time(NULL));

    for (int &i: arr) {
        i = rand() % 100;
    }
}

void generateUniformDistributionArray(std::vector<int> &arr, int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    for (int &i: arr) {
        i = dis(gen);
    }
}
