//
// Created by root on 4/26/18.
//

#ifndef BT_EVENTENGINE_H
#define BT_EVENTENGINE_H
#include"../lockfreequeue/blockingconcurrentqueue.h"
#include<thread>
#include"../eventApi/Event.h"
#include "../eventApi/EventBus.h"
#include"../eventApi/EventListener.h"

class EventEngine {
public:
    EventEngine(EventBusPtr evbus_):__active(false),evbus(evbus_){}
    EventEngine():__active(false),evbus(new EventBus){

    }

    void Regist(EventListenerPtr evl_ptr)
    {
        evl_ptr->RegistAll(evbus);
    }

    void __run(){
        EventPtr evptr;
        while(__active){
            if(events.wait_dequeue_timed(evptr,100)) {
                std::thread task(std::bind(&EventBus::OnEvent,evbus.get(), std::placeholders::_1, std::placeholders::_2),evptr->getEventType(),evptr);
                task.detach();
                evbus->OnEvent(evptr->getEventType(), evptr);
            }
        }
    }


    void Start()
    {
        __active=true;
        __workingTread.reset(new std::thread(std::bind(&EventEngine::__run,this)));
        __workingTread->detach();
    }

    void Stop()
    {
        __active=false;
    }

    void PushEvent(EventPtr evptr)
    {
        events.enqueue(evptr);
    }


private:
    bool __active;
    moodycamel::BlockingConcurrentQueue<EventPtr> events;
    std::shared_ptr<std::thread> __workingTread;
    EventBusPtr evbus;

};

typedef std::shared_ptr<EventEngine> EventEnginePtr;

#endif //BT_EVENTENGINE_H
