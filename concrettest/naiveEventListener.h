//
// Created by root on 4/26/18.
//

#ifndef BT_NAIVEEVENTLISTENER_H
#define BT_NAIVEEVENTLISTENER_H
#include "../eventApi/EventListener.h"
#include "../events/L1TickEvent.h"
class naiveEventListener: public EventListener {
public:
    naiveEventListener():EventListener(),cnt(0){}
    void PrintCount(EventPtr eventPtr)
    {
        std::cout<<"event count :"<<cnt<<std::endl;
        void * data=eventPtr->getData();
        std::cout<<static_cast<L1Tick *>(data)->Symbol<<std::endl;

    }


    virtual void RegistAll(EventBusPtr eventBusPtr)
    {
        RegistEvent(eventBusPtr,"L1TickEvent",std::bind(&naiveEventListener::PrintCount,this ,std::placeholders::_1));
        RegistEvent(eventBusPtr,"L1TickEvent",std::bind(&naiveEventListener::OnEvent,this,std::placeholders::_1));
    }
    int cnt;

};


#endif //BT_NAIVEEVENTLISTENER_H
