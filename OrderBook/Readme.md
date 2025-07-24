# Multi-Order order book

This Limit Order Book is developed in C++ from scratch and able to handle over 1,400,000 TPS (transactions per second) Market and Limit orders.

Performance testing of the order book was also quite a challenging task as it required getting order data for testing, performing the testing to collect latency statistics.All functionality testing was completed thorough a set of unit tests and integration tests using GoogleTest.

## How to Build & Run test
``` 
mkdir build && cd build
cmake ..
make
ctest
```

## Order Types
Market Order - Orders to buy or sell at the best market price.\
Limit Order (Add, Modify & Cancel) - Orders to buy or sell at the defined limit price and that does not produce trades instantly.

## Data Structures: Ordered maps with Set

Add Order – O(log n) + O(1):
Find the price level in the map (O(log n)). If it exists, insert the order into the unordered_set at that level (O(1) average case).

Cancel Order – O(log n) + O(1):
Search for the price level in the map (O(log n)), then remove the specific order from the unordered_set (O(1) average case).

Modify Order – O(log n) + O(1):
Locate the price level in the map (O(log n)), find and update the order in the unordered_set (O(1) average case).

Ordered Map + List time complexity (previous implementation) -> O(log n) + O(log m) for Cancel and Modify Orders. Able to handle 1.4M+ transactions pre seconds.  

## Design Patterns Used
Builder Pattern:
Enables support for various exchanges (with differing message formats).

Publisher/Subscriber Pattern:
Allows downstream engines to subscribe to updates without tight coupling.

Lock-Free Ring Buffer:
Can be used instead of Pub/Sub for ultra-low latency consumption.

## Future Improvements
Use min/max heaps for fast level-top access or lock free buffers

Integrate with real exchange feeds via WebSocket/FIX

Add snapshot synchronization with the exchanges

Make it multithread and thread safe