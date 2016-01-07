project(tests)

include_directories(lib/mocks)

add_subdirectory(lib/gtest-1.7.0)
add_subdirectory(lib/mocks)
add_subdirectory(cases)