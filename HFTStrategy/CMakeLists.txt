add_library(HFTStrategyLib src/Strategy.cpp)

target_include_directories(HFTStrategyLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(HFTStrategyLib PUBLIC OrderBookLib PubSubLib)

# OPTIONAL: only if you want to run pubsub individually
#add_executable(HFTStrategyExe main.cpp)
#target_link_libraries(HFTStrategyExe PRIVATE HFTStrategyLib)
#target_include_directories(HFTStrategyExe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)