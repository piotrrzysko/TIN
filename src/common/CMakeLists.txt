set (common_SRCS
        consts.hpp
        MulticastUtils.cpp
        MulticastUtils.hpp
        SocketFactory.cpp
        SocketFactory.hpp
        Parser.cpp
        Parser.hpp
        Args.cpp
        Args.hpp
        VideoFile.hpp
        VideoFile.cpp)

add_library (common ${common_SRCS})
