# MicroTradeSim

### Overview

MicroTradeSim is a modular trading system designed with a strong focus on design patterns to ensure scalability, maintainability, and adaptability across multiple exchanges.

It supports:

Multi-exchange connectivity

Multiple trading strategies

Trade lifecycle management

### Design Patterns Used
#### Adapter Pattern

Used for integrating with different exchanges by adapting their APIs into a common interface.

BinanceExchangeAdapter

CoinbaseExchangeAdapter

#### Factory Pattern

OrderBookFactory provides flexible creation of different order book implementations:

HashmapBook

DualHeapBook

LockFreeOrderBook

#### Strategy Pattern

Defines interchangeable trading strategies:

ArbitrageStrategy

MarketMakingStrategy

#### Singleton Pattern

Ensures a single instance of the trade lifecycle manager:

TradeLifecycleManager

### System Workflow

Exchange Adapters

Convert raw exchange data (Binance, Coinbase, etc.) into a unified format.

OrderBook Factory

Creates the appropriate order book data structure (Hashmap, Heap, Lock-free, etc.).

Strategies

Strategies like Arbitrage or Market Making consume order book data and make trading decisions.

Trade Lifecycle Manager

Manages trade execution, monitoring, and closing in a consistent manner across exchanges.

#### Components Interaction
```bash
Exchange Adapter  --->  OrderBook Factory  --->  Strategy (Arbitrage/MarketMaking)  
         ↓                           ↓                         ↓
   Exchange Data               OrderBook Impl.        Trade Lifecycle Manager
```

### How to build and  run 

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=home/mac/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
./MicroTradeSim
