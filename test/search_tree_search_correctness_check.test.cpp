//
// Created by alexs on 2023-04-07.
//

#include "gtest/gtest.h"
#include "bencpp.h"
#include "dataStructures/Avl.hpp"
#include <algorithm>

struct SearchTreeData {
    std::vector<int> array;
    int value = 0;
};

class AvlSubject : public Subject<SearchTreeData, bool> {
public:
    bool run(SearchTreeData data) override {
        Avl<int> avl;
        avl.insertFromVector(data.array);
        bool retVal = avl.has(data.value);
        return retVal;
    }
};

class BstSubject : public Subject<SearchTreeData, bool> {
public:
    bool run(SearchTreeData data) override {
        Bst<int> bst;
        bst.insertFromVector(data.array);
        return bst.has(data.value);
    }
};

class SearchTreeResearcher : public Researcher<SearchTreeData, bool, bool> {
public:
    bool evaluate(Subject<SearchTreeData, bool> *subject) override {
        auto data = getData();

        int valueToFind = data.value;
        bool exists = std::any_of(data.array.begin(), data.array.end(), [valueToFind](int &number) {
            return number == valueToFind;
        });

        bool hasFound = subject->run(data);

        return exists == hasFound;
    }
};

TEST(bencpp, search_tree_search_correctness_check) {
    std::vector<Subject<SearchTreeData, bool>*> subjects = {new AvlSubject(), new BstSubject()};
    Researcher<SearchTreeData, bool, bool> *researcher = new SearchTreeResearcher();
    Experiment<SearchTreeData, bool, bool> experiment = Experiment(subjects, researcher);

    SearchTreeData data1 = {
            .array = {7, 4, 3, 9, 1, 14, 16, 18, 20},
            .value = 16
    };
    std::vector<bool> results1 = experiment.run(data1);
    for (auto res : results1) {
        EXPECT_EQ(res, true);
    }

    SearchTreeData data2 = {
            .array = {7, 4, 3, 9, 1, 14, 16, 18, 20},
            .value = 119
    };
    std::vector<bool> results2 = experiment.run(data1);
    for (auto res : results2) {
        EXPECT_EQ(res, true);
    }
}
