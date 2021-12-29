//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_STATE_H
#define FSMIMPL_STATE_H

struct State {
    virtual void onEntry() = 0;
    virtual void onExit() = 0;
};

#endif//FSMIMPL_STATE_H
