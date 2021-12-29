//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_MANAGER_H
#define FSMIMPL_MANAGER_H

#include <iostream>
#include "Fsm.h"


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

    void publishHashes() {
        std::cout << "publishHashes()\n";
    }

    void checkifhashesarematching() {
    }

    std::vector<std::shared_ptr<State>> mStates {
            std::make_shared<Idle>(),
            std::make_shared<Waiting>()
    };

    std::vector<Transition> mTransitions{
            //      Source State                         Event                                    action                      Target State
            {state(Idle), Event::Event3, action(publishHashes), guard(failingCondition), state(Waiting)},
            {state(Idle), Event::Event1 | Event::Event2, action(publishHashes), guard(passingCondition), state(Waiting)},
            {state(Waiting), Event::Event2 | Event::Event3, action(publishHashes), guard(passingCondition), state(Idle)}};

    Fsm fsm;



};


#endif//FSMIMPL_MANAGER_H
