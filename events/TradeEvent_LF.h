//
// Created by liulongxiao on 18-5-22.
//

#ifndef BT_TRADEEVENT_LF_H
#define BT_TRADEEVENT_LF_H
#include "../eventApi/Event.h"
#include "../longfirst/LFDataStruct.h"

using std::string;
constexpr  const char * TRADEEVENT_LF="TRADEEVENT_LF";
typedef std::shared_ptr<LFRtnTradeField> LFRtnTradeFieldPtr;


class TradeEvent_LF: public Event {
public:
    TradeEvent_LF(LFRtnTradeFieldPtr l1TickPtr):Event(TRADEEVENT_LF),data(l1TickPtr){}
    virtual void * getData(){
        return (void *)data.get();
    }
public:
    LFRtnTradeFieldPtr data;
};

#endif //BT_TRADEEVENT_LF_H
