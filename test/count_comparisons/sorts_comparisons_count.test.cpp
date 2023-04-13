//
// Created by alexs on 2023-04-09.
//

#include "gtest/gtest.h"
#include "../../src/bencpp.h"
#include "../sorts/bubbleSort.h"
#include "../sorts/cocktailShakerSort.h"

struct SortMetrics {
    size_t comparisons;
    size_t assignments;
    size_t time;
};

typedef std::vector<ComparisonCounter<int>> Data;
typedef std::vector<ComparisonCounter<int>> Output;
typedef SortMetrics Criteria;

class SortSubject : public Subject<Data, Output> {
private:
    std::function<void(Data &)> sort;

public:
    explicit SortSubject(std::function<void(Data &)> sort) : sort(std::move(sort)) {};

    [[nodiscard]] Output run(Data input) const override {
        sort(input);
        return input;
    }
};

class ComparisonResearcher : public Researcher<Data, Output, Criteria> {
public:
    Criteria evaluate(const Subject<Data, Output> *subject) override {
        ComparisonCounter<int>::resetCounters();

        auto sortedArr = subject->run(data);

        return {
                .comparisons = ComparisonCounter<int>::comparisons,
                .assignments = ComparisonCounter<int>::assignments,
                .time = 0
        };
    }
};

TEST(bencpp, sorts_comparisons_count) {
    std::vector<Subject<Data, Output> *> subjects = {new SortSubject(bubbleSort<ComparisonCounter<int>>),
                                                     new SortSubject(cocktailShakerSort<ComparisonCounter<int>>)};

    Researcher<Data, Output, Criteria> *researcher = new ComparisonResearcher();

    Experiment<Data, Output, Criteria> experiment = Experiment(subjects, researcher);

    Data input = { 1, 6, 4, 3, 8, 22, 12, 1, 77, 456, 13 };

    auto results = experiment.run(input);

    for (auto r : results) {
        EXPECT_GT(r.assignments, 0);
        EXPECT_GT(r.comparisons, 0);
    }
}
