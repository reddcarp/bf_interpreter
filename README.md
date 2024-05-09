# bf_interpreter

A simple [brainfck](https://en.wikipedia.org/wiki/Brainfuck) interpreter written in cpp.

## Compilation

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
./bf_interpreter <bf_filepath>
```

## Example

```bash
./bf_interpreter ../bf_scripts/hello_world.bf
```

## Tests

Requirements:

- shunit2 package
- valgrind package

Run all tests:

```bash
make run_tests
```
