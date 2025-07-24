add_library(book OrderBook.cpp) # Use book to link with other lib
target_include_directories(book PUBLIC ${CMAKE_SOURCE_DIR}/include)