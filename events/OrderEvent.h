//
// Created by root on 5/3/18.
//

#ifndef BT_ORDEREVENT_H
#define BT_ORDEREVENT_H

#include "../eventApi/Event.h"
#include "../dataApi/OrderData.h"

constexpr  const char * ORDEREVENT="ORDEREVENT";



class OrderEvent: public Event {
public:
    OrderEvent( const string & symbol,
                char side ,
                const string & orderid,
                char  ordertype,
                char status,
                float quantity,
                float price):
            Event(ORDEREVENT),data(new OrderData{symbol,side,orderid,ordertype,status,quantity,price}){}
    OrderEvent(OrderDataPtr orderDataPtr):Event(ORDEREVENT),data(orderDataPtr){}

    virtual void * getData(){
        return (void *)data.get();
    }
public:
    OrderDataPtr data;
};
#endif //BT_ORDEREVENT_H
