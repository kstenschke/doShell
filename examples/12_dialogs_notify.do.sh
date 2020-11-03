#!/usr/bin/env bash
#!keep_runtime_file

#if_is_linux
  _notify "Hello Linux!"
#endif_is_linux

#if_is_mac
  _notify "Hello Mac!"
#endif_is_mac
