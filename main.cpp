#include <bits/stdc++.h>
#include "Event.h"
#include "Scheduler.h"
#include "Item.h"
#include "Queue.h"
#include "Scenario.h"

using namespace std;

class Event_s{
    public:
    double start_time = 0.0;
    double end_time = 0.0;
    int type = 0;
};

bool sortoftwo(const Event_s &a,
               const Event_s &b)
{
    return (a.end_time < b.end_time);
}

int main()
{
    //1st testing block
    {
        /*Event obj,obj1,obj2;

        obj.start_time = 10;
        obj.end_time = 15;
        obj.type = 0;

        obj1.start_time = 15;
        obj1.end_time = 18;
        obj1.type = 1;

        obj2.start_time = 18;
        obj2.end_time = 23;
        obj2.type = 0;

        Scheduler sch,sch1,sch2;

        sch.add_event(obj);
        sch1.add_event(obj1);
        sch2.add_event(obj2);

        sch.run();*/

        /*Item obj,obj1,obj2,obj3;

        obj.id = 1;
        obj1.id = 2;
        obj2.id = 3;
        obj3.id = 4;

        Queue q1,q2,q3;

        q1.static_enque_(obj);
        q2.static_enque_(obj);

        cout<<q3.static_size_()<<'\n';*/
    }

    //2nd testing block
    {
        /*Event_s obj1,obj2,obj3,obj4;

        obj1.start_time = 10.1;
        obj1.end_time = 4.3;
        obj1.type = 1;

        obj2.start_time = 10.1;
        obj2.end_time = 100.78;
        obj2.type = 2;

        obj3.start_time = 10.1;
        obj3.end_time = 23.93;
        obj3.type = 3;

        obj4.start_time = 10.1;
        obj4.end_time = 40.35;
        obj4.type = 4;

        vector<Event_s>vv;

        vv.push_back(obj1);
        vv.push_back(obj2);
        vv.push_back(obj3);
        vv.push_back(obj4);

        Event_s mn;

        mn.end_time = 100000000.0;
        int index = -1,cnt = 0;

        for(auto itr:vv)
        {
            if(mn.end_time > itr.end_time)
            {
                index = cnt;
                mn = itr;
            }

            cnt++;
        }

        vv.erase(vv.begin() + index);

        for(auto itr:vv)
        {
            cout<<itr.type<<'\n';
        }*/
    }


    Scenario obj1;

    obj1.set_id(1);
    obj1.set_arrival_mean(1.0);
    obj1.set_departure_mean(3.0);

    obj1.initialize();

    Scenario obj2;

    obj2.set_id(2);
    obj2.set_arrival_mean(1.0);
    obj2.set_departure_mean(3.0);

    obj2.initialize();

    return 0;
}
