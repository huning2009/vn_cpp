//
// Created by root on 5/9/18.
//

#ifndef BT_POSITIONEVENT_H
#define BT_POSITIONEVENT_H
#include "../eventApi/Event.h"
#include "../dataApi/PositionData.h"

constexpr  const char * POSITIONEVENT="POSITIONEVENT";


class PositionEvent: public Event {
public:
    PositionEvent():
            Event(POSITIONEVENT),data(new PositionData()){}
    PositionEvent(PositionDataPtr positionDataPtr):Event(POSITIONEVENT),data(positionDataPtr){}

    virtual void * getData(){
        return (void *)data.get();
    }
public:
    PositionDataPtr data;
};


#endif //BT_POSITIONEVENT_H
