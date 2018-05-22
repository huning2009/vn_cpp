#pragma once
#include<iostream>
#include"../../../config_parse/ConfigParser.h"
#include"ThostFtdcTraderApi.h"
class trader_spi:public CThostFtdcTraderSpi
{
public:
	explicit trader_spi(const char * config_file);

    void OnFrontConnected()override ;
	void OnFrontDisconnected(int nReason)override;
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override ;
    void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override ;
    void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)override ;



    void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)override;
    void OnRtnOrder(CThostFtdcOrderField *pOrder)override;
    void OnRtnTrade(CThostFtdcTradeField *pTrade)override;

    void Init();
    void ReqUserLogin();
    void RegisterSpi();
    void RegisterFront();
    void ReqQrySettlementInfo();

    void ReqPosition(const std::string & symbol);
    void ReqAvaliableCash();

    //side :BUY SELL offsetflag:KAICANG PINGCANG
    void ReqInsertMarketOrder(char offsetflag,const std::string& symbol,char side,float quantity);
    void ReqInsertLimitOrder(char offsetflag,const std::string& symbol,char side,float quantity,double price);
    //original order api
    void InsertOrder(char ordType,char offsetflag,const std::string& symbol,char side,float quantity,double price);

	void Join() { td_api->Join();}
    const bool isReady(){return td_ready;}
    ~trader_spi(){td_api->Release();}
private:
	ConfigParse   config;
	CThostFtdcTraderApi * td_api;
    int requestId;
    int ordRef;
    bool td_ready;
    volatile bool free;
};

