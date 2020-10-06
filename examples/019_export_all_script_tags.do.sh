#!/usr/bin/env bash

# Export all <script> tags from current page in browser
# back to terminal and into a file "script-tags.txt"

#IF(LINUX)
  #BROWSER=chromium
#ELSEIF(MAC)
  #BROWSER=firefox
#ENDIF

#activateBrowser
#openUrlInNewBrowserTab "https://duckduckgo.com"
sleep 1.0

#runScript...
# [].forEach.call("
#  document.querySelectorAll("script[src]"),
#  function(src) {
#    console.log(src);
#  }
#);
#...runScript

#copyAll
#saveClipboardToFile "clip.txt"
