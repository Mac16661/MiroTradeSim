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
    // Batch bids asks entry
    virtual void updateAsks(std::vector<std::vector<std::string>> asks) = 0;
    virtual void updateBids(std::vector<std::vector<std::string>> bids) = 0;
    virtual std::pair<double, std::pair<std::string, std::string>> topBid() = 0;
    virtual std::pair<double, std::pair<std::string, std::string>> topAsk() = 0;
    virtual bool isEmpty() = 0;
    
    virtual ~AbstractOrderBook();

    // TODO: Streamed trade entry (not sure it will be there or not)

    // Notify to downstream program
    virtual void subscribe(OrderBookListener* listener) = 0;
    virtual void unsubscribe(OrderBookListener* listener) = 0;
    virtual void notify(const BookMsg msg) = 0;

    // Debugging and logging
    virtual void showBook() = 0;
};

class MapOrderBook : public AbstractOrderBook {
    public:
        // Batch bids asks entry
        MapOrderBook(std::string _name) : name(_name) {}
        void updateAsks(std::vector<std::vector<std::string>> asks);
        void updateBids(std::vector<std::vector<std::string>> bids);
        std::pair<double, std::pair<std::string, std::string>> topBid();
        std::pair<double, std::pair<std::string, std::string>> topAsk();
        bool isEmpty();

        // TODO: Streamed trade entry (not sure it will be there or not)

        // Notify to downstream program
        void subscribe(OrderBookListener* listener);
        void unsubscribe(OrderBookListener* listener);
        void notify(const BookMsg msg);

        // Debugging and logging
        void showBook();
    private:
        std::map<double, std::pair<std::string, std::string>> asks; // min price first
        std::map<double, std::pair<std::string, std::string>, std::greater<>> bids; // max price first
        std::vector<OrderBookListener*> listeners;
        std::string name;
};

class HeapOrderBook : public AbstractOrderBook {};
