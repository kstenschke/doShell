#!/usr/bin/env bash
#!keep_runtime_file

# Example on how to use runtime macros

vDateTime=::DATE_TIME::
vDate=::DATE::
vTime=::TIME::

echo $("today is: $vDate")
echo $("the time is: $vTime")
echo $("full date/time: $vDateTime")

echo "this is line ::LINE:: of file: ::FILE::"
echo "path of this file: ::DIR::"
echo "your platform is: ::OS::"

#import include/001_echo_hello.sh
