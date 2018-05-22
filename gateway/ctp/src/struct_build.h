#pragma once

#include<string>

using std::string;

extern CThostFtdcReqUserLoginField build_login(const char *broker_Id, const char *user_Id, const char *pwd);

extern CThostFtdcSettlementInfoConfirmField build_conform(const char *broker_Id, const char *user_Id);

extern CThostFtdcQrySettlementInfoField build_settlement(const char *broker_Id, const char *user_Id);

extern CThostFtdcQryTradingAccountField build_account_qry(const char *broker_Id, const char *user_Id);

extern CThostFtdcQryInvestorPositionField  build_position_qry(const char *broker_Id, const char *user_Id, const char *symbol);

extern CThostFtdcInputOrderField build_order_qry(const char *broker_Id, const char *user_Id, int ordref,
                                                 const char *symbol, char offsetFlag, char orderFlag, char side,
                                                 int quantity, double price);