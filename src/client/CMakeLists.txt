set (client_SRCS
        client_main.cpp
        UDPClient.cpp UDPClient.hpp)

add_executable (client ${client_SRCS})
target_link_libraries (client common)