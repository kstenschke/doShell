#!/usr/bin/env bash
#!keep_runtime_file
# URL parsing helper methods

echo "url: https://www.github.com/kstenschke/doShell?this=are&some=parameters"

printf "\nscheme: "
echo #getSchemeFromUrl https://www.github.com/kstenschke/doShell?this=are&some=parameters

printf "\nhost: "
echo #getHostFromUrl https://www.github.com/kstenschke/doShell?this=are&some=parameters

printf "\npath: "
echo #getPathFromUrl https://www.github.com/kstenschke/doShell?this=are&some=parameters

printf "\nquery: "
echo #getQueryFromUrl https://www.github.com/kstenschke/doShell?this=are&some=parameters
