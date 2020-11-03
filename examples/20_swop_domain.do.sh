#!/usr/bin/env bash

# Exchange domain of current site against "http://localhost"

_activateBrowser
_focusBrowserURL
_hitCopy

# remove scheme and domain from URL
_replaceBeforeFromClipboard // "" ::MUTE::
_replaceBeforeFromClipboard / "" ::MUTE::
_hitPaste

_moveCaretToLineStart
_copyPaste 'http://localhost/'
