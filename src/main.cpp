#include <iostream>
#include "Fsm.h"
#include "Event.h"
#include "Manager.h"


int main() {
    Manager manager{};
    manager.processEvent(Event::Event1);
    manager.processEvent(Event::Event2);
}
