#include <bitset>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#define state(y) typeid(y).name()

struct State {
    virtual void onEntry() = 0;
    virtual void onExit() = 0;
};


enum class Events : int {
    Event1 = 1 << 0,
    ReceivedHashesAck = 1 << 1,
    Event2 = 1 << 2,
    Event3 = 1 << 3,
    Event4 = 1 << 4,
    Event5 = 1 << 5,
    Event6 = 1 << 6,
};

class Manager {
public:
    void publishHashes() {
        std::cout << "publishHashes()\n";
    };
    void checkifhashesarematching() {
    }
} mManager;


class Transition {
public:
    Transition(std::string mCurrentState,
               Events mEvent,
               void (Manager::*action)(),
               std::function<bool()> guard,
               std::string mNextState)

        : mStartState(std::move(mCurrentState)),
          mNextState(std::move(mNextState)),
          mEvent(mEvent),
          mAction(std::move(std::bind(action, mManager))),
          mGuard(std::move(guard)) {
    }

    std::string mStartState;
    std::string mNextState;
    Events mEvent;
    std::function<void()> mAction;
    std::function<bool()> mGuard;
};

struct Idle : public State {
    void onEntry() override {
        std::cout << "Idle onEntry\n";
    }

    void onExit() override {
        std::cout << "Idle onExit\n";
    }
};

struct InhibitWaiting : public State {
    void onEntry() override {
        std::cout << "InhibitWaiting onEntry\n";
    }

    void onExit() override {
        std::cout << "InhibitWaiting onExit\n";
    }
};


inline Events operator|(Events a, Events b) {
    return static_cast<Events>(static_cast<int>(a) | static_cast<int>(b));
}

inline bool operator&(Events a, Events b) {
    return ((static_cast<int>(a) & static_cast<int>(b)) != 0);
}


auto transitFromState1ToState2 = []() {
    std::cout << "transitFromState1ToState2() "
              << "\n";
};

auto NO_ACTION = []() {
    std::cout << "NO_ACTION() "
              << "\n";
};

auto allHashesAreMatching = []() {
    std::cout << "allHashesAreMatching() true "
              << "\n";
    return true;
};

auto notAllHashesAreMatching = []() {
    std::cout << "notAllHashesAreMatching() false"
              << "\n";
    mManager.checkifhashesarematching();
    return false;
};

auto pFunction2 = []() {
    std::cout << "Action2() "
              << "\n";
};


class Fsm {
public:
    Fsm() {}

    template<class Event>
    void processEvent(Event event) {
        for (auto &transition: mTransitions) {

            // void (Manager::*pFunction)() = &Manager::checkifhashesarematching;

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

private:
    Manager mHashesManager{};

    std::map<std::string, std::shared_ptr<State>> mStates{
            {state(Idle), std::make_shared<Idle>()},
            {state(InhibitWaiting), std::make_shared<InhibitWaiting>()},
    };

    std::shared_ptr<State> mCurrentState = std::make_shared<Idle>();
    std::vector<Transition> mTransitions{
            //      Source State                         Event                                    action                      Target State
            {state(Idle), Events::ReceivedHashesAck, &Manager::publishHashes, notAllHashesAreMatching, state(InhibitWaiting)},
            {state(Idle), Events::Event1 | Events::Event2, &Manager::publishHashes, allHashesAreMatching, state(InhibitWaiting)},
            {state(InhibitWaiting), Events::Event2 | Events::Event3, &Manager::publishHashes, allHashesAreMatching, state(Idle)}
    };
};

int main() {
    Fsm fsm{};
    fsm.processEvent(Events::Event1);
    fsm.processEvent(Events::Event2);
}
