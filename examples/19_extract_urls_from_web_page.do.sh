#!/usr/bin/env bash

# Extract all URLs from web page

_activateBrowser
_openUrlInNewBrowserTab "https://www.wikipedia.org/"
_copyPaste "foo"
_hitEnter
sleep 0.5

_openBrowserSource
_hitCopyAll
sleep 0.3
_closeBrowserTab
_closeBrowserTab

_pregMatchAllInClipboard "https?:\/\/(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_\+.~#?&//=]*)"

_activateTerminal
