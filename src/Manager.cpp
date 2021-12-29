//
// Created by mrafi on 12/29/2021.
//

#include "Manager.h"
Manager::Manager() : fsm(mTransitions, mStates, mStates[0]) {
}
