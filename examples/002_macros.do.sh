#!/usr/bin/env bash
#!keep_runtime_file

# Example on how to use runtime macros

echo $"current UNIX timestamp: ::TIMESTAMP::"

echo $"this is line ::LINE:: of file: ::FILE::"
echo $"path of this file: ::DIR::"
echo $"your platform is: ::OS::"

#import include/001_echo_hello.sh
