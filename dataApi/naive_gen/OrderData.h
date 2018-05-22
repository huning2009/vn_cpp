//
// Created by liulongxiao on 5/15/18.
//

#ifndef BT_ORDERDATA_H1
#define BT_ORDERDATA_H1
#include<string>
using std::string;
struct OrderData{
    string Symbol;
    char Side;
    string OrderId;
    char OrderType;
    char status;
    float Quantity;
    float Price;
};
#endif //BT_ORDERDATA_H
