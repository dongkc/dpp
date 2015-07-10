cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")
SET( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
SET(QPCPP "$ENV{QPCPP}")
SET(QP_PORT_DIR "${QPCPP}/ports/posix")
SET(QTOOLS "$ENV{QTOOLS}")

PROJECT(gps_importer)

INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(${QPCPP}/include)
INCLUDE_DIRECTORIES(${QTOOLS}/qspy/include)
INCLUDE_DIRECTORIES(${QP_PORT_DIR})

ADD_DEFINITIONS(-DQ_SPY)

ADD_EXECUTABLE(gps_importer
  main.cpp
  bsp.cpp
  philo.cpp
  table.cpp
  ${QTOOLS}/qspy/source/qspy.c)

TARGET_LINK_LIBRARIES(gps_importer
  ${QPCPP}/ports/posix/spy/libqp.a
pthread)
