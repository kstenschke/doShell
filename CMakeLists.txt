cmake_minimum_required(VERSION 3.9)
project(doShell)

include_directories(${CMAKE_SOURCE_DIR})

set (VERSION_MAJOR "0")
set (VERSION_MINOR "0")
set (VERSION_PATCH "1")

# configure config.h to be generated from config.h.in,
# with injected version number
configure_file ("doShell/config.h.in" "doShell/config.h")

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    # Use libc++ explicitly so we can compile for
    # CMAKE_OSX_DEPLOYMENT_TARGET=10.7 or 10.8
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/mac)
else()
    # Linux
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/linux)
endif()

add_executable(dosh
        doShell/main.cpp
        doShell/app/app.cc
        doShell/app/app.h
        doShell/app/app_argument.cc
        doShell/app/app_argument.h
        doShell/app/app_command.cc
        doShell/app/app_command.h
        doShell/app/app_help.cc
        doShell/app/app_help.h
        doShell/app/app_log.cc
        doShell/app/app_log.h
        doShell/dosh/runtime.cc
        doShell/dosh/runtime.h

        doShell/dosh/shellCommand/shellCommandClipboard.cc
        doShell/dosh/shellCommand/shellCommandClipboard.h
        doShell/dosh/shellCommand/shellCommandString.cc
        doShell/dosh/shellCommand/shellCommandString.h
        doShell/dosh/shellCommand/shellCommandUrlParser.cc
        doShell/dosh/shellCommand/shellCommandUrlParser.h

        doShell/dosh/transpile/transpileBrowser.cc
        doShell/dosh/transpile/transpileBrowser.h
        doShell/dosh/transpile/transpileClipboard.cc
        doShell/dosh/transpile/transpileClipboard.h
        doShell/dosh/transpile/transpileDialog.cc
        doShell/dosh/transpile/transpileDialog.h
        doShell/dosh/transpile/transpileKeystrokes.cc
        doShell/dosh/transpile/transpileKeystrokes.h
        doShell/dosh/transpile/transpilePlatform.cc
        doShell/dosh/transpile/transpilePlatform.h
        doShell/dosh/transpile/transpileRandom.cc
        doShell/dosh/transpile/transpileRandom.h
        doShell/dosh/transpile/transpileString.cc
        doShell/dosh/transpile/transpileString.h
        doShell/dosh/transpile/transpileTerminal.cc
        doShell/dosh/transpile/transpileTerminal.h
        doShell/dosh/transpile/transpileUrl.cc
        doShell/dosh/transpile/transpileUrl.h

        doShell/helper/helper_cli.cc
        doShell/helper/helper_cli.h
        doShell/helper/helper_dateTime.cc
        doShell/helper/helper_dateTime.h
        doShell/helper/helper_file.cc
        doShell/helper/helper_file.h
        doShell/helper/helper_numeric.cc
        doShell/helper/helper_numeric.h
        doShell/helper/helper_string.cc
        doShell/helper/helper_string.h
        )

add_subdirectory(vendor/clip/)
include_directories(../vendor/clip/)
target_link_libraries(dosh clip)
