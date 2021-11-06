#include "Scheduler.h"
#include "Event.h"
#include "Server.h"
#include <list>
#include <iostream>
#include <bits/stdc++.h>

void Scheduler::initialize()
{

}

double Scheduler::now()
{
    return clock;
}

void Scheduler::update_clock(double t)
{
    clock = t;
}

void Scheduler::add_event(Event e)
{
    eventList.push_back(e);
}

Event Scheduler::remove_event()
{
    int index = -1,cnt = 0;

    Event mn;
    mn.end_time = 100000000.0;

    for(auto itr:eventList)
    {
        if(mn.end_time > itr.end_time)
        {
            index = cnt;
            mn = itr;
        }
        cnt++;
    }

    eventList.erase(eventList.begin() + index);

    return mn;
}


