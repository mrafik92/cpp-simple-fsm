//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_FSM_H
#define FSMIMPL_FSM_H


#include <vector>
#include <map>
#include "Transition.h"
#include "State.h"

#define state(y) typeid(y).name()
#define action(y) std::bind(&Manager::y, this)
#define guard(y) std::bind(&Manager::y, this)

class Fsm {
public:
    explicit Fsm(std::vector<Transition> transition,
                 const std::vector<std::shared_ptr<State>> &states,
                 std::shared_ptr<State> initialState)
        : mTransitions(std::move(transition)),
          mStates(),
          mCurrentState(std::move(initialState))
    {
        for (auto item: states) {
            mStates[state(*item)] = item;
        }
    };

    void processEvent(Event event);

private:
    std::shared_ptr<State> mCurrentState;

    std::map<std::string, std::shared_ptr<State>> mStates;
    std::vector<Transition> mTransitions;
};


#endif//FSMIMPL_FSM_H
