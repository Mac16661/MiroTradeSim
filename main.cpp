#include <iostream>
#include <string>
#include <chrono>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/chrono.hpp>
#include <unordered_map>

#include "OrderBook.hpp"
#include "PubSub.hpp"
#include "Strategy.hpp"
#include "utils/MarketWebSocket.hpp"

const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";

const std::string FEATURES_WS_URL = "wss://fstream.binance.com/stream?streams="; // <symbol>@depth<levels>@100ms
const std::string SPOT_WS_URL = "wss://stream.binance.com:9443/stream?streams=btcusdt@depth20@100ms/btcusdc@depth20@100ms/btcfdusd@depth20@100ms";

const std::string SPOT_FALLBACK_WS_URL = "wss://stream.binance.com:443";

void showOrderBook(std::unordered_map<std::string, AbstractOrderBook*>& books) {
   while(true){
    system("clear");
    if(!books["btcusdt@depth20@100ms"]->isEmpty()) {
        auto bestBid = books["btcusdt@depth20@100ms"]->topBid();
        auto bestAsk = books["btcusdt@depth20@100ms"]->topAsk();
        std::cout<< BOLD << GREEN <<"BCTUSDT  "<<RESET<<GREEN <<bestBid.first <<RESET <<" ";
        std::cout<< RED <<bestAsk.first<<RESET <<std::endl<<std::endl;    

    }
    if(!books["btcusdc@depth20@100ms"]->isEmpty()) {
        auto bestBid = books["btcusdc@depth20@100ms"]->topBid();
        auto bestAsk = books["btcusdc@depth20@100ms"]->topAsk();
        std::cout<< BOLD << GREEN <<"BCTUSDC  "<<RESET<<GREEN <<bestBid.first <<RESET <<" ";
        std::cout<< RED <<bestAsk.first<<RESET <<std::endl<<std::endl;    
   
    }
    if(!books["btcfdusd@depth20@100ms"]->isEmpty()) {
        auto bestBid = books["btcfdusd@depth20@100ms"]->topBid();
        auto bestAsk = books["btcfdusd@depth20@100ms"]->topAsk();
        std::cout<< BOLD << GREEN <<"BCTFDUSD "<<RESET<<GREEN <<bestBid.first <<RESET <<" ";
        std::cout<< RED <<bestAsk.first <<RESET <<std::endl<<std::endl;
    
    }
    
    boost::this_thread::sleep_for(boost::chrono::seconds(1));
   }
}

int main() {
    HFTStrategy* ab = new ArbitrageStrategy();
    AbstractOrderBook* btcusdtbook = new MapOrderBook("btcusdt"); // expecting name
    AbstractOrderBook* btcusdcbook = new MapOrderBook("btcusdc");
    AbstractOrderBook* btcfdusdbook = new MapOrderBook("btcfusd");

    btcusdtbook->subscribe(dynamic_cast<OrderBookListener*>(ab));
    btcusdcbook->subscribe(dynamic_cast<OrderBookListener*>(ab));
    btcfdusdbook->subscribe(dynamic_cast<OrderBookListener*>(ab));

    std::unordered_map<std::string, AbstractOrderBook*> orderBooks = {
        {"btcusdt@depth20@100ms", btcusdtbook},
        {"btcusdc@depth20@100ms", btcusdcbook},
        {"btcfdusd@depth20@100ms", btcfdusdbook}
    };

    boost::thread worker_thread(showOrderBook, orderBooks);

    BinanceWebSocket wss = BinanceWebSocket(orderBooks);
    // wss.run("wss://stream.binance.com:9443/ws/btcusdt@depth20@100ms");
    // wss.run("wss://fstream.binance.com/stream?streams=bnbusdt@aggTrade/btcusdt@markPrice");
    wss.run(SPOT_WS_URL);

    worker_thread.join();
    return 0;
}