//
// Created by alexs on 2023-04-02.
//

#ifndef BENCPP_BENCPP_H
#define BENCPP_BENCPP_H

#include "ArithmeticCounter.h"
#include "ComparisonCounter.h"
#include "Timer.h"
#include <functional>

template<class Data, class Output>
class Subject {
private:
    Timer *timer;

protected:
    Timer *getTimer() {
        return timer;
    }

public:
    explicit Subject() : timer(nullptr) {};

    explicit Subject(Timer *timer) : timer(timer) {};

    virtual ~Subject() = default;

    virtual Output run(Data input) = 0;
};

template<class Data, class Output>
class FunctionSubject : public Subject<Data, Output> {
private:
    std::function<Output(Data)> func;

public:
    explicit FunctionSubject(const std::function<Output(Data)> &func) : func(func) {};

    Output run(Data input) override {
        return func(input);
    }
};

template<class Data, class Output, class Criteria>
class Researcher {
private:
    Data data;
    Timer *timer;

protected:
    Data getData() {
        return data;
    }

    Timer *getTimer() {
        return timer;
    }

public:
    explicit Researcher() : timer(nullptr) {};

    explicit Researcher(Timer *timer) : timer(timer) {};

    virtual ~Researcher() = default;

    virtual Criteria evaluate(Subject<Data, Output> *subject) = 0;

    void setData(Data newData) {
        data = newData;
    }
};

template<class Data, class Output, class Criteria>
class Experiment {
private:
    Timer *timer;
    std::vector<Subject<Data, Output> *> subjects;
    Researcher<Data, Output, Criteria> *researcher;

public:
    Experiment(const std::vector<Subject<Data, Output> *> &subjects,
               Researcher<Data, Output, Criteria> *researcher) : timer(nullptr), subjects(subjects),
                                                                 researcher(researcher) {};

    Experiment(std::function<std::vector<Subject<Data, Output> *>(Timer *)> createSubjects,
               std::function<Researcher<Data, Output, Criteria> *(Timer *)> createResearcher) {
        timer = new Timer();
        subjects = createSubjects(timer);
        researcher = createResearcher(timer);
    };

    ~Experiment() {
        delete timer;
        delete researcher;
        for (auto &subject: subjects) {
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
