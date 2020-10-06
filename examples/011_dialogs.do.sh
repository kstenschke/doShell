#!/usr/bin/env bash
#!keep_runtime_file

# Display various dialog popups

#alert "Welcome to dialog examples"

#notify "this is a notification"

RESULT=#confirm "Ok or Cancel?"
# $RESULT is e.g.: "button returned:Ok"
RESULT=#replaceBefore $RESULT ':' ''
#notify $RESULT


# #IF(LINUX)
#  #notify "Hello Linux
# #ELSEIF(MAC)
#  #notify "Hello Mac"
# #ENDIF

# #alert "this is an alert"
#
# #confirm "do you confirm?"
#
# #prompt "please enter into this prompt"
