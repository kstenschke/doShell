#!/usr/bin/env bash

# Exchange domain of current site against selected option:
# http://localhost / 'dev' / 'stage' / 'production'

_activateBrowser
_copyBrowserUrl

tmp=_getClipboard

if [[ $tmp == *"http"* ]]; then
  # remove "http://" or "https://" from URL
  _replaceBeforeFromClipboard // "" ::MUTE::
fi

# remove domain from URL
_replaceBeforeFromClipboard / "" ::MUTE::

# paste URL w/o scheme and domain
_hitPaste
_moveCaretToLineStart

choice=_select "Take your pick:" {"localhost/", "dev.localhost/", "stage.localhost/", "live.localhost/"}
_setClipboard $choice
sleep 0.2

# prepend seleted domain before URL
_hitPaste
