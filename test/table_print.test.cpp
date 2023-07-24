//
// Created by alexs on 2023-07-23.
//

#include "gtest/gtest.h"
#include "bencpp.h"
#include "sorts/bubbleSort.h"
#include "sorts/cocktailShakerSort.h"
#include "utils.h"

#include <functional>

struct SortMetrics {
    size_t comparisons;
    size_t assignments;
    double time;
    bool correct;
};

typedef std::vector<ComparisonCounter<int>> Input;
typedef std::vector<ComparisonCounter<int>> Output;
typedef SortMetrics Criteria;

class SortPrintSubject : public Subject<Input, Output> {
private:
    std::function<void(Input &)> sort;

public:
    SortPrintSubject(std::function<void(Input &)> sort, Timer *timer) : sort(std::move(sort)), Subject(timer) {};

    Output run(Input input) override {
        getTimer()->start();
        this->sort(input);
        getTimer()->end();
        return input;
    }
};

class SortPrintResearcher : public Researcher<Input, Output, Criteria> {
public:
    explicit SortPrintResearcher(Timer *timer) : Researcher(timer) {};

    Criteria evaluate(Subject<Input, Output> *subject) override {
        ComparisonCounter<int>::resetCounters();

        auto sortedArray = subject->run(getInput());

        return {
                .comparisons = ComparisonCounter<int>::comparisons,
                .assignments = ComparisonCounter<int>::assignments,
                .time = getTimer()->getSeconds(),
                .correct = isArraySorted(sortedArray),
        };
    }
};

std::vector<Subject<Input, Output> *> createSubjects(Timer *timer) {
    return {new SortPrintSubject(bubbleSort<ComparisonCounter<int>>, timer),
            new SortPrintSubject(cocktailShakerSort<ComparisonCounter<int>>, timer)};
}

Researcher<Input, Output, Criteria> *createResearcher(Timer *timer) {
    return new SortPrintResearcher(timer);
}

TEST(result_output, print_table) {
    Experiment<Input, Output, Criteria> experiment(createSubjects, createResearcher);

    Input input = {1, 6, 4, 3, 8, 22, 12, 1, 77, 456, 13};

    auto results = experiment.run(input);
}
