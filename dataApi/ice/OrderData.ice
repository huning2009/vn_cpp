#pragma once
module DataIceApi{

struct OrderData{
    string Symbol;
    string Side;
    string OrderId;
    string OrderType;
    string status;
    float Quantity;
    float Price;
};
}