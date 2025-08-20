#include "OrderBook.hpp"
#include "PubSub.hpp"
#include "Strategy.hpp"
#include <iostream>
#include <string>

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl.hpp>

const std::string URL = "wss://fstream.binance.com/stream?streams="; // <symbol>@depth<levels>@100ms

using client = websocketpp::client<websocketpp::config::asio_tls_client>;
using websocketpp::connection_hdl;

// TODO: Binance sockets
class BinanceWebSocket
{
public:
    BinanceWebSocket() {
        // Initialize ASIO
        m_endpoint.init_asio();

        // TLS handler
        m_endpoint.set_tls_init_handler([this](websocketpp::connection_hdl) {
            auto ctx = std::make_shared<boost::asio::ssl::context>(
                boost::asio::ssl::context::tls_client
            );
            ctx->set_default_verify_paths();
            ctx->set_verify_mode(boost::asio::ssl::verify_peer);
            return ctx;
        });

        // Bind handlers
        m_endpoint.set_open_handler(std::bind(&BinanceWebSocket::on_open, this, std::placeholders::_1));
        m_endpoint.set_message_handler(std::bind(&BinanceWebSocket::on_message, this, std::placeholders::_1, std::placeholders::_2));
        m_endpoint.set_close_handler(std::bind(&BinanceWebSocket::on_close, this, std::placeholders::_1));

        // Ping / Pong handlers
        m_endpoint.set_pong_handler(std::bind(&BinanceWebSocket::on_pong, this, std::placeholders::_1, std::placeholders::_2));
        m_endpoint.set_ping_handler(std::bind(&BinanceWebSocket::on_ping, this, std::placeholders::_1, std::placeholders::_2));
    }

    void run(const std::string& uri) {
        websocketpp::lib::error_code ec;
        client::connection_ptr con = m_endpoint.get_connection(uri, ec);

        if (ec) {
            std::cout << "❌ Could not create connection: " << ec.message() << std::endl;
            return;
        }

        m_endpoint.connect(con);
        m_endpoint.run();
    }

    private:
    void on_open(websocketpp::connection_hdl hdl) {
        std::cout << "Connected to Binance!" << std::endl;
    }

    void on_message(websocketpp::connection_hdl, client::message_ptr msg) {
        // std::cout << "MSG:: " << msg->get_payload() << std::endl;
    }

    void on_close(websocketpp::connection_hdl) {
        std::cout << "Connection closed!" << std::endl;
    }

    bool on_ping(websocketpp::connection_hdl hdl, std::string payload) {
        std::cout << "Ping received: " << payload << std::endl;
        return true;
    }

    void on_pong(websocketpp::connection_hdl hdl, std::string payload) {
        std::cout << "Pong received: " << payload << std::endl;
    }

    client m_endpoint;
    websocketpp::connection_hdl m_hdl;
};


int main() {
    HFTStrategy* ab = new ArbitrageStrategy();
    MapLLOrderBook* book = new MapLLOrderBook();
    // book->subscribe(dynamic_cast<OrderBookListener*>(ab));
    // for(int i=0; i<15; i++) {
    //     Side s;
    //     if (i%2==0) s = Side::BUY;
    //     else s = Side::SELL;
    //     std::string id = std::to_string(i);
    //     Order o1 = Order(id, id , 2.4+i, 300+i, s, OrderType::LIMIT);
    //     book->openOrder(o1);
    // }
    // book->showBook();

    // =================================================================================================================
    // Binance web scoket implementation
    BinanceWebSocket wss;
    // wss.run("wss://stream.binance.com:9443/ws/btcusdt@depth20@100ms");
    wss.run("wss://fstream.binance.com/stream?streams=bnbusdt@aggTrade/btcusdt@markPrice");
    return 0;

    return 0;

}