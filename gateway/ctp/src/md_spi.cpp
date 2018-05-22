#include "md_spi.h"
#include"error_handle.h"
#include"struct_build.h"


md_spi::md_spi(const char * config_file):config(config_file),requestId(0),md_ready(false)
{
    string localfile=config.get_value("ctp","mdlogfile");
    md_api=CThostFtdcMdApi::CreateFtdcMdApi(localfile.c_str(),true);
}


void md_spi::OnFrontConnected()
{
#ifdef DEBUG
    cout<<__FUNCTION__<<endl;
#endif
    ReqUserLogin();
}


void md_spi::OnFrontDisconnected(int nReason)
{
#ifdef DEBUG
    cout<<__FUNCTION__<<endl;
#endif
}

void md_spi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef DEBUG
    cout<<__FUNCTION__<<endl;
#endif
    if(bIsLast&&hanle_error(__FUNCTION__, pRspInfo))
    {
        md_ready=true;
    }

}


void md_spi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef DEBUG
    cout <<__FUNCTION__ <<":"<< pSpecificInstrument->InstrumentID<<endl;
#endif
    hanle_error(__FUNCTION__, pRspInfo);

}
void md_spi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef DEBUG
    cout << __FUNCTION__ << pSpecificInstrument->InstrumentID <<endl;
#endif
    hanle_error(__FUNCTION__, pRspInfo);
}

void md_spi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
#ifdef DEBUG
    cout<<__FUNCTION__<<endl;
#endif
}
void md_spi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef DEBUG
    cout<<__FUNCTION__<<endl;
#endif
    hanle_error(std::to_string(nRequestID), pRspInfo);
}

void md_spi::RegisterSpi()
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    md_api->RegisterSpi(this);
}

void md_spi::RegisterFront()
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    string MdFrontAddr=config.get_value("ctp","MdFrontAddr");
    md_api->RegisterFront(const_cast<char *>(MdFrontAddr.c_str()));

}

void md_spi::ReqUserLogin()
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    string BrokerID=config.get_value("ctp","BrokerID");
    string InvesterID=config.get_value("ctp","InvesterID");
    string InvesterPassword=config.get_value("ctp","InvesterPassword");
    auto data_struct=build_login(BrokerID.c_str(),InvesterID.c_str(),InvesterPassword.c_str());
    md_api->ReqUserLogin(&data_struct, ++requestId);
}

void md_spi::SubscribeMarketData(std::vector<std::string> symbol_list){
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    char * inlists[symbol_list.size()];
    for(size_t i=0;i!=symbol_list.size();++i){
        inlists[i]= const_cast<char *>(symbol_list[i].data());
    }
    md_api->SubscribeMarketData(inlists,symbol_list.size());

}

void md_spi::UnSubscribeMarketData(std::vector<std::string> symbol_list){
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    char * inlists[symbol_list.size()];
    for(size_t i=0;i!=symbol_list.size();++i){
        inlists[i]= const_cast<char *>(symbol_list[i].data());
    }
    md_api->UnSubscribeMarketData(inlists,symbol_list.size());

}


void md_spi::Init()
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    md_api->Init();

}