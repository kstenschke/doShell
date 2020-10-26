#!/usr/bin/env bash
# URL parsing helper methods

echo "url: https://www.github.com/kstenschke/doShell?these=are&some=parameters"
printf "scheme: "
echo #getSchemeFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
printf "host: "
echo #getHostFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
printf "path: "
echo #getPathFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
printf "query: "
echo #getQueryFromUrl https://www.github.com/kstenschke/doShell?these=are\&some=parameters

echo

# remove scheme and domain from URL
printf "url w/o sheme and host: "
#setClipboard "url: https://www.github.com/kstenschke/doShell?these=are&some=parameters"
#replaceBeforeFromClipboard // '' ::MUTE::
echo #replaceBeforeFromClipboard / ''
