#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>


class CSVReader
{
    public:
     CSVReader();

     static std::vector<OrderBookEntry> readCSV(std::string csvFile);
     static std::vector<std::string> tokenise(const std::string csvLine, char separator, char deletech);
     static OrderBookEntry stringsToOBE(
                                        std::string price, 
                                        std::string amount,
                                        std::string timestamp,
                                        std::string product,
                                        OrderBookType type);
    private:

     static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
     
}; 
