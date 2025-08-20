#include "Strategy.hpp"

void ArbitrageStrategy::executeTrade()  {
        // std::cout<<"Check for arbitrage strategy"<<std::endl;
}

void ArbitrageStrategy::onOrderBookUpdate(const BookMsg& msg)  {
        // std::cout<<"Run Arbitrage strategy"<<std::endl;
        executeTrade();
}
