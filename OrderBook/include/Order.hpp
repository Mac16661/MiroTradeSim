#pragma once
#include <string>
#include <chrono>

enum class Side { BUY, SELL };
enum class OrderType { LIMIT, MARKET };

struct Order {
    std::string orderId;
    std::string userId;
    double price;
    uint32_t qty;
    Side side;
    OrderType type;
    long long timestamp;

    Order() = default;
    Order(std::string oid, std::string uid = "", double _price = 0.0, std::uint32_t _qty = 0, Side _side = Side::BUY, OrderType _type = OrderType::LIMIT)
        : orderId(std::move(oid)), userId(std::move(uid)), price(_price), qty(_qty), side(_side), type(_type) {
        timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
};
