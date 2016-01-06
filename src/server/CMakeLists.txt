set (server_SRCS
        UDPServer.cpp
        UDPServer.hpp
        TCPServer.cpp
        TCPServer.hpp
        ServerController.cpp
        ServerController.hpp)

add_library (lserver ${server_SRCS})
target_link_libraries (lserver common)
