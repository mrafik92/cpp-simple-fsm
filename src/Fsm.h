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
#define fsmAction(y) [this]() { y(); }
#define fsmGuard(y) [this]() { return y(); }

class Fsm {
public:
    explicit Fsm(std::vector<Transition> transition,
                 const std::vector<std::shared_ptr<State>> &states,
                 std::shared_ptr<State> initialState)
        : mTransitions(std::move(transition)),
          mStates(),
          mCurrentState(std::move(initialState)) {
        for (auto item: states) {
            mStates[fsmState(*item)] = item;
        }
    };

    void processEvent(Event event);

private:
    std::shared_ptr<State> mCurrentState;

    std::map<std::string, std::shared_ptr<State>> mStates;
    std::vector<Transition> mTransitions;
};


#endif//FSMIMPL_FSM_H
