cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
SET(QPCPP "$ENV{QPCPP}")
SET(QP_PORT_DIR "${QPCPP}/ports/posix")
SET(QTOOLS "$ENV{QTOOLS}")

PROJECT(gps_importer)

INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(${QPCPP}/include)
INCLUDE_DIRECTORIES(${QPCPP}/source)
INCLUDE_DIRECTORIES(${QTOOLS}/qspy/include)
INCLUDE_DIRECTORIES(${QP_PORT_DIR})

ADD_DEFINITIONS(-DQ_SPY)

ADD_EXECUTABLE(gps_importer
  main.cpp
  util.cpp
  bsp.cpp
  io_mgr.cpp
  database.cpp
  ${QTOOLS}/qspy/source/qspy.c)

TARGET_LINK_LIBRARIES(gps_importer
  qp
  PocoFoundation
  glog
  pthread)

SET(QP_SRC
  ${QPCPP}/source/qep_hsm.cpp
  ${QPCPP}/source/qep_msm.cpp
  ${QPCPP}/source/qf_act.cpp
  ${QPCPP}/source/qf_actq.cpp
  ${QPCPP}/source/qf_defer.cpp
  ${QPCPP}/source/qf_dyn.cpp
  ${QPCPP}/source/qf_mem.cpp
  ${QPCPP}/source/qf_pkg.h
  ${QPCPP}/source/qf_ps.cpp
  ${QPCPP}/source/qf_qact.cpp
  ${QPCPP}/source/qf_qeq.cpp
  ${QPCPP}/source/qf_qmact.cpp
  ${QPCPP}/source/qf_time.cpp
  ${QPCPP}/source/qk_pkg.h
  ${QPCPP}/source/qs_64bit.cpp
  ${QPCPP}/source/qs.cpp
  ${QPCPP}/source/qs_fp.cpp
  ${QPCPP}/source/qs_pkg.h
  ${QP_PORT_DIR}/qf_port.cpp)

ADD_LIBRARY(qp STATIC ${QP_SRC})

ADD_SUBDIRECTORY(test)
