#include"config_parse/ConfigParser.h"
#include"gateway/ctp/gwinclude/CtpGateway.h"
#include"main_engine/MainEngine.h"
#include"gateway/FileGateWay.h"
#include"strategy/StrategyBase.h"
#include"tools/ma.h"

#define Sleep(n) std::this_thread::sleep_for(std::chrono::seconds(n))

class PrintStrategy:public StrategyBase{
public:
    PrintStrategy():StrategyBase(),ma100(100),ma200(200){}
    void OnTick(EventPtr eventPtr)override {
        L1Tick * data =static_cast<L1Tick *>(eventPtr->getData());
        cout<<data->Symbol<<endl;
        cout<<data->lastPrice<<" MA100:"<<ma100.data()<<"MA200:"<<ma200.data()<<endl;
        ma200.push(data->lastPrice);
        ma100.push(data->lastPrice);

        if(ma100.data()>ma200.data()*1.0005)
            insertLimitOrder("ctp",'K',data->Symbol,'L',1,data->lastPrice);
        if(ma100.data()*1.0005<ma200.data())
            insertLimitOrder("ctp",'P',data->Symbol,'L',1,data->lastPrice);
    }

    void OnOrder(EventPtr eventPtr)override {
        OrderData * data = static_cast<OrderData *>(eventPtr->getData());
        cout<<"symbol :"<<data->Symbol<<endl;
        cout<<"status :"<<data->status<<endl;
    }


    void OnTrade(EventPtr eventPtr)override {
        TradeData * data= static_cast<TradeData *>(eventPtr->getData());
        cout<<"symbol :"<<data->Symbol<<endl;
        cout<<"quant  :"<<data->Quantity<<endl;
        cout<<"price  :"<<data->AvgPrice<<endl;
    }




    void RegistAll(EventBusPtr eventBusPtr)override {
        RegistEvent(eventBusPtr, L1TICKEVENT, std::bind(&PrintStrategy::OnTick, this, std::placeholders::_1));
        RegistEvent(eventBusPtr, ORDEREVENT, std::bind(&PrintStrategy::OnOrder, this, std::placeholders::_1));
        RegistEvent(eventBusPtr, TRADEEVENT, std::bind(&PrintStrategy::OnTrade, this, std::placeholders::_1));
    }

    Ma ma200;
    Ma ma100;
};


class PrintStrategy_LF:public StrategyBase{
public:
    PrintStrategy_LF():StrategyBase(),ma100(100),ma200(200){}
    void OnTick(EventPtr eventPtr)override {
        LFMarketDataField * data =static_cast<LFMarketDataField *>(eventPtr->getData());
        cout<<data->InstrumentID<<endl;
        cout<<data->LastPrice<<" MA100:"<<ma100.data()<<"MA200:"<<ma200.data()<<endl;
        ma200.push(data->LastPrice);
        ma100.push(data->LastPrice);

        if(ma100.data()>ma200.data()*1.0005)
            insertLimitOrder("ctp",'K',data->InstrumentID,'L',1,data->LastPrice);
        if(ma100.data()*1.0005<ma200.data())
            insertLimitOrder("ctp",'P',data->InstrumentID,'L',1,data->LastPrice);
    }

    void OnOrder(EventPtr eventPtr)override {
        LFRtnOrderField * data = static_cast<LFRtnOrderField *>(eventPtr->getData());
        cout<<"symbol :"<<data->InstrumentID<<endl;
        cout<<"status :"<<data->OrderStatus<<endl;
    }


    void OnTrade(EventPtr eventPtr)override {
        LFRtnTradeField * data= static_cast<LFRtnTradeField *>(eventPtr->getData());
        cout<<"symbol :"<<data->InstrumentID<<endl;
        cout<<"quant  :"<<data->Volume<<endl;
        cout<<"price  :"<<data->Price<<endl;
    }




    void RegistAll(EventBusPtr eventBusPtr)override {
        RegistEvent(eventBusPtr, L1TICKEVENT_LF, std::bind(&PrintStrategy_LF::OnTick, this, std::placeholders::_1));
        RegistEvent(eventBusPtr, ORDEREVENT_LF, std::bind(&PrintStrategy_LF::OnOrder, this, std::placeholders::_1));
        RegistEvent(eventBusPtr, TRADEEVENT_LF, std::bind(&PrintStrategy_LF::OnTrade, this, std::placeholders::_1));
    }

    Ma ma200;
    Ma ma100;
};


int main(){

    //std::shared_ptr<StrategyBase> l(new PrintStrategy);
    std::shared_ptr<StrategyBase> l(new PrintStrategy_LF);
    std::shared_ptr<MainEngine> mengine(new MainEngine);
    std::shared_ptr<EventEngine> eengine(new EventEngine);
    l->SetMainEngine(mengine.get());
    mengine->SetEngine(eengine);
    mengine->AddEventListener(l);
    std::shared_ptr<GateWay_LF> g(new CtpGateway_LF("/home/liulongxiao/CLionProjects/bt/config_file/ctpconfig"));
    mengine->AddGateWay("ctp",g);
    mengine->Start();

    mengine->SubscribeMarketData("ctp",{"rb1810"});
    //mengine->QryAvaliableCash("ctp");
    getchar();

}