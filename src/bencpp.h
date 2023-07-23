//
// Created by alexs on 2023-04-02.
//

#ifndef BENCPP_BENCPP_H
#define BENCPP_BENCPP_H

#include "ArithmeticCounter.h"
#include "ComparisonCounter.h"
#include "Timer.h"
#include <functional>

template<class Input, class Output>
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

    virtual Output run(Input input) = 0;
};

template<class Input, class Output>
class FunctionSubject : public Subject<Input, Output> {
private:
    std::function<Output(Input)> func;

public:
    explicit FunctionSubject(const std::function<Output(Input)> &func) : func(func) {};

    Output run(Input input) override {
        return func(input);
    }
};

template<class Input, class Output, class Criteria>
class Researcher {
private:
    Input input;
    Timer *timer;

protected:
    Input getInput() {
        return input;
    }

    Timer *getTimer() {
        return timer;
    }

public:
    explicit Researcher() : timer(nullptr) {};

    explicit Researcher(Timer *timer) : timer(timer) {};

    virtual ~Researcher() = default;

    virtual Criteria evaluate(Subject<Input, Output> *subject) = 0;

    void setInput(Input newInput) {
        input = newInput;
    }
};

template<class Input, class Output, class Criteria>
class Experiment {
private:
    Timer *timer;
    std::vector<Subject<Input, Output> *> subjects;
    Researcher<Input, Output, Criteria> *researcher;

public:
    Experiment(const std::vector<Subject<Input, Output> *> &subjects,
               Researcher<Input, Output, Criteria> *researcher) : timer(nullptr), subjects(subjects),
                                                                 researcher(researcher) {};

    Experiment(std::function<std::vector<Subject<Input, Output> *>(Timer *)> createSubjects,
               std::function<Researcher<Input, Output, Criteria> *(Timer *)> createResearcher) {
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

    std::vector<Criteria> run(Input input) {
        researcher->setInput(input);
        std::vector<Criteria> result;

        for (Subject<Input, Output> *&subject: subjects) {
            result.push_back(researcher->evaluate(subject));
        }

        return result;
    };
};

#endif //BENCPP_BENCPP_H
