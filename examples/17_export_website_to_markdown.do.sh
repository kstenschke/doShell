#!/usr/bin/env bash

# Load wikipedia in new browser tab, enter search term and invoke search
# wait for page being loaded, copy page source HTML,
# convert source HTML to Markdown. Finally output Markdown to console

_activateBrowser
_openUrlInNewBrowserTab "https://www.wikipedia.org/"
_copyPaste "foo"
_hitEnter
sleep 0.5

_openBrowserSource
_copyAll
sleep 0.3
_closeBrowserTab
_closeBrowserTab

_saveClipboard ::DIR::/tmp.html
node ::DIR::/scripts/node/turndown.js ::DIR::/tmp.html

rm ::DIR::/tmp.html

_activateTerminal
