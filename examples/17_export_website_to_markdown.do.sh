#!/usr/bin/env bash

# Load wikipedia in new browser tab,
# enter search term and invoke search
# wait for page being loaded
# copy page source HTML
# convert source HTML to Markdown
# output text to console

#activateBrowser
#openUrlInNewBrowserTab "https://www.wikipedia.org/"
#copyPaste "foo"
#hitEnter
sleep 0.5

#openBrowserSource
#copyAll
sleep 0.3
#closeBrowserTab
#closeBrowserTab

#saveClipboard ::DIR::/tmp.html
node ::DIR::/scripts/node/turndown.js ::DIR::/tmp.html

rm ::DIR::/tmp.html

#activateTerminal
