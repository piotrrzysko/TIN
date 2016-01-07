project (AdvertCast)
cmake_minimum_required(VERSION 2.8.7)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${PROJECT_SOURCE_DIR}/cmake)
include(CMakeExtraBootstrap)

set (CMAKE_CXX_FLAGS "-Wall -std=c++11 -pthread")

option(TESTS "Turn on tests" OFF)


include_directories (${AdvertCast_SOURCE_DIR}/src)
set (EXECUTABLE_OUTPUT_PATH "${AdvertCast_BINARY_DIR}/bin")
set (LIBRARY_OUTPUT_PATH "${AdvertCast_BINARY_DIR}/lib")

if (TESTS)
    include(GCoveralls)
    enable_gcoveralls()
    link_libraries(gcov)
    add_subdirectory (tests)
endif()

add_subdirectory (src)

add_executable(client src/client/client_main.cpp)
target_link_libraries(client lclient)
add_executable(server src/server/server_main.cpp)
target_link_libraries(server lserver)

install (DIRECTORY data DESTINATION "${AdvertCast_BINARY_DIR}")
