project (AdvertCast)
cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_FLAGS "-Wall -std=c++11 -lpthread")

include_directories (${AdvertCast_SOURCE_DIR}/src)
set (EXECUTABLE_OUTPUT_PATH "${AdvertCast_BINARY_DIR}/bin")
set (LIBRARY_OUTPUT_PATH "${AdvertCast_BINARY_DIR}/lib")

add_subdirectory (src)

install (DIRECTORY data DESTINATION "${AdvertCast_BINARY_DIR}")