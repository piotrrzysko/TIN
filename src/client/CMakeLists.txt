set (client_SRCS
        client_main.cpp
        UDPClient.cpp
        TCPClient.cpp
        ReceivedVideoFile.cpp
        ClientController.cpp)

find_package(Threads REQUIRED)
add_executable (client ${client_SRCS})
set_target_properties(client PROPERTIES ENABLE_EXPORTS true)
target_link_libraries (client common ${CMAKE_THREAD_LIBS_INIT})
