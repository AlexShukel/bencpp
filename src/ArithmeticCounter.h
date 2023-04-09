//
// Created by alexs on 2023-04-09.
//

#ifndef BENCPP_ARITHMETICCOUNTER_H
#define BENCPP_ARITHMETICCOUNTER_H

template<class T>
class ArithmeticCounter {
private:
    T value;

public:
    static size_t addition;
    static size_t subtraction;
    static size_t multiplication;
    static size_t division;
    static size_t modulo;
    static size_t preIncrement;
    static size_t preDecrement;
    static size_t postIncrement;
    static size_t postDecrement;
    static size_t assignments;

    void resetCounters() {
        addition = 0;
        subtraction = 0;
        multiplication = 0;
        division = 0;
        modulo = 0;
        preIncrement = 0;
        preDecrement = 0;
        postIncrement = 0;
        postDecrement = 0;
        assignments = 0;
    }

    ArithmeticCounter(const T &value) : value(value) {};

    // Copy constructor
    ArithmeticCounter(const ArithmeticCounter<T> &copy) : value(copy.value) {};

    ArithmeticCounter &operator=(const ArithmeticCounter &other) {
        ++assignments;
        value = other.value;
        return *this;
    };

    ArithmeticCounter &operator+=(const ArithmeticCounter &other) {
        *this = *this + other;
        return *this;
    };

    ArithmeticCounter operator+(const ArithmeticCounter &other) const {
        ++addition;
        return value + other.value;
    };

    ArithmeticCounter &operator++() {
        ++preIncrement;
        ++value;
        return *this;
    };

    ArithmeticCounter operator++(int) {
        ++postIncrement;
        ArithmeticCounter copy(value);
        value++;
        return copy;
    };

    ArithmeticCounter &operator-=(const ArithmeticCounter &other) {
        ++subtraction;
        ++assignments;
        value -= other.value;
        return *this;
    };

    ArithmeticCounter operator-(const ArithmeticCounter &other) const {
        ++subtraction;
        return value - other.value;
    };

    ArithmeticCounter &operator--() {
        ++preDecrement;
        --value;
        return *this;
    };

    ArithmeticCounter operator--(int) {
        ++postDecrement;
        ArithmeticCounter copy(value);
        value--;
        return copy;
    };

    ArithmeticCounter &operator*=(const ArithmeticCounter &other) {
        ++multiplication;
        ++assignments;
        value *= other.value;
        return *this;
    };

    ArithmeticCounter operator*(const ArithmeticCounter &other) const {
        ++multiplication;
        return value * other.value;
    };

    ArithmeticCounter &operator/=(const ArithmeticCounter &other) {
        ++division;
        ++assignments;
        value /= other.value;
        return *this;
    };

    ArithmeticCounter operator/(const ArithmeticCounter &other) const {
        ++division;
        return value / other.value;
    };

    ArithmeticCounter &operator%=(const ArithmeticCounter &other) {
        ++modulo;
        ++assignments;
        value %= other.value;
        return *this;
    };

    ArithmeticCounter operator%(const ArithmeticCounter &other) const {
        ++modulo;
        return value % other.value;
    };
};

template<class T>
size_t ArithmeticCounter<T>::addition = 0;
template<class T>
size_t ArithmeticCounter<T>::subtraction = 0;
template<class T>
size_t ArithmeticCounter<T>::multiplication = 0;
template<class T>
size_t ArithmeticCounter<T>::division = 0;
template<class T>
size_t ArithmeticCounter<T>::modulo = 0;
template<class T>
size_t ArithmeticCounter<T>::preIncrement = 0;
template<class T>
size_t ArithmeticCounter<T>::preDecrement = 0;
template<class T>
size_t ArithmeticCounter<T>::postIncrement = 0;
template<class T>
size_t ArithmeticCounter<T>::postDecrement = 0;
template<class T>
size_t ArithmeticCounter<T>::assignments = 0;

#endif //BENCPP_ARITHMETICCOUNTER_H
