#include <iostream>
#include <ostream>

#include "OrderBook.hpp"


// Batch bids asks entry
void MapOrderBook::updateAsks(std::vector<std::vector<std::string>> _asks) {
    // TODO: Need to make this function atomic or thread safe
    asks.clear();

        for (const auto& ask : _asks) {
            if (ask.size() < 2) continue;  // skip invalid entries
            try {
                double price = std::stod(ask[0]);
                asks[price] = {ask[0], ask[1]};
            } catch (const std::exception& e) {
                // Handle invalid string-to-double conversion
                continue;
            }
        }
}

void MapOrderBook::updateBids(std::vector<std::vector<std::string>> _bids) {
    // TODO: Need to make this function atomic or thread safe
    bids.clear();

        for (const auto& bid : _bids) {
            if (bid.size() < 2) continue;  // skip invalid entries
            try {
                double price = std::stod(bid[0]);
                bids[price] = {bid[0], bid[1]};
            } catch (const std::exception& e) {
                // Handle invalid string-to-double conversion
                continue;
            }
        }
}


// Notification service for downstream program
void MapOrderBook::subscribe(OrderBookListener* listener) {
    listeners.push_back(listener);
}

void MapOrderBook::unsubscribe(OrderBookListener* listener) {
    listeners.erase(remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

void MapOrderBook::notify(const BookMsg msg) {
    for(OrderBookListener* listener: listeners) {
         listener->onOrderBookUpdate(msg);
    }
}

// Debug and logging
void MapOrderBook::showBook() {
    std::cout<<"ORDER BOOK\n\n"<<std::endl;

    for(auto bid:bids) {
        std::cout<<bid.second.first<<"\t\t\t"<<bid.second.second<<std::endl;
    }

    
    std::cout<<"\n"<<std::endl;

    for(auto ask:asks) {
        std::cout<<ask.second.first<<"\t\t\t"<<ask.second.second<<std::endl;
    }

    std::cout<<"\n\n"<<std::endl;
}

AbstractOrderBook::~AbstractOrderBook() = default;
