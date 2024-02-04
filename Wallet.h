#pragma once

#include <string>
#include <map>

#include "OrderBookEntry.h"

class Wallet
{
public:

    Wallet() = default;
    /** insert currency to the wallet */
    void insertCurrency(std::string type, double amount);
    /** remove currency from the wallet */
    bool removeCurrency(std::string& type, double amount);
    /** check if the wallet contains this much currency or more */
    bool containCurrency(std::string& type, double amount);
    /** generate a string representation of the wallet */
    std::string toString();

    bool canFulfillOrder (const OrderBookEntry& entry);

    friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

private:
    std::map <std::string, double> currencies;

};