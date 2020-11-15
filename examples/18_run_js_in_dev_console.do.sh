#!/usr/bin/env bash

# Open the console panel within the browser's devTools,
# insert JavaScript into it and execute the JavaScript

_activateBrowser
_openUrlInNewBrowserTab "https://duckduckgo.com/"

_openBrowserDevConsole
_copyPaste "alert(\"hello world!\");"
_hitEnter
