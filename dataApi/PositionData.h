//
// Created by root on 5/9/18.
//

#ifndef BT_POSITIONDATA_H
#define BT_POSITIONDATA_H

#ifdef USEICE
#include"icegen/PositionData.h"
using DataIceApi::PositionData
#else
#include "naive_gen/PositionData.h"
#endif

typedef std::shared_ptr<PositionData> PositionDataPtr;
#endif //BT_POSITIONDATA_H
