#!/usr/bin/env bash

# Extract all URLs from web page

#if_is_linux
  #!browser chromium
#endif_is_linux

#if_is_mac
  #!browser firefox
#endif_is_mac

#activateBrowser
#openUrlInNewBrowserTab "https://www.wikipedia.org/"
#copyPaste "foo"
#hitEnter
sleep 0.5

#openBrowserSource
#copyAll
sleep 0.3
#closeBrowserTab
#closeBrowserTab

#pregMatchAllInClipboard "https?:\/\/(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_\+.~#?&//=]*)"

#activateTerminal
