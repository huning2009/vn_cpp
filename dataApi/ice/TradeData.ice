#pragma once
module DataIceApi{

struct TradeData{
    string Symbol;
    string Side;
    string OrderId;
    float Quantity;
    float AvgPrice;
};
}