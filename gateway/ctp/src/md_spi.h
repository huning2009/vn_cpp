#pragma once
#include<iostream>
#include<ThostFtdcMdApi.h>
#include<ThostFtdcTraderApi.h>
#include<ThostFtdcUserApiStruct.h>
#include<ThostFtdcUserApiDataType.h>
#include<vector>
#include<string>
#include"../../../config_parse/ConfigParser.h"

using std::cout;
using std::cerr;
using std::endl;

class md_spi:public CThostFtdcMdSpi
{
public:
    explicit  md_spi(const char * config_file);
    void OnFrontConnected()override;
    void OnFrontDisconnected(int nReason)override;
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)override;
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)override;

    void ReqUserLogin();
    void RegisterSpi();
    void RegisterFront();
    void Init();
    void Join() { md_api->Join();}
    void SubscribeMarketData(std::vector<std::string> symbol_list);
    void UnSubscribeMarketData(std::vector<std::string> symbol_list);

    const bool isReady(){return md_ready;}
    ~md_spi() { md_api->Release(); }

private:
    CThostFtdcMdApi * md_api;
    ConfigParse   config;
    int requestId;
    bool md_ready;
};
