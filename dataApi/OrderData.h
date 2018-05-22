//
// Created by root on 5/3/18.
//

#ifndef BT_ORDERDATA_H
#define BT_ORDERDATA_H
#ifdef USEICE
#include"icegen/OrderData.h"
using DataIceApi::OrderData;
#else
#include "naive_gen/OrderData.h"

#endif

typedef std::shared_ptr<OrderData> OrderDataPtr;


#endif //BT_ORDERDATA_H
