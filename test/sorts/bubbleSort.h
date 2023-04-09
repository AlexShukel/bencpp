//
// Created by alexs on 2023-04-02.
// https://github.com/ArtiomTr/sorts
//

#ifndef BENCPP_BUBBLESORT_H
#define BENCPP_BUBBLESORT_H

#include <vector>

template<class T>
void bubbleSort(std::vector<T> &array) {
    bool swapped;
    for (int i = 1; i < array.size(); ++i) {
        swapped = false;

        T rotated_element;
        bool in_rotation = false;

        int j;
        for (j = 0; j < array.size() - i; ++j) {
            bool should_move;

            if (in_rotation) {
                should_move = rotated_element > array[j + 1];
            } else {
                should_move = array[j] > array[j + 1];
            }

            if (should_move) {
                if (!in_rotation) {
                    rotated_element = array[j];

                    in_rotation = true;
                }

                array[j] = array[j + 1];

                swapped = true;
            } else if (in_rotation) {
                array[j] = rotated_element;
                in_rotation = false;
            }
        }

        if (in_rotation) {
            array[j] = rotated_element;
        }

        if (!swapped) {
            break;
        }
    }
}

#endif //BENCPP_BUBBLESORT_H
