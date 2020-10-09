#!/usr/bin/env bash

# Load duckduckgo in new browser tab,
# enter search term and invoke the search
# wait for results being loaded
# copy results
# convert results to plaintext
# output text to console

#if_is_linux
  #!browser chromium
#endif_is_linux

#if_is_mac
  #!browser firefox
#endif_is_mac

#activateBrowser
#openUrlInNewBrowserTab "https://duckduckgo.com/"
#copyPaste "foo"
#hitEnter
sleep 0.5

#openBrowserSource
#copyAll
sleep 0.3
#closeBrowserTab
#closeBrowserTab

#activateTerminal
#htmlFromClipboardToText
