//
// Created by alexs on 2023-04-13.
//

#ifndef BENCPP_UTILS_H
#define BENCPP_UTILS_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

void generateRandomArray(std::vector<int> &arr);

void generateUniformDistributionArray(std::vector<int> &arr, int min, int max);

template<class T>
bool isArraySorted(const std::vector<T> &arr) {
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }

    return true;
}

#endif //BENCPP_UTILS_H
