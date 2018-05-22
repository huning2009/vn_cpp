#include "trader_spi.h"
#include"error_handle.h"
#include"struct_build.h"
#include<cstring>
#include<../../../charset/gbk2utf.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;



trader_spi::trader_spi(const char * config_file):config(config_file),requestId(0),ordRef(1),td_ready(false),free(true)
{
	string localfile=config.get_value("ctp","tdlogfile");
	td_api=CThostFtdcTraderApi::CreateFtdcTraderApi(localfile.c_str());
}

void trader_spi::OnFrontConnected()
{
#ifdef  DEBUG
	cout<<__FUNCTION__ << "客户端到行情前置无身份链接已经成功建立" << endl;
#endif
    ReqUserLogin();
}


void trader_spi::OnFrontDisconnected(int nReason)
{
#ifdef  DEBUG
	cout <<__FUNCTION__<< "客户端到行情前置无身份连接建立失败 失败错误代码：" << nReason << endl;
#endif
}



void trader_spi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef  DEBUG
	cout << __FUNCTION__<<endl;
#endif
	hanle_error("OnRspUserLogin", pRspInfo);
	if (bIsLast&&(pRspInfo->ErrorID == 0))
	{
#ifdef  DEBUG
		cout << "trading day" << td_api->GetTradingDay() << endl;
#endif
        ReqQrySettlementInfo();
	}
}


void trader_spi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef DEBUG
	cout << __FUNCTION__<<endl;
#endif
	hanle_error(std::to_string(nRequestID), pRspInfo);
}


void trader_spi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef DEBUG
	cout << __FUNCTION__<<endl;
#endif
	if (bIsLast && (pRspInfo->ErrorID == 0))
	{
#ifdef DEBUG
		cout << "conform success" << endl;
#endif
        td_ready=true;
	}

}

void trader_spi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef DEBUG
	cout << __FUNCTION__ << endl;
#endif
	if (bIsLast)
	{
        string BROKER_ID=config.get_value("ctp","BrokerID");
        string INVESTOR_ID=config.get_value("ctp","InvesterID");
        auto data_struct=build_conform(BROKER_ID.c_str(), INVESTOR_ID.c_str());
		td_api->ReqSettlementInfoConfirm(&data_struct, ++requestId);
	}

}


void trader_spi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{


}



void trader_spi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
#ifdef DEBUG
	cout << __FUNCTION__<<endl;
#endif

	if (bIsLast&&hanle_error(__FUNCTION__,pRspInfo))
	{
#ifdef DEBUG
		cout << " 资金余额:" << pTradingAccount->Available;
#endif
	}

}

void trader_spi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
#ifdef DEBUG
    cout << __FUNCTION__<<endl;
#endif
}


void trader_spi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    if(pRspInfo){
        if(pRspInfo->ErrorID!=0){
            char x[81];
            gbk2utf8(x,pRspInfo->ErrorMsg,81);
            cout<<"error"<<pRspInfo->ErrorID<<"mag:"<<x<<endl;
        }
    }

}



/*------------------------------------------------------------------------------------------------------------------------------------*/
void trader_spi::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    cout<<"银行可用余额 ："<< pNotifyQueryAccount->BankUseAmount;
}

void trader_spi::OnRtnOrder(CThostFtdcOrderField *pOrder){
#ifdef DEBUG
    cout << __FUNCTION__ <<"--"<<pOrder->InstrumentID<<":";

#endif
    pOrder->OrderSubmitStatus;
    std::cout << "=====收到报单应答===== :";
    switch (pOrder->OrderStatus)
    {
        case THOST_FTDC_OSS_InsertSubmitted:
            cout<<"已经提交"<<endl;
            break;
        case THOST_FTDC_OSS_CancelSubmitted:
            cout<<"撤单已经提交"<<endl;
            break;
        case THOST_FTDC_OSS_ModifySubmitted:
            cout<<"修改已经提交"<<endl;
            break;
        case THOST_FTDC_OSS_Accepted:
            cout<<"已经接受"<<endl;
            break;
        case THOST_FTDC_OSS_InsertRejected:
            cout<<"报单已经被拒绝"<<endl;
            break;
        case THOST_FTDC_OSS_CancelRejected:
            cout<<"撤单已经被拒绝"<<endl;
            break;
        case THOST_FTDC_OSS_ModifyRejected:
            cout<<"改单已经被拒绝"<<endl;
            break;
    }
}

