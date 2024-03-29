#include <map>
#include <numeric>

#include "OrderBook.h"

OrderBook::OrderBook(const std::string& filename ): orders(CSVReader::readCSV(filename))
{
   // orders = CSVReader::readCSV(filename);
}



std::vector <OrderBookEntry> OrderBook::getOrders (OrderBookType type, const std::string& product, const std::string&  time)
{
    std::vector <OrderBookEntry> orders_sub;

    copy_if (begin(orders), end(orders), back_inserter(orders_sub),
            [type, &product, &time](
                const OrderBookEntry &order
            ){
                return order.orderType == type && order.product == product && (order.timestamp == time || "0" == time);
            });
 /*           
    for (auto const& e: orders){
        if (
            e.orderType == type &&
            e.product == product &&
            (e.timestamp == time || "0" == time)
        )
        orders_sub.push_back(e);
    }


*/
    return orders_sub;
}
/*
double OrderBook::getHighPrice (const std::vector <OrderBookEntry>& orders)
{
    double max = orders[0].price;

    for (const auto& e: orders )
    {
        if (e.price > max)
            max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice (const std::vector <OrderBookEntry>& orders)
{
    double min = orders[0].price;

    for (const auto& e: orders )
    {
        if (e.price < min)
            min = e.price;
    }
    return min;
}
*/
double OrderBook::getHighPrice (const std::vector <OrderBookEntry>& orders)
{
    auto it = std::max_element(begin(orders), end(orders), [](const OrderBookEntry &a, const OrderBookEntry &b) {
            return a.price < b.price;
        });
    return it->price;
}

double OrderBook::getLowPrice (const std::vector <OrderBookEntry>& orders)
{
    auto it = std::min_element(begin(orders), end(orders), [](const OrderBookEntry &a, const OrderBookEntry &b) {
            return a.price < b.price;
        });
    return it->price;
}

double OrderBook::getMarketDepth (const std::vector <OrderBookEntry>& orders)
{
    return std::accumulate(begin(orders), end(orders), 0, [](double acc, const OrderBookEntry& entry) {
            return acc + entry.amount;
        });
}
/*
double OrderBook::getMarketDepth (const std::vector <OrderBookEntry>& orders)
{
    double sum = 0;
    for (auto const& e: orders)
    {
        sum += e.amount;
    }
    return sum;
}
*/
std::vector <std::string> OrderBook::getKnownProducts()
{
    std::vector <std::string> products;
    std::map<std::string, bool> prodMap;

    for (auto const& e: orders){
        prodMap[e.product] = true;
    }
/*
    for (auto const& e: prodMap){
        products.push_back(e.first);
    }
*/

    std::transform(cbegin(prodMap), cend(prodMap), std::back_inserter(products),
                    [](const std::pair <std::string, bool>& p) { 
                        return p.first;
                    });

/*
    copy (prodMap.cbegin(), prodMap.cend(), back_inserter(products), []() {
            return 
        });


    copy_if (begin(orders), end(orders), back_inserter(orders_sub),
            [type, &product, &time](
                const OrderBookEntry &order
            ){
                return order.orderType == type && order.product == product && (order.timestamp == time || "0" == time);
            });
*/        
    return products;
}



std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime( const std::string& timestamp )
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

void OrderBook::insertOrder (OrderBookEntry& order)
{
    orders.push_back (order);
    std::sort(std::begin(orders), std::end(orders), [](const OrderBookEntry& a, const OrderBookEntry& b){
        return a.timestamp < b.timestamp;
    });
}


std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders (OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders (OrderBookType::bid, product, timestamp);

    std::vector<OrderBookEntry> sales;

    std::sort(std::begin(asks), std::end(asks), [](const OrderBookEntry& a, const OrderBookEntry& b){
        return a.price < b.price;
    });

    std::sort(std::begin(bids), std::end(bids), [](const OrderBookEntry& a, const OrderBookEntry& b){
        return a.price > b.price;
    });

    for (auto& a: asks)
    {
        for (auto &b: bids)
        {
            if (b.price >= a.price)
            {
                OrderBookType type = OrderBookType::asksale;
                OrderBookEntry sale{a.price, 0, timestamp, product, type};
                if ("simuser" == b.username)
                {
                    type = OrderBookType::bidsale;
                    sale.username = "simuset";
                    sale.orderType = type;
                }
                if ("simuser" == a.username)
                {
                    type = OrderBookType::asksale;
                    sale.username = "simuser";
                    sale.orderType = type;
                }

                if (b.amount == a.amount)
                {
                    sale.amount = a.amount;
                    sales.push_back(sale);
                    b.amount = 0;
                    break;
                }

                if (b.amount > a.amount && b.amount > 0)
                {
                    sale.amount = a.amount;
                    sales.push_back(sale);
                    b.amount -= a.amount;
                    break;
                }

                if (b.amount < a.amount)
                {
                    sale.amount = b.amount;
                    sales.push_back(sale);
                    a.amount -= b.amount;
                    b.amount = 0;
                    continue;
                }
            }
        }
    }

    return sales;
}