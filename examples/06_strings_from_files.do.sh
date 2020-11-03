#!/usr/bin/env bash
# All file helper command examples output: foo bar baz qux

printf "extractBetweenFromFile: "
echo _extractBetweenFromFile ::DIR::assets/extractBetween.txt start end

printf "\nreplaceAfterFromFile: "
echo _replaceAfterFromFile ::DIR::assets/replaceAfter.txt bar "bar baz qux"

printf "\nreplaceAllFromFile: "
echo _replaceAllFromFile ::DIR::assets/replaceAll.txt e a

printf "\nreplaceBeforeFromFile: "
echo _replaceBeforeFromFile ::DIR::assets/replaceBefore.txt bar 'foo bar'

printf "\nreplaceBetweenFromFile: "
echo _replaceBetweenFromFile ::DIR::assets/replaceBetween.txt bar qux " bar baz qux"

printf "\nreplaceFirstFromFile: "
echo _replaceFirstFromFile ::DIR::assets/replaceFirst.txt bar foo

printf "\nreplaceLastFromFile: "
echo _replaceLastFromFile ::DIR::assets/replaceLast.txt bar qux
