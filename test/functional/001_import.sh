#!/usr/bin/env bats

load _helper

# TODO assert output from imported sub-script shows up in execution output
test "$BATS_TEST_NUMBER: \"#import - imports given file" {
#  run "${DOSH_BINARY}" -rc "examples/001_import.do.sh"
#  [ "$status" -ne 0 ]
}

# TODO assert output of imported sub-script contains filename

# TODO assert output of imported sub-script contains line number

# TODO assert output of imported sub-script contains parsed macros

# TODO assert output of imported sub-script contains parsed condition

# TODO assert output of imported sub-script contains parsed runtime parameters
