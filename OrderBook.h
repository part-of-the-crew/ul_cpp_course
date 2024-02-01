#pragma once

#include <iostream>
#include <string>

#include "OrderBookEntry.h"
#include "CSVReader.h"

class OrderBook {
    public:
        explicit OrderBook(const std::string& filename );
        
        std::vector <std::string> getKnownProducts();
        std::vector <OrderBookEntry> getOrders (OrderBookType type, const std::string& product, const std::string&  time);

        static double getHighPrice (const std::vector <OrderBookEntry>& orders);
        static double getLowPrice (const std::vector <OrderBookEntry>& orders);

        static double getMarketDepth (const std::vector <OrderBookEntry>& orders);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        std::string getEarliestTime();
        std::string getNextTime(const std::string& timestamp);

        void insertOrder (OrderBookEntry& order);

    private:
        std::vector <OrderBookEntry> orders;

};