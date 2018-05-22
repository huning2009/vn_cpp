#pragma once
module DataIceApi{

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

}