//
// Created by alexs on 2023-04-02.
//

#ifndef BENCPP_BENCPP_H
#define BENCPP_BENCPP_H

#include "ArithmeticCounter.h"
#include "ComparisonCounter.h"
#include <functional>

template<class Data, class Output>
class Subject {
public:
    explicit Subject() = default;

    virtual ~Subject() = default;

    virtual Output run(Data input) const = 0;
};

template<class Data, class Output, class Criteria>
class Researcher {
protected:
    Data data;

public:
    void setData(Data newData) {
        data = newData;
    }

    virtual ~Researcher() = default;

    virtual Criteria evaluate(const Subject<Data, Output> *subject) = 0;
};

template<class Data, class Output, class Criteria>
class Experiment {
private:
    std::vector<Subject<Data, Output> *> subjects;
    Researcher<Data, Output, Criteria> *researcher;

public:
    Experiment() = default;

    explicit Experiment(const std::vector<Subject<Data, Output> *> &subjects,
                        Researcher<Data, Output, Criteria> *researcher) : subjects(subjects),
                                                                          researcher(researcher) {};
    ~Experiment() {
        delete researcher;
        for (auto &subject : subjects) {
            delete subject;
        }
    }

    std::vector<Criteria> run(Data data) {
        researcher->setData(data);
        std::vector<Criteria> result;

        for (Subject<Data, Output> *&subject: subjects) {
            result.push_back(researcher->evaluate(subject));
        }

        return result;
    };
};

#endif //BENCPP_BENCPP_H
