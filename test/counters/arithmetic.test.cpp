//
// Created by alexs on 2023-04-09.
//

#include "gtest/gtest.h"
#include "../../src/ArithmeticCounter.h"

TEST(operator_counters, arithmetic) {
    ArithmeticCounter<int> a = 1;
    ArithmeticCounter<int> b = 1;

    a = b;
    a += b;
    a + b;
    ++a;
    a++;
    a -= b;
    a - b;
    --a;
    a--;
    a *= b;
    a * b;
    a /= b;
    a / b;
    a %= b;
    a % b;

    EXPECT_EQ(ArithmeticCounter<int>::assignments, 6);
    EXPECT_EQ(ArithmeticCounter<int>::subtraction, 2);
    EXPECT_EQ(ArithmeticCounter<int>::addition, 2);
    EXPECT_EQ(ArithmeticCounter<int>::multiplication, 2);
    EXPECT_EQ(ArithmeticCounter<int>::division, 2);
    EXPECT_EQ(ArithmeticCounter<int>::modulo, 2);
    EXPECT_EQ(ArithmeticCounter<int>::preIncrement, 1);
    EXPECT_EQ(ArithmeticCounter<int>::postIncrement, 1);
    EXPECT_EQ(ArithmeticCounter<int>::preDecrement, 1);
    EXPECT_EQ(ArithmeticCounter<int>::postDecrement, 1);
}
