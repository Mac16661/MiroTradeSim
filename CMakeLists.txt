cmake_minimum_required(VERSION 3.16)
project(MicroTradeSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Downloading and installing websocketpp
include(FetchContent)
FetchContent_Declare(
  websocketpp
  GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(websocketpp)

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system chrono thread)
list(APPEND CMAKE_PREFIX_PATH "/home/mac/vcpkg/installed/x64-linux")
find_package(nlohmann_json CONFIG REQUIRED)

if (OPENSSL_FOUND)
    message(STATUS "Found OpenSSL: ${OPENSSL_VERSION}")
    include_directories(${OPENSSL_INCLUDE_DIR})
else()
    message(FATAL_ERROR "OpenSSL not found!")
endif()

# Add subdirectories
add_subdirectory(PubSub)
add_subdirectory(OrderBook)
add_subdirectory(HFTStrategy)

# Main application
add_executable(MicroTradeSim main.cpp
        utils/MarketWebSocket.hpp)

# Link everything properly
target_link_libraries(MicroTradeSim
    PUBLIC
        PubSubLib
        OrderBookLib
        HFTStrategyLib
        ssl
        crypto
        Boost::system
        Boost::thread
        Boost::chrono
        nlohmann_json::nlohmann_json
)
target_include_directories(MicroTradeSim PUBLIC ${websocketpp_SOURCE_DIR})
