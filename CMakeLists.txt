cmake_minimum_required(VERSION 3.14)
project(bytetrack)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

option(WITH_TEST "Build test"  ON)
option(WITH_PYTHON "Build python bindings" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -MMD -Wall -Wextra -Winit-self")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

set(EIGEN3_ZIP "${CMAKE_CURRENT_SOURCE_DIR}/3rd/eigen-3.3.9.zip")
execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${EIGEN3_ZIP}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE EIGEN3_UNPACK_RESULT
    OUTPUT_VARIABLE EIGEN3_UNPACK_OUTPUT
    ERROR_VARIABLE EIGEN3_UNPACK_ERROR
)
if(NOT EIGEN3_UNPACK_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to unpack Eigen3:
        Output: ${EIGEN3_UNPACK_OUTPUT}
        Error: ${EIGEN3_UNPACK_ERROR}")
endif()

if(WITH_PYTHON)
  set(PYBIND11_ZIP "${CMAKE_CURRENT_SOURCE_DIR}/3rd/pybind11-2.10.4.zip")
  execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xzf ${PYBIND11_ZIP}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      RESULT_VARIABLE EPYBIND11_UNPACK_RESULT
      OUTPUT_VARIABLE PYBIND11_UNPACK_OUTPUT
      ERROR_VARIABLE PYBIND11_UNPACK_ERROR
  )
endif()

add_library(${PROJECT_NAME} SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ByteTrackerImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/KalmanFilter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lapjv.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/STrack.cpp
  )

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}/eigen-3.3.9 
  )

if(WITH_PYTHON)
  set(PYTHON_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/python/pybytetrack.cpp)
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/pybind11-2.10.4)
  pybind11_add_module(py${PROJECT_NAME} ${PYTHON_SRC})
  target_link_libraries(py${PROJECT_NAME} PRIVATE ${PROJECT_NAME})
endif()

if(WITH_TEST) 
  add_executable(test_bytetrack ${CMAKE_CURRENT_SOURCE_DIR}/test/test_bytetrack.cpp)
  target_link_libraries(test_bytetrack ${PROJECT_NAME})
endif()

install(TARGETS ${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/ByteTracker.h 
        DESTINATION include/)
