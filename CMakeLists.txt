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
        doShell/dosh/transpiler/transpileBrowser.cc
        doShell/dosh/transpiler/transpileBrowser.h
        doShell/dosh/transpiler/transpileClipboard.cc
        doShell/dosh/transpiler/transpileClipboard.h
        doShell/dosh/transpiler/transpileKeystrokes.cc
        doShell/dosh/transpiler/transpileKeystrokes.h
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
