#!/usr/bin/env bash
#!keep_runtime_file

RESULT=_confirm "Do you agree?"
RESULT=_replaceBefore "$RESULT" ':' ''

if [ $RESULT == "Ok" ]; then
  MESSAGE="You agreed."
else
  MESSAGE="You disagreed."
fi

_notify "$MESSAGE"
