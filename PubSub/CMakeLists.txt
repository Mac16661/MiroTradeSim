#add_library(PubSubLib src/PubSub.cpp)
#target_include_directories(PubSub PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# MORE CLEANER WAY: if it is header file only use interface to instead of implementation above
add_library(PubSubLib INTERFACE)
target_include_directories(PubSubLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


# OPTIONAL: only if you want to run pubsub individually
#add_executable(PubSubExe main.cpp)
#target_link_libraries(PubSubExe PRIVATE PubSubLib)
#target_include_directories(PubSubExe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)