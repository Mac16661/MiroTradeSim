#pragma once

#define PUBSUB_ENABLED

#include <vector>

// TODO: Need to make it thread safe
// TODO: Observer pattern -> not implementing subject interface because for each event we need to be notified

enum class BookMsg {
    OPEN,
    CLOSE,
    MODIFY
};

// TODO: Strategy need to listen to this by implement this virtual function
// Subscriber interface
class OrderBookListener {
    public:
        virtual void onOrderBookUpdate(const BookMsg& mag) = 0;
        virtual ~OrderBookListener() = default;
};




