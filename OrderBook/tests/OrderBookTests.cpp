#include "OrderBook.hpp"
#include "Order.hpp"
#define GTEST_PRINT_TO_STDOUT 1
#include<gtest/gtest.h>
#include <chrono>
#include <iostream>
#include <vector>

// Sample test case
TEST(SampleTest, AddFunction) {
    EXPECT_EQ(1, 1);
}

TEST(CreateOrderTest, AddOrderFunction) {
    AbstractOrderBook* book = new MapLLOrderBook();

    Order o1 = Order("1", "1", 2.4, 3, Side::BUY, OrderType::LIMIT);

    book->openOrder(o1);

    // TODO: Need to build some print and get function to test these cases properly
    EXPECT_EQ(o1.userId, "1");
}

TEST(CloseOrderTest, CloseOrderFunction) {
    AbstractOrderBook* book = new MapLLOrderBook();

    Order o1 = Order("1", "1", 2.4, 3, Side::BUY, OrderType::LIMIT);

    book->closeOrder(o1);

    // TODO: Need to build some print and get function to test these cases properly:: SPECIALLY THIS ONE
    EXPECT_EQ(o1.userId, "1");
}

TEST(ModifyOrderTest, ModifyOrderFunction) {
    AbstractOrderBook* book = new MapLLOrderBook();

    Order o1 = Order("1", "1", 2.4, 3, Side::BUY, OrderType::LIMIT);

    book->modifyOrder(o1, 3, 300);

    // TODO: Need to build some print and get function to test these cases properly
    // EXPECT_EQ(o1.price, 3);
    // EXPECT_EQ(o1.qty, 300);

    // TODO: Need to build some print and get function to test these cases properly:: SPECIALLY THIS ONE
    EXPECT_EQ(o1.userId, "1");
}

TEST(ThroughputTest, PerformanceTestingFunction) {
    int n=1400000; // 1.4 million operations

    // Initializing our order book
    AbstractOrderBook* book = new MapLLOrderBook();
    // For additional testing
    std::vector<Order> orders(n);

    // TODO: Performance test of 1.4M add operations
    // Start the high resolution timer
    auto start = std::chrono::high_resolution_clock::now();

    for(int i=0; i<n; i++) {
        std::string id = std::to_string(i);
        Order o1 = Order(id, id , 2.4+i, 300+i, Side::BUY, OrderType::LIMIT);
        book->openOrder(o1);
        orders[i] = o1;
    }

    // End the high resolution timer
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    double tps =  n / duration.count();

    // Add ops of 1.4M order should be complete in  Less Then 1 second
    EXPECT_LT(duration.count(), 1.0);

    //TODO: Performance test of remove operation of 1.4M openOrders
     start = std::chrono::high_resolution_clock::now();

        for(int i=0; i<n; i++) {
            std::string id = std::to_string(i);
            Order o1 = orders[i];
            book->closeOrder(o1);
        }

        // End the high resolution timer
        end = std::chrono::high_resolution_clock::now();

        duration = end - start;

        tps =  n / duration.count();

        // close order ops of 1.4M order should be complete in  Less Then 1 second
        EXPECT_LT(duration.count(), 1.0);
}