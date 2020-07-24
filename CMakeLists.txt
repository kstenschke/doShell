cmake_minimum_required(VERSION 3.9)
project(robo)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/mac)
else()
    # Linux
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/linux)
endif()

add_executable(robo
        robo/main.cpp
        robo/helper/helper_string.cc
        robo/helper/helper_string.h
        robo/helper/helper_file.cc
        robo/helper/helper_file.h robo/app/app.cc robo/app/app.h robo/helper/helper_dateTime.cc robo/helper/helper_dateTime.h)
