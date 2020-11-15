#!/usr/bin/env bash

# load wikipedia home page,
# find and fire click event on <span> containing text "Commons"

_activateBrowser
_openUrlInNewBrowserTab "https://www.wikipedia.org/"

sleep 0.2

_openBrowserDevConsole
_pasteRenderedFromFile ::DIR::scripts/click_tag_by_contained_text.js "{'<tag_name>':'span','<search_text>','Commons'}"
_hitEnter
