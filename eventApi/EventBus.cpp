//
// Created by root on 4/26/18.
//

#include "EventBus.h"
#include <algorithm>
#include<iostream>
void EventBus::Regist(EventType eventName,CallBack callBack)
{
    auto & callbacks=call_back_map[eventName];
    //if(std::find(callbacks.cbegin(),callbacks.cend(),callBack)!=callbacks.cend())
#ifdef DEBUG
    std::cout<<"regist :"<<eventName<<std::endl;
#endif
    callbacks.push_back(callBack);
}


void EventBus::OnEvent(EventType eventName,EventPtr eventPtr)
{
    for(auto &func:call_back_map[eventName])
        func(eventPtr);
//  std::cout<<"eventType"<<eventName<<"func size:"<<call_back_map[eventName].size()<<std::endl;
}