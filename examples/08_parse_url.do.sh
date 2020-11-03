#!/usr/bin/env bash
# URL parsing helper methods

echo "url: https://www.github.com/kstenschke/doShell?these=are&some=parameters"
printf "scheme: "
echo _getSchemeFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
printf "host: "
echo _getHostFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
printf "path: "
echo _getPathFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
printf "query: "
echo _getQueryFromUrl https://www.github.com/kstenschke/doShell?these=are\&some=parameters

echo

# remove scheme and domain from URL
printf "url w/o sheme and host: "
_setClipboard "url: https://www.github.com/kstenschke/doShell?these=are&some=parameters"
_replaceBeforeFromClipboard // '' ::MUTE::
echo _replaceBeforeFromClipboard / ''
