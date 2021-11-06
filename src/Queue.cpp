#include "Queue.h"
#include "Item.h"
#include <list>

std::list<Item> Queue::static_queue_;

void Queue::enque_(Item i)
{
    queue_.push_back(i);
}

Item Queue::deque_()
{
    Item vv;

    if(queue_.size() > 0)
    {
        vv = queue_.front();
        queue_.pop_front();
    }

    return vv;
}

int Queue::size_()
{
    return queue_.size();
}

void Queue::static_enque_(Item i)
{
    static_queue_.push_back(i);
}

Item Queue::static_deque_()
{
    Item vv;

    if(static_queue_.size() > 0)
    {
        vv = static_queue_.front();
        static_queue_.pop_front();
    }

    return vv;
}

int Queue::static_size_()
{
    return static_queue_.size();
}

