#ifndef SCENARIO_H
#define SCENARIO_H
#include "Scheduler.h"
#include "Server.h"
#include "Queue.h"
#include "Event.h"
#include "Item.h"
#include <fstream>

class Scenario : public Scheduler
{
    public:
        int get_id();
        void set_id(int v);

        double get_arrival_mean();
        void set_arrival_mean(double m);

        double get_departure_mean();
        void set_departure_mean(double m);

        double get_total_queuing_delay();
        double get_total_system_delay();

        double exponential(double mean);

        void initialize();

        Item create_item();

        void arrival_handler();
        void departure_handler_1();
        void departure_handler_2();

        Event create_arrival_event(double t);
        Event create_departure_event_1(double t);
        Event create_departure_event_2(double t);

        void run();

        void create_trace_file();


    protected:

    private:
        int id;

        double arrival_mean;
        double departure_mean;

        int s1_status;
        int s2_status;

        Queue q1,q2;

        int total_serviced_item;
        Item item_in_service_at_s1;
        Item item_in_service_at_s2;

        double total_queuing_delay;
        double total_system_delay;

       std::ofstream trace_;
};

#endif // SCENARIO_H
