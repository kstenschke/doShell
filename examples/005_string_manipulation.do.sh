#!/usr/bin/env bash
# String helper commands

# output: Between
echo #extractBetween beforeBetweenAfter before After

# output: replaced successfully
echo #replaceAfter "replaceAfter" After "d successfully"

# output: the deer went there
echo #replaceAll "tho door wont thoro" o e

# output: foo bar baz qux
echo #replaceBefore "thingummibob bar baz qux" bat foo

# output: foo bar baz qux
echo #replaceBetween "foo thingummibob qux" foo qux " bar baz "

# output: foo bar baz qux
echo #replaceFirst "bar bar baz qux" bar foo

# output: foo bar baz qux
echo #replaceLast "foo bar baz bar" bar qux
