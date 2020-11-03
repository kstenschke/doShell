#!/usr/bin/env bash

# Exchange domain of current site against selected option:
# http://localhost / 'dev' / 'stage' / 'production'

CHOICE=_select "Take your pick:" {"http://localhost", "dev.tam.ch", "stage.tam.ch", "intranet.tam.ch"}
_setClipboard $CHOICE

_activateBrowser
_focusBrowserURL
_hitCopy

tmp=$(_getClipboard)

if [[ $tmp == *"http"* ]]; then
  # remove "http://" or "https://" from URL
  _replaceBeforeFromClipboard // "" ::MUTE::
fi

# remove domain from URL
_replaceBeforeFromClipboard / "" ::MUTE::

# paste URL w/o scheme and domain
_hitPaste

# prepend seleted domain before URL
_moveCaretToLineStart
_hitPaste
