cmake_minimum_required(VERSION 3.5)

PROJECT(bf_interpreter
    VERSION 1.0.0
    LANGUAGES CXX
)

# Global CMake variables
set(CMAKE_CXX_STANDARD 20)

# Variables set
set(executable_name bf_interpreter)

set(bf_interpreter_SRC_DIR
    src/
)
set(bf_interpreter_INCLUDE_DIRS
    src/
)
set(bf_interpreter_SRC_FILES
    src/main.cpp
    src/token.cpp
    src/tokenize.cpp
)

file(GLOB_RECURSE bf_interpreter_HEADER_FILES
    ${bf_interpreter_SRC_DIR}/*.hpp 
)

include_directories(${bf_interpreter_INCLUDE_DIRS})

# exe creation
add_executable(${executable_name}
    ${bf_interpreter_SRC_FILES}
    ${bf_interpreter_HEADER_FILES}
)

# Custom target for tests
add_custom_target(run_tests COMMAND ctest --output-on-failure)
add_dependencies(run_tests ${executable_name})

# Tests
enable_testing()

add_test(NAME helloWorldTest
    COMMAND ${CMAKE_SOURCE_DIR}/test/helloWorldTest.sh
)

add_test(NAME memoryLeakTest
    COMMAND ${CMAKE_SOURCE_DIR}/test/memoryLeakTest.sh
)

add_test(NAME userInputTest
    COMMAND ${CMAKE_SOURCE_DIR}/test/userInputTest.sh
)

add_test(NAME errorNoMatchingEndBracket
    COMMAND ${CMAKE_SOURCE_DIR}/test/errorNoMatchingEndBracket.sh
)

add_test(NAME errorNoMatchingStartBracket
    COMMAND ${CMAKE_SOURCE_DIR}/test/errorNoMatchingStartBracket.sh
)

add_test(NAME errorDataPointerOutOfBound
    COMMAND ${CMAKE_SOURCE_DIR}/test/errorDataPointerOutOfBound.sh
)
