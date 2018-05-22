//
// Created by root on 4/26/18.
//

#ifndef BT_EVENT_H
#define BT_EVENT_H
#include<memory>
#include<string>


class Event {
public:
    Event(const std::string & type_ ):eventType(type_){}
    virtual std::string getEventType(){return eventType;};
    virtual void * getData()=0;
    const std::string eventType;
};

typedef std::shared_ptr<Event> EventPtr;

#endif //BT_EVENT_H
