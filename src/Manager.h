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
        //Source State          Event                               fsmAction                  fsmGuard                       Target State
        {fsmState(Idle),        Event::Event1,                      fsmAction(doSomething),    fsmGuard(failingCondition),    fsmState(Waiting)},
        {fsmState(Idle),        Event::Event1 | Event::Event2,      fsmAction(doSomething),    fsmGuard(passingCondition),    fsmState(Waiting)},
        {fsmState(Waiting),     Event::Event2 | Event::Event3,      fsmAction(doSomething),    fsmGuard(passingCondition),    fsmState(Idle)}
    };
    // clang-format on

    Fsm fsm;
};


#endif//FSMIMPL_MANAGER_H
