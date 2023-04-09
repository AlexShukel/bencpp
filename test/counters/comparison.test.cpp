//
// Created by alexs on 2023-04-09.
//

#include "gtest/gtest.h"
#include "../../src/ComparisonCounter.h"

TEST(operator_counters, comparison) {
    ComparisonCounter<int> a = 1;
    ComparisonCounter<int> b = 1;
    a == b;
    a != b;
    a < b;
    a <= b;
    a > b;
    a >= b;
    a = b;
    EXPECT_EQ(ComparisonCounter<int>::equals, 1);
    EXPECT_EQ(ComparisonCounter<int>::notEquals, 1);
    EXPECT_EQ(ComparisonCounter<int>::lessThan, 1);
    EXPECT_EQ(ComparisonCounter<int>::lessOrEqualThan, 1);
    EXPECT_EQ(ComparisonCounter<int>::greaterThan, 1);
    EXPECT_EQ(ComparisonCounter<int>::greaterOrEqualThan, 1);
    EXPECT_EQ(ComparisonCounter<int>::comparisons, 6);
    EXPECT_EQ(ComparisonCounter<int>::assignments, 1);
}
