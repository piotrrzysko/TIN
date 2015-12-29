set (common_SRCS
        consts.hpp MulticastUtils.cpp MulticastUtils.hpp
        SocketFactory.cpp SocketFactory.hpp)

add_library (common ${common_SRCS})