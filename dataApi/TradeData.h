//
// Created by root on 5/3/18.
//

#ifndef BT_TRADEDATA_H
#define BT_TRADEDATA_H
#ifdef USEICE
#include"icegen/TradeData.h"
using DataIceApi::TradeData;
#else
#include "naive_gen/TradeData.h"
#endif

typedef std::shared_ptr<TradeData> TradeDataPtr;

#endif //BT_TRADEDATA_H
