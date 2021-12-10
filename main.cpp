#include <bitset>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

//enum class Event {
//    EVENT1,
//    EVENT2
//};

#define typeName(y) typeid(y).name()

enum class Events : int {
    Event1,
    Event2
};

struct State {
    virtual void onEntry() = 0;
    virtual void onExit() = 0;
};


class Transition {
public:
    Transition(std::string mCurrentState,
               Events mEvent,
               std::function<void()> action,
               std::string mNextState)

        : mCurrentState(std::move(mCurrentState)),
          mNextState(std::move(mNextState)),
          mEvent(mEvent),
          action(std::move(action)) {}

    std::string mCurrentState;
    std::string mNextState;
    Events mEvent;
    std::function<void()> action;
};

struct State1 : public State {
    void onEntry() override {
        std::cout << "State1 onEntry\n";
    }
    void onExit() override {
        std::cout << "State1 onExit\n";
    }
};

struct State2 : public State {
    void onEntry() override {
        std::cout << "State2 onEntry\n";
    }
    void onExit() override {
        std::cout << "State2 onExit\n";
    }
};


auto pFunction1 = []() {
    std::cout << "Action1() with args = " << "\n";
};

auto pFunction2 = []() {
    std::cout << "Action2() with args = "
              << "\n";
};


class Fsm {
public:
    Fsm() {}

    template<class Event>
    void processEvent(Event event) {
        for (auto &transition: mTransitions) {
            //std::cout << transition.mCurrentState << "   " <<  typeName(*mCurrentState) << "\n";
            if (transition.mEvent == event && transition.mCurrentState == typeName(*mCurrentState)) {
                // process event
                std::shared_ptr<State> &state = mStates[typeName(*mCurrentState)];
                state->onExit();
                transition.action();
                state->onEntry();

                mCurrentState = mStates[transition.mNextState];
            }
        }
    }

private:
    std::map<std::string, std::shared_ptr<State>> mStates{
            {typeName(State1), std::make_shared<State1>()},
            {typeName(State2), std::make_shared<State2>()},
    };

    std::shared_ptr<State> mCurrentState = std::make_shared<State1>();
    std::vector<Transition> mTransitions{
            {typeName(State1), Events::Event1, pFunction1, typeName(State2)},
            {typeName(State2), Events::Event2, pFunction2, typeName(State1)}};
};

int main() {
    Fsm fsm{};
    fsm.processEvent(Events::Event1);

    std::cout << "XXXXXXXXXXX next action\n";

    fsm.processEvent(Events::Event2);
}
