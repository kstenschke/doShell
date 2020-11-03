#!/usr/bin/env bash
# All clipboard helper command examples output: foo bar baz qux

printf "extractBetweenFromClipboard: "
_setClipboard "start foo bar baz qux end"
echo _extractBetweenFromClipboard start end

printf "\nreplaceAfterFromClipboard: "
_setClipboard "foo bar xxx xxx"
echo _replaceAfterFromClipboard bar "bar baz qux"

printf "\nreplaceAllFromClipboard: "
_setClipboard "foo ber bez qux"
echo _replaceAllFromClipboard e a

printf "\nreplaceBeforeFromClipboard: "
_setClipboard "thingummibob bar baz qux"
echo _replaceBeforeFromClipboard bar 'foo bar'

printf "\nreplaceBetweenFromClipboard: "
_setClipboard "foo bar thingummibob qux"
echo _replaceBetweenFromClipboard bar qux " bar baz qux"

printf "\nreplaceFirstFromClipboard: "
_setClipboard "bar bar baz qux"
echo _replaceFirstFromClipboard bar foo

printf "\nreplaceLastFromClipboard: "
_setClipboard "foo bar baz bar"
echo _replaceLastFromClipboard bar qux
