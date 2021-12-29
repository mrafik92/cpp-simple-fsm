#include <memory>
#include "Fsm.h"


void Fsm::processEvent(Event event) {
    for (auto &transition: mTransitions) {

        if ((transition.mEvent & event) && transition.mStartState == state(*mCurrentState)) {
            if (transition.mGuard()) {
                // process event
                std::shared_ptr<State> &state = mStates[state(*mCurrentState)];
                state->onExit();
                transition.mAction();
                mCurrentState = mStates[transition.mNextState];
                mCurrentState->onEntry();
                break;
            }
        }
    }
}
