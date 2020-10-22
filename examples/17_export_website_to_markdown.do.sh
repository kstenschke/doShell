#!/usr/bin/env bash

# Load wikipedia in new browser tab,
# enter search term and invoke search
# wait for page being loaded
# copy page source HTML
# convert source HTML to plaintext
# output text to console

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
#hitCopyAll
sleep 0.3
#closeBrowserTab
#closeBrowserTab

#saveClipboard ::DIR::/tmp.html
node ::DIR::/scripts/node/turndown.js ::DIR::/tmp.html

rm ::DIR::/tmp.html

#activateTerminal
