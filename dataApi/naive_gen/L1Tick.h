//
// Created by liulongxiao on 5/15/18.
//

#ifndef BT_L1TICK_H1
#define BT_L1TICK_H1
#include<string>
using std::string;
struct L1Tick{
    string Symbol;
    string time;
    float lastPrice;
    float ask1Price;
    float bid1Price;
    float Volume;
    float ask1Volume;
    float bid1Volume;
};
#endif //BT_L1TICK_H
