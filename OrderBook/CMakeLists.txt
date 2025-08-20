add_library(OrderBookLib src/OrderBook.cpp)

target_include_directories(OrderBookLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(OrderBookLib PUBLIC PubSubLib)

# OPTIONAL: make independent executable
#add_executable(OrderBookExe main.cpp)
#target_link_libraries(OrderBookLib PUBLIC PubSubLib)
#target_include_directories(OrderBookExe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)