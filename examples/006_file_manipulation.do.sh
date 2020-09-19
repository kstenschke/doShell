#!/usr/bin/env bash
# All file helper command examples output: foo bar baz qux

printf "extractBetweenFromFile: "
echo #extractBetweenFromFile ::DIR::assets/extractBetween.txt start end

printf "\nreplaceAfterFromFile: "
echo #replaceAfterFromFile ::DIR::assets/replaceAfter.txt bar "bar baz qux"

printf "\nreplaceAllFromFile: "
echo #replaceAllFromFile ::DIR::assets/replaceAll.txt e a

printf "\nreplaceBeforeFromFile: "
echo #replaceBeforeFromFile ::DIR::assets/replaceBefore.txt bar 'foo bar'

printf "\nreplaceBetweenFromFile: "
echo #replaceBetweenFromFile ::DIR::assets/replaceBetween.txt bar qux ' bar baz '

printf "\nreplaceFirstFromFile: "
echo #replaceFirstFromFile ::DIR::assets/replaceFirst.txt bar foo

printf "\nreplaceLastFromFile: "
echo #replaceLast ::DIR::assets/replaceLast.txt bar qux
