//
// Created by root on 5/9/18.
//

#ifndef BT_CTPGATEWAY_H
#define BT_CTPGATEWAY_H
#include "../../GateWay.h"
#include"../src/md_spi.h"
#include"../src/trader_spi.h"
#include"../../../longfirst/LFDataStruct.h"
#include"../../../longfirst/ctp.h"
class CtpGateway: public GateWay,
                  public md_spi,
                  public trader_spi
{
public:
    CtpGateway(const char * config_file):GateWay(),trader_spi(config_file),md_spi(config_file){}

    void Start()override {
        md_spi::RegisterSpi();
        md_spi::RegisterFront();
        md_spi::Init();
        trader_spi::RegisterSpi();
        trader_spi::RegisterFront();
        trader_spi::Init();

        while(!isReady()){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    bool isReady(){
        return md_spi::isReady()&&trader_spi::isReady();
    }


    void SubscribeMarketData(std::vector<std::string> symbol_list)override {
        md_spi::SubscribeMarketData(symbol_list);
    }
    void UnSubscribeMarketData(std::vector<std::string> symbol_list)override {
        md_spi::UnSubscribeMarketData(symbol_list);
    }
    void insertMarketOrder(char offsetflag,const string& symbol,char side,float quantity)override {
        trader_spi::ReqInsertMarketOrder(offsetflag,symbol,side,quantity);
    }
    void insertLimitOrder(char offsetflag,const string& symbol,char side,float quantity,float price)override{
        trader_spi::ReqInsertLimitOrder(offsetflag,symbol,side,quantity,price);
    }

    void QryPosition(const std::string & symbol)override{
        trader_spi::ReqPosition(symbol);
    }
    void QryAvaliableCash()override{
        trader_spi::ReqAvaliableCash();
    }

/*--------------------------------------------------------------------RSP-------------------------------------------------------------*/
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)override
    {
#ifdef DEBUG
        cout<<__FUNCTION__<<endl;
#endif
        L1TickPtr tickDataPtr(new L1Tick{pDepthMarketData->InstrumentID,
                                         pDepthMarketData->UpdateTime,
                                         pDepthMarketData->LastPrice,
                                         pDepthMarketData->AskPrice1,
                                         pDepthMarketData->BidPrice1,
                                         pDepthMarketData->Volume,
                                         pDepthMarketData->AskVolume1,
                                         pDepthMarketData->BidVolume1
        });
        OnL1Tick(tickDataPtr);
    }

    void OnRtnOrder(CThostFtdcOrderField *pOrder)override{
#ifdef DEBUG
        cout<<__FUNCTION__<<endl;
#endif
        OrderDataPtr orderDataPtr(new OrderData{
                pOrder->InstrumentID,
                pOrder->CombOffsetFlag[0],
                pOrder->OrderRef,
                pOrder->OrderPriceType,
                pOrder->OrderStatus,
                pOrder->VolumeTotalOriginal,
                pOrder->LimitPrice,
        });
        OnOrder(orderDataPtr);

    }
    void OnRtnTrade(CThostFtdcTradeField *pTrade)override{
#ifdef DEBUG
        cout<<__FUNCTION__<<endl;
#endif
        TradeDataPtr tradeDataPtr(new TradeData{
                pTrade->InstrumentID,
                pTrade->Direction,
                pTrade->OrderRef,
                pTrade->Volume,
                pTrade->Price
        });
        OnTrade(tradeDataPtr);
    }
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override{
        static PositionData position;
        if(bIsLast){
            position[pInvestorPosition->InstrumentID]=pInvestorPosition->YdPosition+pInvestorPosition->Position;
            PositionDataPtr pos(new PositionData(position));
            OnPosition(pos);
            position.clear();
        }
        else{
            position[pInvestorPosition->InstrumentID]=pInvestorPosition->YdPosition+pInvestorPosition->Position;
        }
    }


};






class CtpGateway_LF: public GateWay_LF,
                     public md_spi,
                     public trader_spi
{
public:
    CtpGateway_LF(const char * config_file):GateWay_LF(),trader_spi(config_file),md_spi(config_file){}

    void Start()override {
        md_spi::RegisterSpi();
        md_spi::RegisterFront();
        md_spi::Init();
        trader_spi::RegisterSpi();
        trader_spi::RegisterFront();
        trader_spi::Init();

        while(!isReady()){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    bool isReady(){
        return md_spi::isReady()&&trader_spi::isReady();
    }


    void SubscribeMarketData(std::vector<std::string> symbol_list)override {
        md_spi::SubscribeMarketData(symbol_list);
    }
    void UnSubscribeMarketData(std::vector<std::string> symbol_list)override {
        md_spi::UnSubscribeMarketData(symbol_list);
    }
    void insertMarketOrder(char offsetflag,const string& symbol,char side,float quantity)override {
        trader_spi::ReqInsertMarketOrder(offsetflag,symbol,side,quantity);
    }
    void insertLimitOrder(char offsetflag,const string& symbol,char side,float quantity,float price)override{
        trader_spi::ReqInsertLimitOrder(offsetflag,symbol,side,quantity,price);
    }

    void QryPosition(const std::string & symbol)override{
        trader_spi::ReqPosition(symbol);
    }
    void QryAvaliableCash()override{
        trader_spi::ReqAvaliableCash();
    }

/*--------------------------------------------------------------------RSP-------------------------------------------------------------*/
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)override
    {
#ifdef DEBUG
        cout<<__FUNCTION__<<endl;
#endif

        OnL1Tick(parsePtrFrom(*pDepthMarketData));
    }

    void OnRtnOrder(CThostFtdcOrderField *pOrder)override{
#ifdef DEBUG
        cout<<__FUNCTION__<<endl;
#endif

        OnOrder(parsePtrFrom(*pOrder));
    }
    void OnRtnTrade(CThostFtdcTradeField *pTrade)override{
#ifdef DEBUG
        cout<<__FUNCTION__<<endl;
#endif

        OnTrade(parsePtrFrom(*pTrade));
    }
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override{
        static PositionData position;
        if(bIsLast){
            position[pInvestorPosition->InstrumentID]=pInvestorPosition->YdPosition+pInvestorPosition->Position;
            PositionDataPtr pos(new PositionData(position));
            OnPosition(pos);
            position.clear();
        }
        else{
            position[pInvestorPosition->InstrumentID]=pInvestorPosition->YdPosition+pInvestorPosition->Position;
        }
    }


};








#endif //BT_CTPGATEWAY_H
