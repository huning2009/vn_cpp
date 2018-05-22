#include<iostream>
#include<ThostFtdcUserApiStruct.h>
#include<ThostFtdcUserApiDataType.h>

#include<string>
#include<ctime>
#include<mutex>
#include<cstring>

using std::to_string;
using std::cout;
using std::endl;
using std::string;

CThostFtdcReqUserLoginField build_login(const char *broker_Id, const char *user_Id, const char *pwd) {
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_Id);
    strcpy(req.UserID, user_Id);
    strcpy(req.Password, pwd);
    return req;
}

CThostFtdcSettlementInfoConfirmField build_conform(const char *broker_Id, const char *user_Id) {
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_Id);
    strcpy(req.InvestorID, user_Id);
    return req;
}

CThostFtdcQrySettlementInfoField build_settlement(const char *broker_Id, const char *user_Id) {
    CThostFtdcQrySettlementInfoField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_Id);
    strcpy(req.InvestorID, user_Id);
    return req;
}

CThostFtdcQryTradingAccountField build_account_qry(const char *broker_Id, const char *user_Id) {
    CThostFtdcQryTradingAccountField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_Id);
    strcpy(req.InvestorID, user_Id);
    return req;

}

CThostFtdcQryInvestorPositionField build_position_qry(const char *broker_Id, const char *user_Id, const char *symbol) {
    CThostFtdcQryInvestorPositionField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_Id);
    strcpy(req.InvestorID, user_Id);
    strcpy(req.InstrumentID, symbol);
    return req;
}

CThostFtdcInputOrderField build_order_qry(const char *broker_Id, const char *user_Id, int ordref,
                                          const char *symbol, char offsetFlag, char orderFlag, char side,
                                          int quantity, double price) {
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, broker_Id);
    strcpy(req.InvestorID, user_Id);
    strcpy(req.InstrumentID, symbol);
   // string OrderRefStr = std::to_string(ordref);
   // strcpy(req.OrderRef, OrderRefStr.c_str());
  //  strcpy(req.OrderRef, "201");

   // req.Direction = side;
    req.Direction = THOST_FTDC_D_Buy;

    req.CombOffsetFlag[0] = offsetFlag;
    //req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;

    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;

    req.VolumeTotalOriginal = quantity;
   // req.VolumeTotalOriginal = 1;

    req.VolumeCondition = THOST_FTDC_VC_AV;

    req.MinVolume = 1;

    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;

    req.IsAutoSuspend = 0;

    req.UserForceClose = 0;

    req.ContingentCondition = THOST_FTDC_CC_Immediately;

    if (orderFlag == THOST_FTDC_OPT_AnyPrice) {
        req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
        req.LimitPrice = 0;
        req.TimeCondition = THOST_FTDC_TC_IOC;

    } else if (orderFlag == THOST_FTDC_OPT_LimitPrice) {
        req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        req.LimitPrice = price;
        req.TimeCondition = THOST_FTDC_TC_GFD;
    } else
        throw std::runtime_error("this kind orderFlag not implemented");

    return req;
}