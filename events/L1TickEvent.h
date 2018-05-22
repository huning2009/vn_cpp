//
// Created by root on 4/26/18.
//

#ifndef BT_L1TICKEVENT_H
#define BT_L1TICKEVENT_H
#include "../eventApi/Event.h"
#include "../dataApi/L1Tick.h"

using std::string;
constexpr  const char * L1TICKEVENT="L1TickEvent";



class L1TickEvent: public Event {
public:
    L1TickEvent(const string & symbol,
                const string & time ,
                float lastPrice,
                float ask1Price,
                float bid1Price,
                float Volume,
                float ask1Volume,
                float bid1Volume):Event(L1TICKEVENT),data(new L1Tick{symbol,time,lastPrice,ask1Price,bid1Price,Volume,ask1Volume,bid1Volume}){}
    L1TickEvent(L1TickPtr l1TickPtr):Event(L1TICKEVENT),data(l1TickPtr){}

    virtual void * getData(){
        return (void *)data.get();
    }
public:
    L1TickPtr data;
};


#endif //BT_L1TICKEVENT_H
