#!/usr/bin/env bash
#!keep_runtime_file

RESULT=#confirm "Do you agree?"
RESULT=#replaceBefore "$RESULT" ':' ''

if [ $RESULT == "Ok" ]; then
  MESSAGE="You agreed."
else
  MESSAGE="You disagreed."
fi

#notify "$MESSAGE"
