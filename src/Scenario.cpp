#include "Scenario.h"
#include <iostream>
#include "Event.h"
#include "Item.h"

void Scenario::set_id(int i)
{
    id = i;
}

int Scenario::get_id()
{
    return id;
}

void Scenario::set_arrival_mean(double m)
{
    arrival_mean = m;
}

double Scenario::get_arrival_mean()
{
    return arrival_mean;
}

void Scenario::set_departure_mean(double m)
{
    departure_mean = m;
}

double Scenario::get_departure_mean()
{
    return departure_mean;
}

double Scenario::get_total_queuing_delay()
{
    return total_queuing_delay;
}

double Scenario::get_total_system_delay()
{
    return total_system_delay;
}

double Scenario::exponential(double mean)
{

    double r = (double)rand()/RAND_MAX;

    double ex = -1 * mean * log (r);

    //std::cout<<ex<<'\n';

    return ex;

    //return 10.0;
}

void Scenario::create_trace_file()
{
    if(id == 1)
    {
        trace_.open ("trace1.out", std::ios::out);
        if (!trace_)
        {
            std::cout << "cannot open the trace file.\n";
        }
        trace_<< "trace file for the Scenario 1" << std::endl << std::endl;
    }
    else if(id == 2)
    {
        trace_.open ("trace2.out", std::ios::out);
        if (!trace_)
        {
            std::cout << "cannot open the trace file.\n";
        }
        trace_<< "trace file for the Scenario 2" << std::endl << std::endl;
    }
}

void Scenario::initialize()
{
    if(id == 1)
    {
        s1_status = 0;
        s2_status = 0;
        total_serviced_item = 0;
        total_queuing_delay = 0.0;
        total_system_delay = 0.0;
        total_number_item = 0.0;
        total_util_s1 = 0.0;
        total_util_s2 = 0.0;
        create_trace_file();

        //std::cout<<"For initial arrival event ";
        Event e = create_arrival_event(exponential(arrival_mean));
        add_event(e);

        run();

        trace_<<"Average Waiting Time : "<<(total_queuing_delay/100.0)<<std::endl;
        trace_<<"Average # Jobs in System : "<<( ( total_number_item*(1.0) ) / ( now()*(1.0) ) )<<std::endl;
        trace_<<"Server 1 Utilization : "<<( ( total_util_s1*(1.0) ) / ( now()*(1.0) ) )<<std::endl;
        trace_<<"Server 2 Utilization : "<<( ( total_util_s2*(1.0) ) / ( now()*(1.0) ) )<<std::endl;
        trace_<<"Average System Delay : "<<( (total_system_delay*(1.0)) / 100.0 )<<std::endl;

        //trace_<<"Total Queueing Delay : "<<(total_queuing_delay)<<std::endl;
    }
    else if(id == 2)
    {
        s1_status = 0;
        s2_status = 0;
        total_serviced_item = 0;
        total_queuing_delay = 0.0;
        total_system_delay = 0.0;
        total_number_item = 0.0;
        total_util_s1 = 0.0;
        total_util_s2 = 0.0;
        create_trace_file();

        Event e = create_arrival_event(exponential(arrival_mean));
        add_event(e);

        run();

        trace_<<"Average Waiting Time : "<<(total_queuing_delay/100.0)<<std::endl;
        trace_<<"Average # Jobs in System : "<<( ( total_number_item*(1.0) ) / ( now()*(1.0) ) )<<std::endl;
        trace_<<"Server 1 Utilization : "<<( ( total_util_s1*(1.0) ) / ( now()*(1.0) ) )<<std::endl;
        trace_<<"Server 2 Utilization : "<<( ( total_util_s2*(1.0) ) / ( now()*(1.0) ) )<<std::endl;
        trace_<<"Average System Delay : "<<( (total_system_delay*(1.0)) / 100.0)<<std::endl;

        //trace_<<"Total Queueing Delay : "<<(total_queuing_delay)<<std::endl;
    }
}

void Scenario::run()
{
    Event ee;

    while(eventList.size() > 0)
    {
        ee = remove_event();
        update_clock(ee.end_time);

        if(ee.type == 1)
        {
            arrival_handler();
        }
        else if(ee.type == 2)
        {
            departure_handler_1();
        }
        else if(ee.type == 3)
        {
            departure_handler_2();
        }
    }
}

Item Scenario::create_item()
{
    Item ii;
    ii.id = total_serviced_item + 1;
    total_serviced_item++;
    return ii;
}

