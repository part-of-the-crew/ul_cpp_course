
#include <map>

#include "OrderBook.h"

OrderBook::OrderBook(std::string filename )
{
    orders = CSVReader::readCSV(filename);
}

std::vector <std::string> OrderBook::getKnownProducts()
{
    std::vector <std::string>  products;
    std::map<std::string, bool> prodMap;

    for (auto const& e: orders){
        prodMap[e.product] = true;
    }

    for (auto const& e: prodMap){
        products.push_back(e.first);
    }

    return products;
}



std::vector <OrderBookEntry> OrderBook::getOrders (OrderBookType type, std::string product, std::string  time)
{
    std::vector <OrderBookEntry> orders_sub;


    for (auto const& e: orders){
        if (
            e.orderType == type &&
            e.product == product &&
            e.timestamp == time
        )
        orders_sub.push_back(e);
    }



    return orders_sub;
}

double OrderBook::getHighPrice (std::vector <OrderBookEntry>& orders)
{
    double max = orders[0].price;

    for (const auto& e: orders )
    {
        if (e.price > max)
            max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice (std::vector <OrderBookEntry>& orders)
{
    double min = orders[0].price;

    for (const auto& e: orders )
    {
        if (e.price < min)
            min = e.price;
    }
    return min;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime( std::string timestamp )
{
    std::string next_timestamp = "";

    for (const auto& e: orders )
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }

        if (next_timestamp == "")
            next_timestamp = orders[0].timestamp;
    }
    
    return next_timestamp;
}