#pragma once

#include <string>

enum class OrderBookType{bid, ask, unknown, bidsale, asksale};

class OrderBookEntry
{
    public:

        OrderBookEntry( double _price, 
                        double _amount, 
                        const std::string& _timestamp, 
                        const std::string& _product, 
                        OrderBookType _orderType,
                        std::string username = "dataset");

        static OrderBookType stringToOrderBookType(const std::string& s);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;
};
 
