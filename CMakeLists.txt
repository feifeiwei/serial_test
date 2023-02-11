cmake_minimum_required(VERSION 2.8)

project(socket-apps)

set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")


add_executable(sed sed.cpp)
add_executable(rec rec.cpp)




