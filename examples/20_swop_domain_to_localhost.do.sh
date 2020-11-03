#!/usr/bin/env bash

# Exchange domain of current site against "http://localhost"

_activateBrowser
_focusBrowserURL
_hitCopy

if [[ $tmp == *"http"* ]]; then
  # remove given scheme from URL
  _replaceBeforeFromClipboard // "" ::MUTE::
fi

# remove domain from URL
_replaceBeforeFromClipboard / "" ::MUTE::

_hitPaste

_moveCaretToLineStart
_copyPaste 'http://localhost/'
