//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_MANAGER_H
#define FSMIMPL_MANAGER_H

#include <iostream>
#include <memory>

#include "Fsm.h"
#include "StateIdle.h"
#include "StateWaiting.h"

class Manager {

public:
    Manager();

    void processEvent(Event e) {
        fsm.processEvent(e);
    }

private:
    bool passingCondition() {
        std::cout << "passingCondition() true "
                  << "\n";
        return true;
    };

    bool failingCondition() {
        std::cout << "failingCondition() false"
                  << "\n";
        return false;
    };

    void doSomething() {
        std::cout << "doSomething()\n";
    }

    std::vector<std::shared_ptr<State>> mStates{
            std::make_shared<Idle>(),
            std::make_shared<Waiting>()};

    // clang-format off
    std::vector<Transition> mTransitions{
            //Source State      Event                               action                  guard                       Target State
            {state(Idle),       Event::Event1,                      action(doSomething),    guard(failingCondition),    state(Waiting)},
            {state(Idle),       Event::Event1 | Event::Event2,      action(doSomething),    guard(passingCondition),    state(Waiting)},
            {state(Waiting),    Event::Event2 | Event::Event3,      action(doSomething),    guard(passingCondition),    state(Idle)}};
    // clang-format on

    Fsm fsm;
};


#endif//FSMIMPL_MANAGER_H
