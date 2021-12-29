//
// Created by mrafi on 12/29/2021.
//

#ifndef FSMIMPL_EVENT_H
#define FSMIMPL_EVENT_H

enum class Event : int {
    Event1 = 1 << 0,
    Event2 = 1 << 1,
    Event3 = 1 << 2,
    Event4 = 1 << 3,
    Event5 = 1 << 4,
    Event6 = 1 << 5,
};


inline Event operator|(Event a, Event b) {
    return static_cast<Event>(static_cast<int>(a) | static_cast<int>(b));
}

inline bool operator&(Event a, Event b) {
    return ((static_cast<int>(a) & static_cast<int>(b)) != 0);
}


#endif//FSMIMPL_EVENT_H
