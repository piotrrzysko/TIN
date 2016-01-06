set (client_SRCS
        UDPClient.cpp
        TCPClient.cpp
        ReceivedVideoFile.cpp
        ClientController.cpp)

set (client_HEADERS
        UDPClient.hpp
        TCPClient.hpp
        ReceivedVideoFile.hpp
        ClientController.hpp)

find_package(Threads REQUIRED)
add_library (lclient ${client_SRCS} ${client_HEADERS})
target_link_libraries (lclient common ${CMAKE_THREAD_LIBS_INIT})
