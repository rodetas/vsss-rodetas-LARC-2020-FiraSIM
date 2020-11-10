cmake_minimum_required(VERSION 2.6)

OPTION(TESTS "build tests" OFF)

project(SDK_Rodetas)

SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -o2 -pthread -std=gnu++11")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(PkgConfig)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Protobuf REQUIRED)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)


INCLUDE(FindProtobuf)
include_directories(${PROTOBUF_INCLUDE_DIR} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})
include_directories(includes includes/Strategies includes/Communication includes/Positioning net net/pb net/google)  
include_directories(src src/Strategies src/Communication src/Positioning net net/pb net/google)

include_directories(usr/local/include)
include_directories(usr/local/glade)

add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Network_DEFINITIONS})
add_definitions(${Qt5Core_DEFINITIONS})

link_libraries(${GTKMM_LIBRARIES})
link_directories(/usr/lib ${GTKMM_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

file(GLOB_RECURSE SRC src/*.cpp net/*.cpp net/*.pb.cc)
file(GLOB_RECURSE INCLUDE includes/*.h net/*.h net/*.pb.h)

ADD_LIBRARY(core ${SRC} ${INCLUDE})

SET (VSS_CORE libvss-core.so)


ADD_EXECUTABLE(SDK-Rodetas src/Main.cpp)



TARGET_LINK_LIBRARIES(core ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES} ${VSS_CORE} ${GTKMM_LIBRARIES} ${PROTOBUF_LIBRARY} ${PROTOBUF_LIBRARIES} ${Boost_LIBRARIES})

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
