#include <stdexcept>
//#include <format>
#include "Wallet.h"
#include "CSVReader.h"

/*
Wallet::Wallet()
{

}
*/
std::ostream& operator<<(std::ostream& os, Wallet& wallet)
{
    os << wallet.toString();
    return os;
}

void  Wallet::insertCurrency (std::string type, double amount)
{
    //std::map <std::string, double> currencies;
    double balance;
    if ( amount < 0)
        //throw std::runtime_error(std::format("amount < 0 {0}: {1}", errno, strerror(errno)));
        throw std::invalid_argument("Trying to insert amount < 0");

    if (0 == currencies.count(type))
        currencies[type] = amount;
    else {
        balance = currencies[type];
        currencies[type] = amount + balance;
    }

}

bool Wallet::removeCurrency (std::string type, double amount)
{
    if ( amount < 0)
        throw std::invalid_argument("Trying to remove amount < 0");

    if (0 == currencies.count(type))
        return false;

    double balance = currencies[type];

    if (balance >= amount)
    {
        currencies[type] = balance - amount;
        return true;
    }

    return false;

}

bool  Wallet::containCurrency (std::string type, double amount)
{
    if (0 == currencies.count(type))
        return false;

    return currencies[type] >= amount;
}

std::string  Wallet::toString()
{
    std::string str = "";
    for (auto c: currencies)
    {
        str += c.first + " : " + std::to_string(c.second) + "\n";
    }
    return str;
}

bool Wallet::canFulfillOrder (const OrderBookEntry& order)
{
    std::vector <std::string> curr = CSVReader::tokenise (order.product, '/', 0);
    //ask

    if (order.orderType == OrderBookType::ask)
        return containCurrency(curr[0], order.amount);

    if (order.orderType == OrderBookType::bid)
        return containCurrency(curr[1], order.amount * order.price);

    return false;

}

void Wallet::processSale(const OrderBookEntry& sale)
{
    std::vector <std::string> curr = CSVReader::tokenise (sale.product, '/', 0);
    //ask

    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = curr[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = curr[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }

        if (sale.orderType == OrderBookType::asksale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = curr[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = curr[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }

}