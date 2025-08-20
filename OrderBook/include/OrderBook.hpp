#pragma once
#include "Order.hpp"

 // TODO: need to modify the Cmake file to use it here
#include "PubSub.hpp"

#include <map>
#include <list>
#include <vector>
#include <functional>

class OrderBookListener;

class AbstractOrderBook {
public:
    virtual void openOrder(const Order& order) = 0;
    virtual void closeOrder(const Order& order) = 0;
    virtual void modifyOrder(const Order& order, double newPrice = 0.0, uint32_t newQty = 0) = 0;
    virtual ~AbstractOrderBook();

    // TODO: Notify to downstream program
    virtual void subscribe(OrderBookListener* listener) = 0;
    virtual void unsubscribe(OrderBookListener* listener) = 0;
    virtual void notify(const BookMsg msg) = 0;

    // TODO: Debugging and logging
    virtual void showBook() = 0;
};

class MapLLOrderBook : public AbstractOrderBook {
public:
    void openOrder(const Order& order) override;
    void closeOrder(const Order& order) override;
    void modifyOrder(const Order& order, double newPrice, uint32_t newQty) override;

    // TODO: Create a sub, unsub, notify function which will send event to HFT strategy
    void subscribe(OrderBookListener* listener) override;

    void unsubscribe(OrderBookListener* listener) override;

    void notify(const BookMsg msg) override;

    void showBook() override;

private:
    std::map<double, std::list<Order>, std::greater<>> bids; // max price first
    std::map<double, std::list<Order>> asks;                 // min price first
    std::vector<OrderBookListener*> listeners;
};

// Other data structure implementation
class MapSetOrderBook : public AbstractOrderBook {};
class HeapOrderBook : public AbstractOrderBook {};
