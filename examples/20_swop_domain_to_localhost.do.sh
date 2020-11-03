#!/usr/bin/env bash

# Exchange domain of current site against "http://localhost"

_activateBrowser
_copyBrowserUrl

tmp=_getClipboard

if [[ $tmp == *"http"* ]]; then  # remove given scheme from URL
  _replaceBeforeFromClipboard // "" ::MUTE::
fi

_replaceBeforeFromClipboard / "" ::MUTE::  # remove domain from URL

_hitPaste

_moveCaretToLineStart
_copyPaste 'http://localhost/'
