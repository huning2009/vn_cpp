//
// Created by liulongxiao on 18-5-22.
//

#ifndef BT_L1TICKEVENT_LF_H
#define BT_L1TICKEVENT_LF_H
#include "../eventApi/Event.h"
#include "../longfirst/LFDataStruct.h"
using std::string;
constexpr  const char * L1TICKEVENT_LF="L1TickEvent_LF";
typedef std::shared_ptr<LFMarketDataField> LFMarketDataFieldPtr;


class L1TickEvent_LF: public Event {
public:
    L1TickEvent_LF(LFMarketDataFieldPtr l1TickPtr):Event(L1TICKEVENT_LF),data(l1TickPtr){}

    virtual void * getData(){
        return (void *)data.get();
    }
public:
    LFMarketDataFieldPtr data;
};

#endif //BT_L1TICKEVENT_LF_H
