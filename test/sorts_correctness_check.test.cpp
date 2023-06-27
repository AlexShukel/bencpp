//
// Created by alexs on 2023-04-02.
//

#include "gtest/gtest.h"
#include "bencpp.h"
#include "sorts/bubbleSort.h"
#include "sorts/cocktailShakerSort.h"
#include <utility>
#include <vector>

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

    std::vector<int> run(std::vector<int> input) override {
        sort(input);
        return input;
    }
};

class SortResearcher : public Researcher<std::vector<int>, std::vector<int>, bool> {
public:
    bool evaluate(Subject<std::vector<int>, std::vector<int>> *subject) override {
        std::vector<int> sortedArr = subject->run(getData());
        return isSorted(sortedArr);
    }
};

TEST(bencpp, sorts_correctness_check) {
    std::vector<Subject<std::vector<int>, std::vector<int>> *> subjects = {new SortSubject(bubbleSort<int>),
                                                                           new SortSubject(
                                                                                   cocktailShakerSort<int>)};

    Researcher<std::vector<int>, std::vector<int>, bool> *researcher = new SortResearcher();

    Experiment<std::vector<int>, std::vector<int>, bool> experiment(subjects, researcher);

    std::vector<int> arr = {1, 3, 2};
    auto results = experiment.run(arr);

    for (auto r: results) {
        EXPECT_EQ(r, true);
    }
}