void trader_spi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo){
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
}

void trader_spi::OnRtnTrade(CThostFtdcTradeField *pTrade){
#ifdef DEBUG
    cout << __FUNCTION__ <<":";
    std::cout << "=====报单成功成交=====" << std::endl;
    std::cout << "成交时间： " << pTrade->TradeTime << std::endl;
    std::cout << "合约代码： " << pTrade->InstrumentID << std::endl;
    std::cout << "成交价格： " << pTrade->Price << std::endl;
    std::cout << "成交量： " << pTrade->Volume << std::endl;
    std::cout << "开平仓方向： " << pTrade->Direction << std::endl;
#endif

}







void trader_spi::RegisterSpi()
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    td_api->RegisterSpi(this);

}
void trader_spi::RegisterFront()
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    string TradeFrontAddr=config.get_value("ctp","TradeFrontAddr");
    td_api->RegisterFront(const_cast<char *>(TradeFrontAddr.c_str()));
}

void trader_spi::Init()
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    td_api->Init();
}

void trader_spi::ReqUserLogin() {
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    string BrokerID=config.get_value("ctp","BrokerID");
    string InvesterID=config.get_value("ctp","InvesterID");
    string InvesterPassword=config.get_value("ctp","InvesterPassword");
    auto data_struct=build_login(BrokerID.c_str(),InvesterID.c_str(),InvesterPassword.c_str());
    td_api->ReqUserLogin(&data_struct, ++requestId);

}

void trader_spi::ReqQrySettlementInfo(){
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    string BrokerID=config.get_value("ctp","BrokerID");
    string InvesterID=config.get_value("ctp","InvesterID");
    auto data_struct=build_settlement(BrokerID.c_str(),InvesterID.c_str());
    td_api->ReqQrySettlementInfo(&data_struct,requestId++);

}

void trader_spi::ReqPosition(const string & symbol){
#ifdef DEBUG
    cout<<__FUNCTION__<<endl;
#endif
	string BrokerID=config.get_value("ctp","BrokerID");
	string InvesterID=config.get_value("ctp","InvesterID");
	auto data_struct=build_position_qry(BrokerID.c_str(),InvesterID.c_str(),symbol.c_str());
	td_api->ReqQryInvestorPosition(&data_struct,++requestId);
}

void trader_spi::ReqAvaliableCash(){
#ifdef DEBUG
    cout<<__FUNCTION__<<endl;
#endif

    string BrokerID=config.get_value("ctp","BrokerID");
    string InvesterID=config.get_value("ctp","InvesterID");
    auto data_struct=build_account_qry(BrokerID.c_str(),InvesterID.c_str());
    td_api->ReqQryTradingAccount(&data_struct,++requestId);
}

void trader_spi::InsertOrder(char ordType,char offsetflag,const std::string& symbol,char side,float quantity,double price){
    string BrokerID=config.get_value("ctp","BrokerID");
    string InvesterID=config.get_value("ctp","InvesterID");
    char offset;

    char sideflag;

    if(offsetflag=='K')
        offset=THOST_FTDC_OF_Open;
    else if(offsetflag=='P')
        offset=THOST_FTDC_OF_Close;
    else
        throw std::runtime_error("offsetflag error");




    if(side=='L')
        sideflag=THOST_FTDC_D_Sell;
    else if(side=='S')
        sideflag=THOST_FTDC_D_Buy;
    else
        throw std::runtime_error("order side  not implemented");


    auto data_struct=build_order_qry(BrokerID.c_str(),InvesterID.c_str(),ordRef++,symbol.c_str(),offset,ordType,sideflag,quantity,price);
    td_api->ReqOrderInsert(&data_struct,++requestId);

}

void trader_spi::ReqInsertMarketOrder(char offsetflag,const std::string& symbol,char side,float quantity)
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    InsertOrder(THOST_FTDC_OPT_AnyPrice,offsetflag,symbol,side,quantity,0);
}

void trader_spi::ReqInsertLimitOrder(char offsetflag,const std::string& symbol,char side,float quantity,double price)
{
#ifdef DEBUG
    cout << __FUNCTION__ <<endl;
#endif
    InsertOrder(THOST_FTDC_OPT_LimitPrice,offsetflag,symbol,side,quantity,price);
}
