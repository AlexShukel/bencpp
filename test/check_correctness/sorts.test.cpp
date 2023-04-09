//
// Created by alexs on 2023-04-02.
//

#include "gtest/gtest.h"
#include "../../src/bencpp.h"
#include "../sorts/bubbleSort.h"
#include "../sorts/cocktailShakerSort.h"
#include <utility>
#include <vector>

TEST(bencpp, ComparableCounter) {
    std::vector<ComparableCounter<int>> data1 = {1, 6, 3, 2, 9, 12, 2, 0, 84};
    bubbleSort(data1);
    EXPECT_GT(ComparableCounter<int>::comparisons, 0);
    EXPECT_GT(ComparableCounter<int>::assignments, 0);

    ComparableCounter<int>::resetCounters();

    EXPECT_EQ(ComparableCounter<int>::comparisons, 0);
    EXPECT_EQ(ComparableCounter<int>::assignments, 0);

    std::vector<ComparableCounter<int>> data2 = {1, 6, 3, 2, 9, 12, 2, 0, 84};
    cocktailShakerSort(data2);
    EXPECT_GT(ComparableCounter<int>::comparisons, 0);
    EXPECT_GT(ComparableCounter<int>::assignments, 0);
}

bool isSorted(const std::vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }

    return true;
}

class SortSubject : public Subject<std::vector<int>, std::vector<int>> {
private:
    std::function<void(std::vector<int> &)> sort;

public:
    explicit SortSubject(std::function<void(std::vector<int> &)> sort) : sort(std::move(sort)) {};

    [[nodiscard]] std::vector<int> run(std::vector<int> input) const override {
        sort(input);
        return input;
    }
};

class SortResearcher : public Researcher<std::vector<int>, std::vector<int>, bool> {
public:
    bool evaluate(const Subject<std::vector<int>, std::vector<int>> *subject) override {
        std::vector<int> sortedArr = subject->run(data);
        return isSorted(sortedArr);
    }
};

TEST(bencpp, simpleExperiment) {
    std::vector<Subject<std::vector<int>, std::vector<int>> *> subjects = {new SortSubject(bubbleSort<int>),
                                                                           new SortSubject(
                                                                                       cocktailShakerSort<int>)};

    Researcher<std::vector<int>, std::vector<int>, bool> *researcher = new SortResearcher();

    Experiment<std::vector<int>, std::vector<int>, bool> experiment(subjects, researcher);

    std::vector<int> arr = {1, 3, 2};
    auto results = experiment.run(arr);

    for (auto r : results) {
        EXPECT_EQ(r, true);
    }
}
