//
// Created by root on 5/3/18.
//

#ifndef BT_STRATEGYBASE_H
#define BT_STRATEGYBASE_H
#include"../eventApi/EventListener.h"
#include <string>
#include<algorithm>
#include"../main_engine/MainEngine.h"
using std::string;

class StrategyBase : public EventListener
{
public:
    StrategyBase(){};
    StrategyBase(MainEngine * mengine):EventListener(),mainEnginePtr(mengine){}

    void SetMainEngine(MainEngine * mengine){
        mainEnginePtr=mengine;
//        mengine->AddEventListener(EventListenerPtr(this));
    }
    void insertMarketOrder(const string & gatewayName,char offsetflag,const string& symbol,char side,float quantity){
#ifdef DEBUG
        cout<<__FUNCTION__<<endl;
#endif
        mainEnginePtr->insertMarketOrder(gatewayName,offsetflag,symbol,side,quantity);
    }
    void insertLimitOrder(const string & gatewayName,char offsetflag,const string& symbol,char side,float quantity,float price){
        mainEnginePtr->insertLimitOrder(gatewayName,offsetflag,symbol,side,quantity,price);
    }
    void QryPosition(const string & gatewayName)
    {
        mainEnginePtr->QryPosition(gatewayName);
    }

    void QryAvaliableCash(const string & gatewayName)
    {
        mainEnginePtr->QryAvaliableCash(gatewayName);
    }
    void SubscribeMarketData(const string & gatewayName,std::vector<std::string> symbol_list){
        mainEnginePtr->SubscribeMarketData(gatewayName,symbol_list);
    }
    void UnSubscribeMarketData(const string & gatewayName,std::vector<std::string> symbol_list){
        mainEnginePtr->UnSubscribeMarketData(gatewayName,symbol_list);
    };

    virtual void OnTick(EventPtr eventPtr){}
    virtual void OnOrder(EventPtr eventPtr){}
    virtual void OnTrade(EventPtr eventPtr){}
    virtual void OnPosition(EventPtr eventPtr){}
    virtual void RegistAll(EventBusPtr eventBusPtr)=0;

private:
    MainEngine * mainEnginePtr;

};


#endif //BT_STRATEGYBASE_H
