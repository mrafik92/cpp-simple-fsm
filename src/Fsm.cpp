#include <memory>
#include "Fsm.h"


Fsm::Fsm(std::vector<Transition> transition, const std::vector<std::shared_ptr<State>> &states, std::shared_ptr<State> initialState)
        : mTransitions(std::move(transition)),
          mStates(),
          mCurrentState(std::move(initialState)) {
    for (const auto& item: states) {
        mStates[fsmState(*item)] = item;
    }
}

void Fsm::processEvent(Event event) {
    for (auto &transition: mTransitions) {

        if ((transition.mEvent & event) && transition.mStartState == fsmState(*mCurrentState)) {
            if (transition.mGuard()) {
                // process event

                // 1. exit Current State
                std::shared_ptr<State> &state = mStates[fsmState(*mCurrentState)];
                state->onExit();

                // 2. do fsmAction
                transition.mAction();

                // 3. onEntry of Next State
                mCurrentState = mStates[transition.mNextState];
                mCurrentState->onEntry();
                break;
            }
        }
    }
}
