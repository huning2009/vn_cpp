//
// Created by root on 4/26/18.
//

#ifndef BT_STRATEGY_H
#define BT_STRATEGY_H

#include"../eventApi/EventListener.h"
#include <string>
#include<string.h>
#include<algorithm>

using std::string;

constexpr const char *MarketOrder = "MarketOrder";
constexpr const char *FILLED_ORDER = "FILLED_ORDER";
constexpr const char *SideAsk = "SideAsk";
constexpr const char *SideBid = "SideBid";

struct Order {
    string Symbol;
    string OrderType;
    string Side;
    string Time;
    int Quantity;
    float Price;

};

inline long timediff(const string & t1,const string  &t2){
    long hour1  =atol(t1.substr(11,2).c_str()),hour2  =atol(t2.substr(11,2).c_str());
    long minute1=atol(t1.substr(14,2).c_str()),minute2=atol(t2.substr(14,2).c_str());
    long second1=atol(t1.substr(17,2).c_str()),second2=atol(t2.substr(17,2).c_str());
    long milsec1=atol(t1.substr(20,3).c_str()),milsec2=atol(t2.substr(20,3).c_str());
    return (hour1-hour2)*60*60*1000+(minute1-minute2)*60*1000+(second1-second2)*1000+milsec1-milsec2;

}




class StrategyBackTestBase {

public:
    StrategyBackTestBase(float commission_rate_,float init_cash,int timeout,int delay):comissionRate(commission_rate_),
                                                                                       cashAmt(init_cash),
                                                                                       timeOutTreshold(timeout),
                                                                                       tradeDelay(delay),
                                                                                       aliveOrders(0),
                                                                                       positionMap()

    {}

    virtual void DealTrade(EventPtr eventPtr) {
        L1Tick *data = static_cast<L1Tick *>(eventPtr->getData());
        for (auto &order:aliveOrders)
        {

            if(timediff(data->time,order.Time)<=tradeDelay)
                continue;

            if (data->Symbol == order.Symbol) {
                if (!strcmp(order.OrderType.c_str(), MarketOrder)) {
                    if (!strcmp(order.Side.c_str(), SideAsk)) {
                        positionMap[order.Symbol] -= order.Quantity;
                        cashAmt += order.Quantity * (data->bid1Price*(1-comissionRate));
                    } else {
                        float price_include_comission=data->ask1Price*(1+comissionRate);
                        if (cashAmt / price_include_comission > order.Quantity) {
                            positionMap[order.Symbol] += order.Quantity;
                            cashAmt -= order.Quantity * price_include_comission;
                        } else {
                            positionMap[order.Symbol] += int(cashAmt /price_include_comission);
                            cashAmt -= int(cashAmt /price_include_comission) * price_include_comission;
                        }
                    }

                    order.OrderType=FILLED_ORDER;
                } else {
                    // limit order not implemented

                }
            }
        }
        aliveOrders.erase(std::remove_if(aliveOrders.begin(),aliveOrders.end(),[](Order &od){return !strcmp(od.OrderType.c_str(),FILLED_ORDER) ;}),aliveOrders.end());
        cleanAliveOrder(data->time);
    }

    void MarketOrderBuy(string symbol,int quant,string time)
    {
        aliveOrders.push_back({symbol,
                                 MarketOrder,
                                 SideBid,
                                 time,
                                 quant,
                                 0});
    }

    void MarketOrderSell(string symbol,int quant,string time)
    {
        aliveOrders.push_back({symbol,
                                 MarketOrder,
                                 SideAsk,
                                 time,
                                 quant,
                                 0});

    }

    float AvaliableCash(){return cashAmt;}

    const std::map<string, int> & currentPosition(){
        return positionMap;
    };

    void cleanAliveOrder(const string & time)
    {

        auto remove_start=std::remove_if(aliveOrders.begin(),aliveOrders.end(),[time,this](Order &od){return timediff(time,od.Time)>timeOutTreshold;});
        aliveOrders.erase(remove_start,aliveOrders.end());
    }


protected:
    float comissionRate;
    float cashAmt;
    std::map<string, int> positionMap;
    std::vector<Order> aliveOrders;
    int timeOutTreshold;
    int tradeDelay;

};


class StrategyBackTest : public EventListener,
                         public  StrategyBackTestBase
{
public:

    StrategyBackTest(float commission_rate_,float init_cash,int timeout,int delay) :StrategyBackTestBase(commission_rate_,init_cash,timeout,delay), EventListener() {}

    virtual void OnTick(EventPtr eventPtr) {
        L1Tick * data =static_cast<L1Tick *>(eventPtr->getData());
        MarketOrderBuy(data->Symbol,1,data->time);
    }

    void printPosition(EventPtr eventPtr)
    {
        std::cout<<"use able amount"<<AvaliableCash()<<std::endl;
        for(auto &iter :positionMap)
            std::cout<<"symbol :"<<iter.first<<" quant :"<<iter.second<<std::endl;

    }


    virtual void RegistAll(EventBusPtr eventBusPtr) {
        RegistEvent(eventBusPtr, "L1TickEvent", std::bind(&StrategyBackTest::DealTrade, this, std::placeholders::_1));
        RegistEvent(eventBusPtr, "L1TickEvent", std::bind(&StrategyBackTest::OnTick, this, std::placeholders::_1));
        RegistEvent(eventBusPtr, "L1TickEvent", std::bind(&StrategyBackTest::printPosition, this, std::placeholders::_1));

    }

private:

    string pretic;
    volatile string time;


};


#endif //BT_STRATEGY_H
