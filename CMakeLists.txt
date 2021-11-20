cmake_minimum_required(VERSION 3.10)
project(planesweeping)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})


include_directories("/usr/include/eigen3/")

set(CMAKE_CXX_STANDARD 14)

add_executable(planesweeping main.cpp CalculateRT.h CalculateRT.cpp PlaneSweeping.cpp PlaneSweeping.h)
target_link_libraries(planesweeping ${OpenCV_LIBS})
