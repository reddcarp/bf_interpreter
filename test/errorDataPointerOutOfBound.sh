#!/bin/bash

OUTPUT_FILE=output.txt
BF_EXECUTABLE=$1

tearDown() {
    rm -f $OUTPUT_FILE
}

testErrorNoMatchingEndBracket() {
    ./bf_interpreter ../test/bf_scripts/error_data_pointer_out_of_bound.bf > ${OUTPUT_FILE}
    assertNotEquals 0 $?
    assertEquals 'Error: Trying to access index < 0' "$( cat ${OUTPUT_FILE} )"
}

. shunit2