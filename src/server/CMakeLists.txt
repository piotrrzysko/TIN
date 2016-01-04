set (server_SRCS
        server_main.cpp
        UDPServer.cpp
        TCPServer.cpp
        TCPServer.hpp
        ServerController.cpp
        ServerController.hpp)

add_executable (server ${server_SRCS})
set_target_properties(server PROPERTIES ENABLE_EXPORTS true)
target_link_libraries (server common)
