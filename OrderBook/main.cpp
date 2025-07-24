#include "OrderBook.hpp"
#include "Order.hpp"

int main() {
    AbstractOrderBook* book = new LocalOrderBook();

    Order o1 = Order("1", "1", 2.4, 3, Side::BUY, OrderType::LIMIT);

    book->openOrder(o1);
    book->modifyOrder(o1, 3, 300);
    book->closeOrder(o1);
    return 0;
}