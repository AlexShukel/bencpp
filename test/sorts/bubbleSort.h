//
// Created by alexs on 2023-04-02.
//

#ifndef BENCPP_BUBBLESORT_H
#define BENCPP_BUBBLESORT_H

#include <vector>

template<class T>
void bubbleSort(std::vector<T> &array) {
    // Flag, indicating if array is already fully sorted.
    bool swapped;
    for (int i = 1; i < array.size(); ++i) {
        swapped = false;

        // Additional element, for the rotation.
        T rotated_element;
        // Flag, indicating, if element is currently in rotation or not.
        bool in_rotation = false;

        int j;
        for (j = 0; j < array.size() - i; ++j) {
            // Flag, indicating if element is not on the right place.
            bool should_move;

            // If currently rotating some element.
            if (in_rotation) {
                should_move = rotated_element > array[j + 1];
            } else {
                should_move = array[j] > array[j + 1];
            }

            // Element is not in right place, should move it.
            if (should_move) {
                // If currently nothing is rotated.
                if (!in_rotation) {
                    // Begin rotation.
                    rotated_element = array[j];

                    in_rotation = true;
                }

                // Move element.
                array[j] = array[j + 1];

                swapped = true;
            } else if (in_rotation) {
                // If currently rotating some element, then end rotation.
                array[j] = rotated_element;
                in_rotation = false;
            }
        }

        // Finalize last rotation.
        if (in_rotation) {
            array[j] = rotated_element;
        }

        if (!swapped) {
            break;
        }
    }
}

#endif //BENCPP_BUBBLESORT_H
