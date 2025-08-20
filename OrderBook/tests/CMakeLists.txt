# Download GoogleTest at configure time
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(runOrderBookTest OrderBookTests.cpp)
target_link_libraries(runOrderBookTest gtest_main Book)

include(GoogleTest)
gtest_discover_tests(runOrderBookTest)