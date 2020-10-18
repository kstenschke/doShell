#!/usr/bin/env bash

# Open the console panel within the browser's devTools,
# insert JavaScript into it and execute the JavaScript

#IF(LINUX)
  #BROWSER=chromium
#ELSEIF(MAC)
  #BROWSER=firefox
#ENDIF

#activateBrowser
#openUrlInNewBrowserTab "https://duckduckgo.com/"
#openBrowserDevConsole
#copyPaste "alert(\"hello world!\");"
#hitEnter
