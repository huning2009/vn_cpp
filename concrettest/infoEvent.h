//
// Created by root on 4/26/18.
//

#ifndef BT_INFOEVENT_H
#define BT_INFOEVENT_H
#include "../eventApi/Event.h"

class infoEvent: public Event {
public:
    infoEvent():Event("info event"){}
};


#endif //BT_INFOEVENT_H
