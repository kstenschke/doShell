#!/usr/bin/env bash

# Load google.com in new browser tab

#if_is_linux
  #!browser chromium
#endif_is_linux

#if_is_mac
  #!browser firefox
#endif_is_mac

#activateBrowser
#openUrlInNewBrowserTab "https://www.google.com/"
#copyPaste "foo"
#hitEnter
