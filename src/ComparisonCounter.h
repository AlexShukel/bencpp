//
// Created by alexs on 2023-04-04.
//

#ifndef BENCPP_COMPARISONCOUNTER_H
#define BENCPP_COMPARISONCOUNTER_H

template<class T>
class ComparisonCounter {
protected:
    T value;

public:
    static size_t lessThan;
    static size_t lessOrEqualThan;
    static size_t greaterThan;
    static size_t greaterOrEqualThan;
    static size_t equals;
    static size_t notEquals;
    // Number of executed operators '<', '<=', '>', '>=', '==', '!='
    static size_t comparisons;
    // Number of executed operators '='
    static size_t assignments;

    static void resetCounters() {
        lessThan = 0;
        lessOrEqualThan = 0;
        greaterThan = 0;
        greaterOrEqualThan = 0;
        equals = 0;
        notEquals = 0;
        comparisons = 0;
        assignments = 0;
    }

    ComparisonCounter() = default;

    ComparisonCounter(const T &value) : value(value) {};

    // Copy constructor
    ComparisonCounter(const ComparisonCounter &copy) : value(copy.value) {};

    bool operator<(const ComparisonCounter &other) const {
        ++lessThan;
        ++comparisons;
        return value < other.value;
    }

    bool operator<=(const ComparisonCounter &other) const {
        ++lessOrEqualThan;
        ++comparisons;
        return value <= other.value;
    }

    bool operator>(const ComparisonCounter &other) const {
        ++greaterThan;
        ++comparisons;
        return value > other.value;
    }

    bool operator>=(const ComparisonCounter &other) const {
        ++greaterOrEqualThan;
        ++comparisons;
        return value >= other.value;
    }

    bool operator==(const ComparisonCounter &other) const {
        ++equals;
        ++comparisons;
        return value == other.value;
    }

    bool operator!=(const ComparisonCounter &other) const {
        ++notEquals;
        ++comparisons;
        return value != other.value;
    }

    ComparisonCounter &operator=(const ComparisonCounter &other) {
        ++assignments;
        if (&other != this) {
            this->value = other.value;
        }

        return *this;
    }
};

template<class T>
size_t ComparisonCounter<T>::lessThan = 0;
template<class T>
size_t ComparisonCounter<T>::lessOrEqualThan = 0;
template<class T>
size_t ComparisonCounter<T>::greaterThan = 0;
template<class T>
size_t ComparisonCounter<T>::greaterOrEqualThan = 0;
template<class T>
size_t ComparisonCounter<T>::equals = 0;
template<class T>
size_t ComparisonCounter<T>::notEquals = 0;
template<class T>
size_t ComparisonCounter<T>::comparisons = 0;
template<class T>
size_t ComparisonCounter<T>::assignments = 0;

#endif //BENCPP_COMPARISONCOUNTER_H
