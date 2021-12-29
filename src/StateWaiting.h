//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_STATEWAITING_H
#define FSMIMPL_STATEWAITING_H

#include <iostream>
#include "State.h"


struct Waiting : public State {
    void onEntry() override {
        std::cout << "Waiting onEntry\n";
    }

    void onExit() override {
        std::cout << "Waiting onExit\n";
    }
};
#endif//FSMIMPL_STATEWAITING_H
