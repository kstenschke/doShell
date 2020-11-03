#!/usr/bin/env bash

# Example on how to use runtime macros

echo $"Your platform is: ::OS::"

echo $"Current UNIX timestamp: ::TIMESTAMP::"

echo $"This is line ::LINE:: of file: ::FILE::"

echo $"Path of this file: ::DIR::"
echo "Working dir is: ::DIR_EXEC::"
echo "Path to doShell exectable is: ::DIR_DOSH::"

_import include/001_echo_hello.sh
