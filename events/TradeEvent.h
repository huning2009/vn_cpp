//
// Created by root on 5/3/18.
//

#ifndef BT_TRADEEVENT_H
#define BT_TRADEEVENT_H

#include "../eventApi/Event.h"
#include "../dataApi/TradeData.h"

constexpr  const char * TRADEEVENT="TRADEEVENT";



class TradeEvent: public Event {
public:
    TradeEvent( const string & symbol,
                char side ,
                const string & orderid,
                float quantity,
                float avgPrice):
            Event(TRADEEVENT),data(new TradeData{symbol,side,orderid,quantity,avgPrice}){}
    TradeEvent(TradeDataPtr tradeDataPtr):Event(TRADEEVENT),data(tradeDataPtr){}

    virtual void * getData(){
        return (void *)data.get();
    }
public:
    TradeDataPtr data;
};
#endif //BT_TRADEEVENT_H
