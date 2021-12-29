//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_TRANSITION_H
#define FSMIMPL_TRANSITION_H


#include "Event.h"
#include <functional>
#include <string>

class Transition {
public:
    Transition(std::string mCurrentState,
               Event mEvent,
               std::function<void()> action,
               std::function<bool()> guard,
               std::string mNextState)

        : mStartState(std::move(mCurrentState)),
          mNextState(std::move(mNextState)),
          mEvent(mEvent),
          mAction(action),
          mGuard(std::move(guard)) {
    }

    std::string mStartState;
    std::string mNextState;
    Event mEvent;
    std::function<void()> mAction;
    std::function<bool()> mGuard;
};


#endif//FSMIMPL_TRANSITION_H
