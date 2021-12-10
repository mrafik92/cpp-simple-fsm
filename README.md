# cpp-simple-fsm


This is a simple FSM implmentation using C++14 .
It consists of a simple FSM handler that loops on a vector of transitions to determine which state to go to while executing a specific action

The transition class holds all the allowed transitions in the form of 

src_state -> event -> action -> destination_state

![alt text](https://github.com/mrafik92/cpp-simple-fsm/blob/master/doc/design.png?raw=true)
