//
// Created by root on 4/26/18.
//

#ifndef BT_FAKEGATEWAY_H
#define BT_FAKEGATEWAY_H
#include"GateWay.h"

class FakeGateWay: public GateWay {
public:
    FakeGateWay(int interval_):GateWay(),interval(interval_){}

public:
    int interval;

};


#endif //BT_FAKEGATEWAY_H
