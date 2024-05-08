#!/bin/bash

OUTPUT_FILE=output.txt
BF_EXECUTABLE=$1

tearDown() {
    rm -f $OUTPUT_FILE
}

testUserInput() {
    ./bf_interpreter ../test/bf_scripts/echo_times_two.bf > ${OUTPUT_FILE} <<EOF
!
?
EOF
    assertEquals 0 $?
    assertContains "$( cat ${OUTPUT_FILE} )" '!'
    assertContains "$( cat ${OUTPUT_FILE} )" '?'
}

. shunit2