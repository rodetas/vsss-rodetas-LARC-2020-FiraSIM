project(SDK_Rodetas)
cmake_minimum_required(VERSION 2.6)

OPTION(TESTS "build tests" OFF)

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
include_directories(includes includes/strategies)
include_directories(src src/strategies)
include_directories(usr/local/include)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INCLUDE includes/*.h)

ADD_LIBRARY(core ${SRC} ${INCLUDE})

SET (VSS_CORE libvss-core.so)

ADD_EXECUTABLE(SDK-Rodetas src/Main.cpp)

TARGET_LINK_LIBRARIES(core ${VSS_CORE} ${PROTOBUF_LIBRARY} ${PROTOBUF_LIBRARIES} ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(SDK-Rodetas core)

# USAGE: cmake -D TESTS=ON ..

if(TESTS)
    enable_testing()

    # Tests. *-test.cpp should be added here.
    add_executable(tests
           test/MainTest.cpp test/RobotStrategyTest.cpp test/TransmissionTests.h )

    # Link core, pthread and gtest to test.
    target_link_libraries(tests
            pthread
            core)

endif()
