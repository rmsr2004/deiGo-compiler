# README

## Compiler Project 2024/2025

### Compiler for the deiGo Language

This project involves the development of a compiler for the **deiGo** language, which is a subset of the [Go language](https://golang.org/ref/spec), following the May 2018 specification provided in the course materials.

The main goal is to implement a functional compiler capable of analyzing, interpreting, and generating code for programs written in the deiGo language, covering various stages of compiler construction.

---

## Features

- **Lexical Analysis**: Token identification and removal of whitespace and comments.
- **Syntax Analysis**: Grammar structure verification according to the language specification.
- **Semantic Analysis**: Type validation, scope checking, and other semantic rules.
- **Code Generation**: Production of intermediate or executable code.

---

## Requirements

To run the compiler, you need the following installed:

- **Flex**
- **Bison**
- **LLVM**

    ```
    sudo apt update
    sudo apt install flex bison llvm clang
    ```

---

## How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/rmsr2004/deiGo-compiler
   ```

2. Navigate to the project directory:
   ```bash
   cd deiGo-compiler
   ```

3. Compile and run the project:
   ```bash
   ./compile.sh
   ./src/gocompiler < input_file > output_file
   ```
    1. Run only the lexical analysis:
        ```bash
        ./compile.sh
        ./src/gocompiler -l < input_file > output_file
        ```
    2. Run only the syntax analysis:
        ```bash
        ./compile.sh
        ./src/gocompiler -t < input_file > output_file
        ```
    3. Run only the semantic analysis:
        ```bash
        ./compile.sh
        ./src/gocompiler -s < input_file > output_file
        ```

---

## Test Cases

The `tests/` directory contains example programs written in the deiGo language to verify different aspects of the compiler. Run the tests to ensure compliance with the specification:

- Lexical analysis tests.
- Syntax analysis tests.
- Semantic analysis tests.
