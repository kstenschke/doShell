#!/usr/bin/env bash
#!keep_runtime_file

RESULT=#confirm "Ok or Cancel?"
RESULT=#replaceBefore "$RESULT" ':' ''
MESSAGE="You clicked: $RESULT"
#notify $MESSAGE
