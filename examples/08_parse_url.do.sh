#!/usr/bin/env bash
# URL parsing helper methods

# echo "url: https://www.github.com/kstenschke/doShell?these=are&some=parameters"
# printf "scheme: "
# echo #getSchemeFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
# printf "host: "
# echo #getHostFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
# printf "path: "
# echo #getPathFromUrl https://www.github.com/kstenschke/doShell?these=are&some=parameters
# printf "query: "
# echo #getQueryFromUrl https://www.github.com/kstenschke/doShell?these=are\&some=parameters

# remove scheme and domain from URL
#setClipboard "http://www.test.com/foo-bar-baz-qux"
#replaceBeforeFromClipboard // ''
#replaceBeforeFromClipboard / ''
echo #getClipboard