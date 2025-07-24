cmake_minimum_required(VERSION 3.10)
project(OrderBook)

set(CMAKE_CXX_STANDARD 17)

# ADD SOURCE CODE
add_subdirectory(src)

# ADD TEST
enable_testing()
add_subdirectory(tests)