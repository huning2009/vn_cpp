//
// Created by root on 5/3/18.
//

#ifndef BT_L1TICK_H
#define BT_L1TICK_H
#include<string>
#ifdef USEICE
#include"icegen/L1Tick.h"
using DataIceApi::L1Tick;
#else
#include "naive_gen/L1Tick.h"
#endif

typedef std::shared_ptr<L1Tick> L1TickPtr;
#endif //BT_L1TICK_H
