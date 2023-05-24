cmake_minimum_required(VERSION 3.10)

project(rental VERSION 1.0.0)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})