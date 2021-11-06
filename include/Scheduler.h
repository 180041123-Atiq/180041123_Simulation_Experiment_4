#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <bits/stdc++.h>
#include "Event.h"

class Scheduler
{
    public:

        void initialize();
        double now();
        void update_clock(double t);
        void add_event(Event e);
        Event remove_event();



    protected:
        double clock = 0.0;
        std::vector<Event> eventList;

    private:

};

#endif // SCHEDULER_H
