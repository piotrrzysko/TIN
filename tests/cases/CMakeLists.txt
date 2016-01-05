include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set (CMAKE_CXX_FLAGS "-Wall -std=c++11 -pthread -Wno-write-strings")
add_executable(runTests
        server_tests.cpp common_tests.cpp client_tests.cpp)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests client common server)