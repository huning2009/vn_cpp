//
// Created by root on 4/26/18.
//

#ifndef BT_MAINENGINE_H
#define BT_MAINENGINE_H
#include<vector>
#include<algorithm>
#include "../eventApi/EventListener.h"
#include"../engine/EventEngine.h"
#include "../gateway/GateWay.h"
#include<map>


class MainEngine {
public:
    void AddEventListener(EventListenerPtr evl)
    {

        if(std::find(evlisteners.cbegin(),evlisteners.cend(),evl)==evlisteners.cend()) {
            evlisteners.push_back(evl);
            event_engine_ptr->Regist(evl);
        }
    }
    void AddGateWay(const string & gatewayName,GateWayLFPtr gvptr)
    {
        gvlf_ptrs[gatewayName]=gvptr;
        gvptr->SetEngine(event_engine_ptr);
    }

    void AddGateWay(const string & gatewayName,GateWayPtr gvptr)
    {
        gv_ptrs[gatewayName]=gvptr;
        gvptr->SetEngine(event_engine_ptr);
    }


    void SetEngine(EventEnginePtr enginePtr)
    {
        event_engine_ptr=enginePtr;
    }

    void Start()
    {
        event_engine_ptr->Start();
        for(auto& gateway:gv_ptrs)
            gateway.second->Start();
        for(auto& gateway:gvlf_ptrs)
            gateway.second->Start();
    }


    void SubscribeMarketData(const string & gatewayName,std::vector<std::string> symbol_list){
        for(auto &iter:gv_ptrs){
            if(iter.first==gatewayName)
            {
                iter.second->SubscribeMarketData(symbol_list);
                break;
            }
        }
    }
    void UnSubscribeMarketData(const string & gatewayName,std::vector<std::string> symbol_list){
        for(auto &iter:gv_ptrs){
            if(iter.first==gatewayName)
            {
                iter.second->UnSubscribeMarketData(symbol_list);
                break;
            }
        }
    };



    void insertMarketOrder(const string & gatewayName,char offsetflag,const string& symbol,char side,float quantity){
        for(auto &iter:gv_ptrs){
            if(iter.first==gatewayName)
            {
                iter.second->insertMarketOrder(offsetflag,symbol,side,quantity);
                break;
            }
        }

    }
    void insertLimitOrder(const string & gatewayName,char offsetflag,const string& symbol,char side,float quantity,float price){
        for(auto &iter:gv_ptrs){
            if(iter.first==gatewayName)
            {
                iter.second->insertLimitOrder(offsetflag,symbol,side,quantity,price);
                break;
            }
        }
    }


    void QryPosition(const string & gatewayName){
        for(auto &iter:gv_ptrs){
            if(iter.first==gatewayName)
            {
                iter.second->QryPosition();
                break;
            }
        }
    }
    void QryAvaliableCash(const string & gatewayName){
        for(auto &iter:gv_ptrs){
            if(iter.first==gatewayName)
            {
                iter.second->QryAvaliableCash();
                break;
            }
        }
    }



private:
    std::vector<EventListenerPtr> evlisteners;
    std::map<std::string,GateWayPtr> gv_ptrs;
    std::map<std::string,GateWayLFPtr> gvlf_ptrs;
    std::shared_ptr<EventEngine> event_engine_ptr;

};


#endif //BT_MAINENGINE_H
