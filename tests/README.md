# How to test the compiler

On terminal:
if you are at deiGo-compiler:

```bash
./tests/run_tests.sh -b src/gocompiler
```

if you are at tests:

```bash
./run_tests.sh -b ../src/gocompiler
```

Options:

```
  -b, --bin           gocompiler location
  -f, --folder        tests folder path. script path by default
  -m, --meta          Number of the goal to test, test all by omission.
  -h, --help          Display this help and exit.
```
