set (server_SRCS
        server_main.cpp
        UDPServer.cpp
        TCPServer.cpp
        TCPServer.hpp
        VideoFile.hpp
        VideoFile.cpp)

add_executable (server ${server_SRCS})
target_link_libraries (server common)