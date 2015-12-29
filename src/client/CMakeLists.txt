set (client_SRCS
        client_main.cpp
        UDPClient.cpp UDPClient.hpp
        TCPClient.cpp TCPClient.hpp Parser.cpp Parser.hpp ReceivedVideoFile.cpp ReceivedVideoFile.hpp)

add_executable (client ${client_SRCS})
target_link_libraries (client common)