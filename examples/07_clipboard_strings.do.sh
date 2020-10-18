#!/usr/bin/env bash
# All clipboard helper command examples output: foo bar baz qux

printf "extractBetweenFromClipboard: "
#setClipboard "start foo bar baz qux end"
echo #extractBetweenFromClipboard start end

printf "\nreplaceAfterFromClipboard: "
#setClipboard "foo bar xxx xxx"
echo #replaceAfterFromClipboard bar "bar baz qux"

printf "\nreplaceAllFromClipboard: "
#setClipboard "foo ber bez qux"
echo #replaceAllFromClipboard e a

printf "\nreplaceBeforeFromClipboard: "
#setClipboard "thingummibob bar baz qux"
echo #replaceBeforeFromClipboard bar 'foo bar'

printf "\nreplaceBetweenFromClipboard: "
#setClipboard "foo bar thingummibob qux"
echo #replaceBetweenFromClipboard bar qux " bar baz qux"

printf "\nreplaceFirstFromClipboard: "
#setClipboard "bar bar baz qux"
echo #replaceFirstFromClipboard bar foo

printf "\nreplaceLastFromClipboard: "
#setClipboard "foo bar baz bar"
echo #replaceLastFromClipboard bar qux
