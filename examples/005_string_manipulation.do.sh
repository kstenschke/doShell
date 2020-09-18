#!/usr/bin/env bash
# All string helper command examples output: foo bar baz qux

printf "extractBetween: "
echo #extractBetween "start foo bar baz qux end" start end

printf "\nreplaceAfter: "
echo #replaceAfter "foo bar xxx xxx" bar " baz qux"

printf "\nreplaceAll: "
echo #replaceAll "foo ber bez qux" e a

printf "\nreplaceBefore: "
echo #replaceBefore "thingummibob bar baz qux" bat foo

printf "\nreplaceBetween: "
echo #replaceBetween "foo thingummibob qux" foo qux " bar baz "

printf "\nreplaceFirst: "
echo #replaceFirst "bar bar baz qux" bar foo

printf "\nreplaceLast: "
echo #replaceLast "foo bar baz bar" bar qux
