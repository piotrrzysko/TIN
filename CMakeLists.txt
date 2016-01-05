project (AdvertCast)
cmake_minimum_required(VERSION 2.8.7)

set (CMAKE_CXX_FLAGS "-Wall -std=c++11 -pthread")

option(COVERALLS "Turn on coveralls support" OFF)
option(COVERALLS_UPLOAD "Upload the generated coveralls json" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${PROJECT_SOURCE_DIR}/cmake)

if (COVERALLS)
    include(Coveralls)
    coveralls_turn_on_coverage()
endif()

include_directories (${AdvertCast_SOURCE_DIR}/src)
set (EXECUTABLE_OUTPUT_PATH "${AdvertCast_BINARY_DIR}/bin")
set (LIBRARY_OUTPUT_PATH "${AdvertCast_BINARY_DIR}/lib")

add_subdirectory (src)
add_subdirectory (tests)

if (COVERALLS)
    file(GLOB cov_SRC
            "src/client/*.cpp"
            "src/common/*.cpp"
            "src/server/*.cpp"
            )
    coveralls_setup(
            "${cov_SRC}"
            ${COVERALLS_UPLOAD}
            "${PROJECT_SOURCE_DIR}/cmake")
endif()

install (DIRECTORY data DESTINATION "${AdvertCast_BINARY_DIR}")
