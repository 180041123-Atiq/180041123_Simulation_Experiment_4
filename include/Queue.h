#ifndef QUEUE_H
#define QUEUE_H
#include <list>
#include "Item.h"

class Queue
{
    public:
        void enque_(Item i);
        Item deque_();
        int size_();

        void static_enque_(Item i);
        Item static_deque_();
        int static_size_();

    protected:

    private:
        std::list<Item> queue_;
        static std::list<Item> static_queue_;
};

#endif // QUEUE_H
