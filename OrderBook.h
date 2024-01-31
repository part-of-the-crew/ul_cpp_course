#pragma once

#include <iostream>
#include <string>

#include "OrderBookEntry.h"
#include "CSVReader.h"

class OrderBook {
    public:
        OrderBook(std::string filename );
        
        std::vector <std::string> getKnownProducts();
        std::vector <OrderBookEntry> getOrders (OrderBookType, std::string product, std::string  time);

        static double getHighPrice (std::vector <OrderBookEntry>& orders);
        static double getLowPrice (std::vector <OrderBookEntry>& orders);

        static double getMarketDepth (std::vector <OrderBookEntry>& orders);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        std::string getEarliestTime();
        std::string getNextTime(std::string timestamp);

        void insertOrder (OrderBookEntry& order);

    private:
        std::vector <OrderBookEntry> orders;

};