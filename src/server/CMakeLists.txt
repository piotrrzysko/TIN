set (server_SRCS
        server_main.cpp
        UDPServer.cpp
        )

add_executable (server ${server_SRCS})
target_link_libraries (server common)