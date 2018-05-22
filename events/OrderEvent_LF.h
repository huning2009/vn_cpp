//
// Created by liulongxiao on 18-5-22.
//

#ifndef BT_ORDEREVENT_LF_H
#define BT_ORDEREVENT_LF_H

#include "../eventApi/Event.h"
#include "../longfirst/LFDataStruct.h"

using std::string;
constexpr  const char * ORDEREVENT_LF="ORDEREVENT_LF";
typedef std::shared_ptr<LFRtnOrderField> LFRtnOrderFieldPtr;


class OrderEvent_LF: public Event {
public:
    OrderEvent_LF(LFRtnOrderFieldPtr lfRtnOrderFieldPtr):Event(ORDEREVENT_LF),data(lfRtnOrderFieldPtr){}
    virtual void * getData(){
        return (void *)data.get();
    }
public:
    LFRtnOrderFieldPtr data;
};


#endif //BT_ORDEREVENT_LF_H
