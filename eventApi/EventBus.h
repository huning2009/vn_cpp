//
// Created by root on 4/26/18.
//

#ifndef BT_EVENTBUS_H
#define BT_EVENTBUS_H
#include<map>
#include<memory>
#include<functional>
#include<string>
#include <vector>
#include"Event.h"





typedef std::function<void(EventPtr)> CallBack;
typedef std::string EventType;
typedef std::map<EventType,std::vector<CallBack>> CallBackMap;

class EventBus {
public:
    virtual void Regist(EventType,CallBack);
    virtual void UnRist(const EventType &,CallBack){}
    virtual void OnEvent(EventType,EventPtr);
public:
    CallBackMap call_back_map;
};

typedef std::shared_ptr<EventBus> EventBusPtr;


#endif //BT_EVENTBUS_H
