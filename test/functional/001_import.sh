#!/usr/bin/env bats

load _helper

@test "$BATS_TEST_NUMBER: \"#import - imports given file" {
  run "${DOSH_BINARY}" -rc "examples/001_import.do.sh"
  [ "$status" -ne 0 ]
# TODO assert import worked
}
