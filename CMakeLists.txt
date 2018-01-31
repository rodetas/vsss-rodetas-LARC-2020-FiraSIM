project(SDK_Rodetas)
cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -o2")

FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

include_directories(${PROTOBUF_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
include_directories(src src/strategies src/VSS-Interface)
include_directories(include include/Interfaces)
include_directories(usr/local/include)

file(GLOB_RECURSE SRC src/*.cpp)

set (VSS_INTERFACE libvss-interface.so)

ADD_EXECUTABLE(SDK-Rodetas ${SRC})

TARGET_LINK_LIBRARIES(SDK-Rodetas ${VSS_INTERFACE} ${PROTOBUF_LIBRARY} ${PROTOBUF_LIBRARIES})
TARGET_LINK_LIBRARIES(SDK-Rodetas LINK_PUBLIC ${Boost_LIBRARIES})

INSTALL(TARGETS SDK-Rodetas DESTINATION bin)