#include <memory>
#include "Fsm.h"


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
