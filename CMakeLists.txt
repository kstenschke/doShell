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

        doShell/dosh/runtimeOptions/runtime_options.cc
        doShell/dosh/runtimeOptions/runtime_options.h

        doShell/dosh/shellCommand/shell_command_clipboard.cc
        doShell/dosh/shellCommand/shell_command_clipboard.h
        doShell/dosh/shellCommand/shell_command_string.cc
        doShell/dosh/shellCommand/shell_command_string.h
        doShell/dosh/shellCommand/shell_command_url_parse.cc
        doShell/dosh/shellCommand/shell_command_url_parse.h

        doShell/dosh/transpile/transpile_browser.cc
        doShell/dosh/transpile/transpile_browser.h
        doShell/dosh/transpile/transpile_clipboard.cc
        doShell/dosh/transpile/transpile_clipboard.h
        doShell/dosh/transpile/transpile_dialog.cc
        doShell/dosh/transpile/transpile_dialog.h
        doShell/dosh/transpile/transpile_keystrokes.cc
        doShell/dosh/transpile/transpile_keystrokes.h
        doShell/dosh/transpile/transpile_platform.cc
        doShell/dosh/transpile/transpile_platform.h
        doShell/dosh/transpile/transpile_random.cc
        doShell/dosh/transpile/transpile_random.h
        doShell/dosh/transpile/transpile_string.cc
        doShell/dosh/transpile/transpile_string.h
        doShell/dosh/transpile/transpile_terminal.cc
        doShell/dosh/transpile/transpile_terminal.h
        doShell/dosh/transpile/transpile_url.cc
        doShell/dosh/transpile/transpile_url.h

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
