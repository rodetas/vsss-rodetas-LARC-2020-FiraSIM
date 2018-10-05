cmake_minimum_required(VERSION 2.6)

OPTION(TESTS "build tests" OFF)

project(SDK_Rodetas)

SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -o2 -pthread")

FIND_PACKAGE(PkgConfig)
FIND_PACKAGE(Protobuf REQUIRED)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-2.4)

INCLUDE(FindProtobuf)
include_directories(${PROTOBUF_INCLUDE_DIR} ${GTKMM_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})
include_directories(includes includes/Strategies includes/Communication includes/Positioning)
include_directories(src src/Strategies src/Communication src/Positioning)

include_directories(usr/local/include)
include_directories(usr/local/glade)

link_libraries(${GTKMM_LIBRARIES})
link_directories(/usr/lib ${GTKMM_LIBRARY_DIRS})

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INCLUDE includes/*.h)

ADD_LIBRARY(core ${SRC} ${INCLUDE} includes/Strategies/RobotStrategyDefenderLeft.h includes/Strategies/RobotStrategyDefenderRight.h includes/Strategies/RobotStrategySideAttack.h src/Strategies/RobotStrategySideAttack.cpp src/Strategies/RobotStrategyDefenderLeft.cpp  src/Strategies/RobotStrategyDefenderRight.cpp includes/Strategies/RobotStrategyCenterAttack.h src/Strategies/RobotStrategyCenterAttack.cpp includes/Strategies/RobotStrategyForwardAttack.h src/Strategies/RobotStrategyForwardAttack.cpp includes/Strategies/RobotStrategyAttackDefense.h src/Strategies/RobotStrategyAttackDefense.cpp)

SET (VSS_CORE libvss-core.so)

ADD_EXECUTABLE(SDK-Rodetas src/Main.cpp src/Strategies/RobotStrategyDefenderLeft.cpp includes/Strategies/RobotStrategyDefenderLeft.h includes/Strategies/RobotStrategySideAttack.h src/Strategies/RobotStrategySideAttack.cpp includes/Strategies/RobotStrategyCenterAttack.h src/Strategies/RobotStrategyCenterAttack.cpp includes/Strategies/RobotStrategyForwardAttack.h src/Strategies/RobotStrategyForwardAttack.cpp includes/Strategies/RobotStrategyAttackDefense.h src/Strategies/RobotStrategyAttackDefense.cpp)

TARGET_LINK_LIBRARIES(core ${VSS_CORE} ${GTKMM_LIBRARIES} ${PROTOBUF_LIBRARY} ${PROTOBUF_LIBRARIES} ${Boost_LIBRARIES})

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
