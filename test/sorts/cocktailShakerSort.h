//
// Created by alexs on 2023-04-02.
// https://github.com/ArtiomTr/sorts
//

#ifndef BENCPP_COCKTAILSHAKER_SORT_H
#define BENCPP_COCKTAILSHAKER_SORT_H

#include <vector>

template<class T>
void cocktailShakerSort(std::vector<T> &array) {
    bool swapped;
    do {
        swapped = false;
        for (std::size_t i = 0; i < array.size() - 1; ++i) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

        swapped = false;

        for (std::size_t i = array.size() - 1; i > 0; --i) {
            if (array[i - 1] > array[i]) {
                std::swap(array[i - 1], array[i]);
                swapped = true;
            }
        }
    } while (swapped);
}

#endif //BENCPP_COCKTAILSHAKER_SORT_H
