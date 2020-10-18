#!/usr/bin/env bash
# All string helper command examples output: foo bar baz qux

echo
echo "1. Manipulate hard-coded strings"
echo "--------------------------------"

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


echo
echo
echo "2. Manipulate strings from variables"
echo "------------------------------------"

printf "extractBetween: "
STR="start foo bar baz qux end"
echo #extractBetween "$STR" start end

printf "\nreplaceAfter: "
STR="foo bar xxx xxx"
echo #replaceAfter "$STR" bar "bar baz qux"

printf "\nreplaceAll: "
STR="foo ber bez qux"
echo #replaceAll "$STR" e a

printf "\nreplaceBefore: "
STR="thingummibob bar baz qux"
echo #replaceBefore "$STR" bar "foo bar"

printf "\nreplaceBetween: "
STR="foo bar thingummibob qux"
echo #replaceBetween "$STR" bar qux " bar baz "

printf "\nreplaceFirst: "
STR="bar bar baz qux"
echo #replaceFirst "$STR" bar foo

printf "\nreplaceLast: "
STR="foo bar baz bar"
echo #replaceLast "$STR" bar qux

echo
