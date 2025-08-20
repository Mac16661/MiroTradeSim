#pragma once
// TODO: Listens to PubSub msg(which will trigger on order book update) and execute order
#include "PubSub.hpp"
#include <iostream>

class HFTStrategy {
    public:
        virtual void executeTrade() = 0;
        virtual ~HFTStrategy() = default;
};

class ArbitrageStrategy: public HFTStrategy, public OrderBookListener {
    public:
        void executeTrade() override;
        void onOrderBookUpdate(const BookMsg& msg) override;
};