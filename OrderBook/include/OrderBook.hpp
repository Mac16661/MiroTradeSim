#pragma once
#include "Order.hpp"
#include <map>
#include <list>
#include <functional>

class AbstractOrderBook {
public:
    virtual void openOrder(const Order& order) = 0;
    virtual void closeOrder(const Order& order) = 0;
    virtual void modifyOrder(const Order& order, double newPrice = 0.0, uint32_t newQty = 0) = 0;
    virtual ~AbstractOrderBook() = default;
};

class LocalOrderBook : public AbstractOrderBook {
public:
    void openOrder(const Order& order) override;
    void closeOrder(const Order& order) override;
    void modifyOrder(const Order& order, double newPrice, uint32_t newQty) override;

private:
    std::map<double, std::list<Order>, std::greater<>> bids; // max price first
    std::map<double, std::list<Order>> asks;                 // min price first
};

// Other exchanges
class BinanceOrderBook : public AbstractOrderBook {};
class CoinbaseOrderBook : public AbstractOrderBook {};
