#!/usr/bin/env bash

# Exchange domain of current site against selected option:
# http://localhost / 'dev' / 'stage' / 'production'

CHOICE=_select "Take your pick:" {"http://localhost", "dev.tam.ch", "stage.tam.ch", "intranet.tam.ch"}
_setClipboard $CHOICE

_activateBrowser
_focusBrowserURL
_hitCopy

# remove scheme and domain from URL
_replaceBeforeFromClipboard // "" ::MUTE::
_replaceBeforeFromClipboard / "" ::MUTE::
_hitPaste

_moveCaretToLineStart
_hitPaste
