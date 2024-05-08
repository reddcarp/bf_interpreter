#!/bin/bash

OUTPUT_FILE=output.txt
BF_EXECUTABLE=$1

tearDown() {
    rm -f $OUTPUT_FILE
}

testMemoryLeak() {
    valgrind --leak-check=yes --error-exitcode=1 ./bf_interpreter ../test/bf_scripts/data_cell_size_test.bf
    assertEquals 'Memory leaks detected' 0 $?
}

. shunit2