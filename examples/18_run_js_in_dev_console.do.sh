#!/usr/bin/env bash

# Open the console panel within the browser's devTools,
# insert JavaScript into it and execute the JavaScript

#IF(LINUX)
  #BROWSER=chromium
#ELSEIF(MAC)
  #BROWSER=firefox
#ENDIF

_activateBrowser
_openUrlInNewBrowserTab "https://duckduckgo.com/"

_openBrowserDevConsole
_copyPaste "alert(\"hello world!\");"
_hitEnter
