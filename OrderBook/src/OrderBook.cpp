#include "OrderBook.hpp"

void LocalOrderBook::openOrder(const Order& order) {
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

}

void LocalOrderBook::closeOrder(const Order& order) {
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
                            return;
                        }
                    }
                }

    }
}

void LocalOrderBook::modifyOrder(const Order& order, double newPrice=0.0, uint32_t newQty=0) {
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
                    if(price != -1.0) it->price = newPrice;
                    if(newQty != -1) it->qty = newQty;

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

                            return;
                        }
                    }
                }
     }
}