//
// Created by root on 4/26/18.
//

#ifndef BT_EVENTLISTENER_H
#define BT_EVENTLISTENER_H
#include "Event.h"
#include "EventBus.h"
#include<iostream>

class EventListener {
public:
    using CallBackFunc= std::function<void (EventPtr)>;

    virtual void OnEvent(EventPtr eventPtr)
    {
        std::cout<<eventPtr->getEventType()<<std::endl;
    }

    void RegistEvent(EventBusPtr eventBusPtr,EventType eventType,CallBackFunc callbackfunc)
    {
        eventBusPtr->Regist(eventType,callbackfunc);
    }

    virtual void RegistAll(EventBusPtr eventBusPtr){};

};

typedef std::shared_ptr<EventListener> EventListenerPtr;

#endif //BT_EVENTLISTENER_H
