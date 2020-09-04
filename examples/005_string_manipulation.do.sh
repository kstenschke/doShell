#!/usr/bin/env bash
# Export all URLs from HTML and all scripts of a web page

# output: Between
echo #extractBetween "beforeBetweenAfter" before After

# output: replaced successfully
echo #replaceAfter "replaceAfter" After "d successfully"

# output: the deer went there
echo #replaceAll "tho door wont thoro" o e

# output: has been replaced successfully
echo #replaceBefore "replaceBefore successfully" Before "has been replaced"

# output: hello there, test
echo #replaceBetween "hello world this is a test" world a "there,"

# output: foo qux baz bar
echo #replaceFirst "foo bar baz bar" bar qux

# output: foo bar baz qux
echo #replaceLast "foo bar baz bar" bar qux