void Scenario::arrival_handler()
{
    if(id == 1)
    {
        //std::cout<<"Inside Arrival handler at "<<now()<<' '<<total_serviced_item<<'\n';

        //creating Item
        Item ii = create_item();


        //processing Item
        if(q1.size_() <= q2.size_())
        {
            if(s1_status == 0)
            {
                total_util_s1 += s1_status;

                ii.added_to_server_at = now();
                item_in_service_at_s1 = ii;
                s1_status = 1;

                //std::cout<<"For departure event 1 : ";
                Event d = create_departure_event_1(exponential(departure_mean));
                add_event(d);
            }
            else if(s1_status == 1)
            {
                total_util_s1 += s1_status;

                ii.added_to_queue_at = now();
                q1.enque_(ii);

                total_number_item += q1.size_() + s1_status;
            }
        }
        else if(q1.size_() > q2.size_())
        {
            if(s2_status == 0)
            {
                total_util_s2 += s2_status;

                ii.added_to_server_at = now();
                item_in_service_at_s2 = ii;
                s2_status = 1;

                //std::cout<<"For departure event 2 : ";
                Event d = create_departure_event_2(exponential(departure_mean));
                add_event(d);
            }
            else if(s2_status == 1)
            {
                total_util_s2 += s2_status;

                ii.added_to_queue_at = now();
                q2.enque_(ii);

                total_number_item += q2.size_() + s2_status;
            }
        }


        //Scheduling New Arrival
        if(total_serviced_item < 100)
        {
            //std::cout<<"For arrival_handler arrival event : ";
            Event e = create_arrival_event(exponential(arrival_mean));
            add_event(e);
        }
    }
    else if(id == 2)
    {
        Item ii = create_item();

        if(s1_status == 0)
        {
            total_util_s1 += s1_status;

            ii.added_to_server_at = now();
            item_in_service_at_s1 = ii;
            s1_status = 1;

            Event d = create_departure_event_1(exponential(departure_mean));
            add_event(d);
        }
        else if(s2_status == 0)
        {
            total_util_s2 += s2_status;

            ii.added_to_server_at = now();
            item_in_service_at_s2 = ii;
            s2_status = 1;

            Event d = create_departure_event_2(exponential(departure_mean));
            add_event(d);
        }
        else if(s1_status == 1 && s2_status == 1)
        {
            total_util_s1 += s1_status;
            total_util_s2 += s2_status;

            ii.added_to_queue_at = now();
            q1.enque_(ii);

            total_number_item += q1.size_() + s1_status + s2_status;
        }

        if(total_serviced_item < 100)
        {
            //std::cout<<"For arrival_handler arrival event : ";
            Event e = create_arrival_event(exponential(arrival_mean));
            add_event(e);
        }
    }
}

void Scenario::departure_handler_1()
{
    if(id == 1)
    {
        total_util_s1 += s1_status;

        //std::cout<<"Inside Departure handler 1"<<now()<<' '<<total_serviced_item<<'\n';

        Item ii = item_in_service_at_s1;
        ii.leave_server_at = now();

        total_queuing_delay += (ii.leave_queue_at - ii.added_to_queue_at);
        total_system_delay += (ii.leave_server_at - ii.added_to_queue_at);

        //std::cout<<total_queuing_delay<<' '<<total_system_delay<<'\n';
        //std::cout<<"departure handler 1 "<<ii.added_to_queue_at<<'\n';

        if(q1.size_() > 0)
        {
            Item ii1 = q1.deque_();
            ii1.leave_queue_at = now();
            ii1.added_to_server_at = now();
            item_in_service_at_s1 = ii1;

            //std::cout<<"For departure event 1 : ";
            Event d = create_departure_event_1(exponential(departure_mean));
            add_event(d);
        }
        else if(q1.size_() == 0)
        {
            s1_status = 0;
        }
    }
    else if(id == 2)
    {
        total_util_s1 += s1_status;

        Item ii = item_in_service_at_s1;
        ii.leave_server_at = now();

        total_queuing_delay += (ii.leave_queue_at - ii.added_to_queue_at);
        total_system_delay += (ii.leave_server_at - ii.added_to_queue_at);

        if(q1.size_() > 0)
        {
            Item ii1 = q1.deque_();
            ii1.leave_queue_at = now();
            ii1.added_to_server_at = now();
            item_in_service_at_s1 = ii1;

            Event d = create_departure_event_1(exponential(departure_mean));
            add_event(d);
        }
        else if(q1.size_() == 0)
        {
            s1_status = 0;
        }
    }
}

void Scenario::departure_handler_2()
{
    if(id == 1)
    {
        total_util_s2 += s2_status;

        //std::cout<<"Inside Departure handler 2"<<now()<<' '<<total_serviced_item<<'\n';

        Item ii = item_in_service_at_s2;
        ii.leave_server_at = now();

        total_queuing_delay += (ii.leave_queue_at - ii.added_to_queue_at);
        total_system_delay += (ii.leave_server_at - ii.added_to_queue_at);

        //std::cout<<total_queuing_delay<<' '<<total_system_delay<<'\n';
        //std::cout<<"departure handler 2 "<<ii.added_to_queue_at<<'\n';

        if(q2.size_() > 0)
        {
            Item ii1 = q2.deque_();
            ii1.leave_queue_at = now();
            ii1.added_to_server_at = now();
            item_in_service_at_s2 = ii1;

            //std::cout<<"For departure event 2 : ";
            Event d = create_departure_event_2(exponential(departure_mean));
            add_event(d);
        }
        else if (q2.size_() == 0)
        {
            s2_status = 0;
        }
    }
    else if(id == 2)
    {
        total_util_s2 += s2_status;

        Item ii = item_in_service_at_s2;
        ii.leave_server_at = now();

        total_queuing_delay += (ii.leave_queue_at - ii.added_to_queue_at);
        total_system_delay += (ii.leave_server_at - ii.added_to_queue_at);

        if(q1.size_() > 0)
        {
            Item ii1 = q1.deque_();
            ii1.leave_queue_at = now();
            ii1.added_to_server_at = now();
            item_in_service_at_s2 = ii1;

            Event d = create_departure_event_2(exponential(departure_mean));
            add_event(d);
        }
        else if(q1.size_() == 0)
        {
            s2_status = 0;
        }
    }
}

Event Scenario::create_arrival_event(double t)
{
    Event ee;
    ee.start_time = now();
    ee.end_time = ee.start_time + t;
    ee.type = 1;

    return ee;
}

Event Scenario::create_departure_event_1(double t)
{
    Event ee;
    ee.start_time = now();
    ee.end_time = ee.start_time + t;
    ee.type = 2;

    return ee;
}

Event Scenario::create_departure_event_2(double t)
{
    Event ee;
    ee.start_time = now();
    ee.end_time = ee.start_time + t;
    ee.type = 3;

    return ee;
}






















