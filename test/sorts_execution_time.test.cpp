//
// Created by alexs on 2023-04-13.
//

#include <iomanip>
#include "gtest/gtest.h"
#include "../src/bencpp.h"
#include "sorts/bubbleSort.h"
#include "sorts/cocktailShakerSort.h"
#include "utils.h"

typedef std::vector<int> Data;
typedef std::vector<int> Output;

class SortTimeSubject : public Subject<Data, Output> {
private:
    std::function<void(std::vector<int> &)> sort;

public:
    explicit SortTimeSubject(std::function<void(std::vector<int> &)> sort, Timer *timer) : sort(std::move(sort)),
                                                                                           Subject(timer) {};

    Output run(Data input) override {
        getTimer()->start();
        sort(input);
        getTimer()->end();
        return input;
    }
};

class SortTimeResearcher : public Researcher<std::vector<int>, std::vector<int>, double> {
public:
    explicit SortTimeResearcher(Timer *timer) : Researcher(timer) {};

    double evaluate(Subject<std::vector<int>, std::vector<int>> *subject) override {
        std::vector<int> sortedArr = subject->run(getData());
        return getTimer()->getSeconds();
    }
};

std::vector<Subject<Data, Output> *> createSubjects(Timer *timer) {
    return {new SortTimeSubject(bubbleSort<int>, timer),
            new SortTimeSubject(cocktailShakerSort<int>, timer)};
}

Researcher<Data, Output, double> *createResearcher(Timer *timer) {
    return new SortTimeResearcher(timer);
}

TEST(bencpp, sorts_execution_time) {
    auto experiment = Experiment<Data, Output, double>(createSubjects, createResearcher);

    std::vector<int> arr;
    arr.resize(1000);
    generateUniformDistributionArray(arr, -100000, 100000);

    auto results = experiment.run(arr);

    for (auto r: results) {
        std::cout << std::fixed << std::setprecision(9) << r << " seconds" << std::endl;
    }
}
