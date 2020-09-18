#!/usr/bin/env bash
# All file helper command examples output: foo bar baz qux

printf "extractBetween: "
echo #extractBetween "start foo bar baz qux end" start end

printf "\nreplaceAfter: "
echo #replaceAfter "foo bar xxx xxx" bar "bar baz qux"

printf "\nreplaceAll: "
echo #replaceAll "foo ber bez qux" e a

printf "\nreplaceBefore: "
echo #replaceBefore "thingummibob bar baz qux" bar "foo bar"

printf "\nreplaceBetween: "
echo #replaceBetween "foo bar thingummibob qux" bar qux " bar baz "

printf "\nreplaceFirst: "
echo #replaceFirst "bar bar baz qux" bar foo

printf "\nreplaceLast: "
echo #replaceLast "foo bar baz bar" bar qux
