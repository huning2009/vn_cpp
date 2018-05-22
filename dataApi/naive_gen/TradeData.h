//
// Created by liulongxiao on 5/15/18.
//

#ifndef BT_TRADEDATA_H1
#define BT_TRADEDATA_H1
#include<string>
using std::string;
struct TradeData{
    string Symbol;
    char Side;
    string OrderId;
    float Quantity;
    float AvgPrice;
};
#endif //BT_TRADEDATA_H
