//
// Created by alexs on 2023-04-04.
//

#ifndef BENCPP_COMPARABLECOUNTER_H
#define BENCPP_COMPARABLECOUNTER_H

template<class T>
class ComparableCounter {
protected:
    T value;

public:
    static size_t comparisons;
    static size_t assignments;

    static void resetCounters() {
        comparisons = 0;
        assignments = 0;
    }

    ComparableCounter(): value(0) {};

    ComparableCounter(const T &value): value(value) {};

    // Copy constructor
    ComparableCounter(const ComparableCounter<T> &copy): value(copy.value) {};

    bool operator<(const ComparableCounter<T> &other) {
        ++comparisons;
        return value < other.value;
    }

    bool operator<=(const ComparableCounter<T> &other) {
        ++comparisons;
        return value <= other.value;
    }

    bool operator>(const ComparableCounter<T> &other) {
        ++comparisons;
        return value > other.value;
    }

    bool operator>=(const ComparableCounter<T> &other) {
        ++comparisons;
        return value >= other.value;
    }

    ComparableCounter<T> &operator=(const ComparableCounter<T> &other) {
        ++assignments;
        if (&other != this) {
            this->value = other.value;
        }

        return *this;
    }
};

template<class T>
size_t ComparableCounter<T>::comparisons = 0;

template<class T>
size_t ComparableCounter<T>::assignments = 0;

#endif //BENCPP_COMPARABLECOUNTER_H
