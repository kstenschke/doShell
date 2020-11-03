#!/usr/bin/env bash

# Example on random shorthand

# echo random number between 5 and 15
echo "Here are 10 random numbers between 5 and 15:"

for i in 1 2 3 4 5 6 7 8 9 10; do
  printf _random 5 15

  if (( i < 10 )); then
    printf ", "
  fi
done

echo
