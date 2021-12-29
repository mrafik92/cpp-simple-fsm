//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_FSM_H
#define FSMIMPL_FSM_H


#include "State.h"
#include "Transition.h"
#include <map>
#include <vector>

#define fsmState(y) typeid(y).name()

#define fsmEvent1(e) Event::e
#define fsmEvent2(e1, e2) Event::e1 | fsmEvent1(e2)
#define fsmEvent3(e1, e2, e3) Event::e1 | fsmEvent2(e2, e3)
#define fsmEvent4(e1, e2, e3, e4) Event::e1 | fsmEvent3(e2, e3, e4)

#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME
#define fsmEvent(...) GET_MACRO(__VA_ARGS__, fsmEvent4, fsmEvent3, fsmEvent2, fsmEvent1) \
(__VA_ARGS__)


#define fsmAction(y) [this]() { y(); }
#define fsmGuard(y) [this]() { return y(); }

class Fsm {
public:
    explicit Fsm(std::vector<Transition>,
                 const std::vector<std::shared_ptr<State>> &,
                 std::shared_ptr<State>);

    void processEvent(Event event);

private:
    std::shared_ptr<State> mCurrentState;
    std::map<std::string, std::shared_ptr<State>> mStates;
    std::vector<Transition> mTransitions;
};


#endif//FSMIMPL_FSM_H
