#include <iostream>
#include <string>
#include <chrono>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/chrono.hpp>

#include "OrderBook.hpp"
#include "PubSub.hpp"
#include "Strategy.hpp"
#include "utils/MarketWebSocket.hpp"

const std::string FEATURES_WS_URL = "wss://fstream.binance.com/stream?streams="; // <symbol>@depth<levels>@100ms
const std::string SPOT_WS_URL = "wss://stream.binance.com:9443/stream?streams=btcusdt@depth20@100ms/btcusdc@depth20@100ms/btcfdusd@depth20@100ms";
const std::string SPOT_FALLBACK_WS_URL = "wss://stream.binance.com:443";

void showOrderBook(AbstractOrderBook* book) {
   while(true){
    system("clear");
    book->showBook();
    boost::this_thread::sleep_for(boost::chrono::seconds(1));
   }
}

int main() {
    HFTStrategy* ab = new ArbitrageStrategy();
    AbstractOrderBook* book = new MapOrderBook("btcusdt"); // expecting name
    book->subscribe(dynamic_cast<OrderBookListener*>(ab));

    boost::thread worker_thread(showOrderBook, book);


    BinanceWebSocket wss = BinanceWebSocket(book);
    // wss.run("wss://stream.binance.com:9443/ws/btcusdt@depth20@100ms");
    // wss.run("wss://fstream.binance.com/stream?streams=bnbusdt@aggTrade/btcusdt@markPrice");
    wss.run(SPOT_WS_URL);

    worker_thread.join();
    // book->showBook();
    return 0;
}