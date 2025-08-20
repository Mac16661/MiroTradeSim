#include "OrderBook.hpp"

#include <iostream>
#include <ostream>

void MapLLOrderBook::openOrder(const Order& order) {
    /*
       Check if order price already exists in given order type(bid/ask).
       If yes then add it to the order list tail.
       else create a new entry on map and add it to the list.
    */

    // TODO: Need to implement logic to mantain depth of the book N_SIZE as it is a L2 order book
    double price = order.price;
    if (order.side == Side::BUY) {
        bids[price].push_back(order);
    }else{
        asks[price].push_back(order);
    }

    // TODO: Create pubsub event
    #ifdef PUBSUB_ENABLED
    notify(BookMsg::OPEN);
    #endif

}

void MapLLOrderBook::closeOrder(const Order& order) {
     /*
        Check if price exists and also does this order exists.
        Go to the map index using price and delete order form the list using orderID.
    */
    double price = order.price;
    if (order.side == Side::BUY) {
        if(bids.find(price) != bids.end()) {
            auto& orderList = bids[price];
            for(auto it = orderList.begin(); it != orderList.end(); ++it){
                if(it->orderId == order.orderId){
                    orderList.erase(it);
                    // TODO: Create a pubsub event
                    #ifdef PUBSUB_ENABLED
                    notify(BookMsg::CLOSE);
                    #endif
                    return;
                }
            }
        }
    }else {
        if(asks.find(price) != asks.end()) {
                    auto& orderList = bids[price];
                    for(auto it = orderList.begin(); it != orderList.end(); ++it){
                        if(it->orderId == order.orderId){
                            orderList.erase(it);
                            // TODO: Create a pubsub event
                            #ifdef PUBSUB_ENABLED
                            notify(BookMsg::CLOSE);
                            #endif
                            return;
                        }
                    }
                }

    }
}

void MapLLOrderBook::modifyOrder(const Order& order, double newPrice=0.0, uint32_t newQty=0) {
      /*
         Delete old order and construct new one using newPrice or newQty of both.
         Search in map by price and in list by order id, delete it and construct a new order object and push it in a newPrice
      */

     double price = order.price;
     if (order.side == Side::BUY) {
        if(bids.find(price) != bids.end()) {
            auto& orderList = bids[price];
            for(auto it = orderList.begin(); it != orderList.end(); ++it) {
                if(it->orderId==order.orderId) {
                    if(price > 0.0) it->price = newPrice;
                    if(newQty > 0) it->qty = newQty;
                    // TODO: Create a pubsub
                    #ifdef PUBSUB_ENABLED
                    notify(BookMsg::MODIFY);
                    #endif
                    return;
                }
            }
        }
     }else {
         if(asks.find(price) != asks.end()) {
                    auto& orderList = bids[price];
                    for(auto it = orderList.begin(); it != orderList.end(); ++it) {
                        if(it->orderId==order.orderId) {
                            if(price > 0.0) it->price = newPrice;
                            if(newQty > 0) it->qty = newQty;
                            // TODO: Create a pubsub
                            #ifdef PUBSUB_ENABLED
                            notify(BookMsg::MODIFY);
                            #endif
                            return;
                        }
                    }
                }
     }
}

// TODO: Notification service for downstream program
void MapLLOrderBook::subscribe(OrderBookListener* listener) {
    listeners.push_back(listener);
}

void MapLLOrderBook::unsubscribe(OrderBookListener* listener) {
    listeners.erase(remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

void MapLLOrderBook::notify(const BookMsg msg) {
    for(OrderBookListener* listener: listeners) {
         listener->onOrderBookUpdate(msg);
    }
}

// TODO: Debug and logging
void MapLLOrderBook::showBook() {

    for (auto bid: bids)
    {
        double price = bid.first;
        uint32_t qty = 0;
        for (auto order: bid.second)
        {
            qty+= order.qty;
        }
        std::cout<<price<<"  ->  "<<qty<<std::endl;
    }

    std::cout<<std::endl;

    for (auto ask:asks)
    {
        double price = ask.first;
        uint32_t qty = 0;
        for (auto order: ask.second)
        {
            qty+= order.qty;
        }
        std::cout<<price<<"  ->  "<<qty<<std::endl;
    }
}

AbstractOrderBook::~AbstractOrderBook() = default;
