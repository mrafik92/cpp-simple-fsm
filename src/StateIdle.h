//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_STATEIDLE_H
#define FSMIMPL_STATEIDLE_H

#include "State.h"
#include <iostream>

struct Idle : public State {
    void onEntry() override {
        std::cout << "Idle onEntry\n";
    }

    void onExit() override {
        std::cout << "Idle onExit\n";
    }
};
#endif//FSMIMPL_STATEIDLE_H
