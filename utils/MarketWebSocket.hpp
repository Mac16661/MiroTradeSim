#pragma once

#include <iostream>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl.hpp>
#include <nlohmann/json.hpp>

using client = websocketpp::client<websocketpp::config::asio_tls_client>;
using websocketpp::connection_hdl;

// TODO: MarketWebSocket interface


// TODO: Binance sockets which should inherit the market interface
class BinanceWebSocket
{
public:
    BinanceWebSocket(AbstractOrderBook* bookPtr) {
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
        m_endpoint.set_pong_handler(std::bind(&BinanceWebSocket::on_pong, this, std::placeholders::_1, std::placeholders::_2));
        m_endpoint.set_ping_handler(std::bind(&BinanceWebSocket::on_ping, this, std::placeholders::_1, std::placeholders::_2));

        book = bookPtr;
    }

    void run(const std::string& uri) {
        websocketpp::lib::error_code ec;
        client::connection_ptr con = m_endpoint.get_connection(uri, ec);

        if (ec) {
            std::cout << "Could not create connection: " << ec.message() << std::endl;
            return;
        }

        m_endpoint.connect(con);
        m_endpoint.run();
    }

    private:
    void on_open(websocketpp::connection_hdl hdl) {
        std::cout << "Connected to Binance!" << std::endl;
        // TODO: On connection open it should take snapshort of current order book for each symbole(or may be not required)
    }

    void on_message(websocketpp::connection_hdl, client::message_ptr msg) {
        nlohmann::json j = nlohmann::json::parse(msg->get_payload());

        // TODO: Update bids and asks of each order book on receiving data
        if(j["stream"] == "btcusdc@depth20@100ms") {
            // std::cout<<"BTCUSDC:: "<< j.dump(2)<< "\n\n\n";
        }else if(j["stream"] == "btcusdt@depth20@100ms") {

            // std::cout<<"BTCUSDT:: "<< j.dump(2)<< "\n\n\n";
            // !TESTING UPDATE BIDS AND ASK FOR ONLY ONE BOOK
            // std::cout<<j["data"]["asks"]<<std::endl<<std::endl;
            // std::cout<<j["data"]["bids"]<<std::endl<<std::endl;
            book->updateAsks(j["data"]["asks"]);
            book->updateBids(j["data"]["bids"]);

        }else if(j["stream"] == "btcfdusd@depth20@100ms") {
            // std::cout<<"BTCFDUSD:: "<< j.dump(2)<< "\n\n\n";
        }

        // book->updateAsks(j["data"]["asks"]);
        // book->updateBids(j["data"]["bids"]);
        
    }

    void on_close(websocketpp::connection_hdl) {
        std::cout << "Connection closed!" << std::endl;
    }

    bool on_ping(websocketpp::connection_hdl hdl, std::string payload) {
        // std::cout << "Ping received: " << payload << std::endl;
        return true;
    }

    void on_pong(websocketpp::connection_hdl hdl, std::string payload) {
        // std::cout << "Pong received: " << payload << std::endl;
    }

    client m_endpoint;
    websocketpp::connection_hdl m_hdl;
    // TODO: We will have multipe books so unordered_map or vector with type -> AbstractOrderBook
    AbstractOrderBook* book; 
};