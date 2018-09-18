project(zmqwrap_lib)
cmake_minimum_required(VERSION 2.8)

# This won't be needed with recent cmake versions.
add_definitions(-std=c++11)

find_package(Threads)

include (cmake/FatalWarnings.cmake)
ADM_EXTRA_WARNINGS()

FIND_LIBRARY(ZMQ_LIB NAMES zmq)

if (MSVC)
  FIND_PATH(ZMQ_INCLUDE_DIR NAMES zmq.hpp)
endif (MSVC)

message(STATUS "ZMQ found => " "${ZMQ_LIB}")

set(zmq_wrapper_lib_sources
  zmqwrap_base.cpp
  zmqwrap_pub.cpp
  zmqwrap_sub.cpp
)

add_library(zmqwrap_lib ${zmq_wrapper_lib_sources})

if (MSVC)
  include_directories(${ZMQ_INCLUDE_DIR})
endif (MSVC)

install (TARGETS zmqwrap_lib DESTINATION lib)

set(headers_to_install
  zmqwrap_base.hpp  zmqwrap_pull.hpp  zmqwrap_sub.hpp
  zmqwrap_pub.hpp   zmqwrap_push.hpp)

install (FILES ${headers_to_install} DESTINATION include/adm_zmq)
install (FILES third_party/zmq.hpp DESTINATION include/adm_zmq/third_party)

SET(BUILD_TESTS OFF CACHE STRING "Disable tests by default. You can override this passing -DBUILD_TESTS=ON to cmake")

if (BUILD_TESTS)
  include(CTest)

  add_executable(test_pubsub test_pubsub.cpp)
  target_link_libraries(test_pubsub zmqwrap_lib)
  target_link_libraries(test_pubsub
                        gtest_main gtest
                        ${CMAKE_THREAD_LIBS_INIT}
                        ${ZMQ_LIB})
  add_test(NAME test_pubsub COMMAND test_pubsub)

  add_executable(test_pushpull test_pushpull.cpp)
  target_link_libraries(test_pushpull zmqwrap_lib)
  target_link_libraries(test_pushpull
                        gtest_main gtest
                        ${CMAKE_THREAD_LIBS_INIT}
                        ${ZMQ_LIB})
  add_test(NAME test_pushpull COMMAND test_pushpull)
endif()
