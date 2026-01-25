# CS210 Simple Shell

[![Build](https://github.com/finlaysr/CS210-Simple-Shell/actions/workflows/c-ci.yml/badge.svg)](https://github.com/finlaysr/CS210-Simple-Shell/actions/workflows/c-ci.yml)

## AUTHORS
* Callum Charteris
* Duncun Amundrund
* Finlay Robb
* Luke Wallace
* Muhammad Saad Khan 

## How to Use
The `make` command is used:
* `make` - builds the project, putting the final binary in ./bin
* `make run` - builds and runs the project
* `make format` - formats all the c files in the project (requires `clang-format`)
* `make clean` - removes any build artifacts, use when you want to rebuild

Additional options:
* `release=1` - use release profile without debug info
* `sanitize=1` - use address sanitizer to detect memory unsafety

Examples:
* `make run sanitize=1` - run with address sanitizer
* `make format && make release=1` - format project files and build project in release profile

## File Structure
``` text
.
├── bin
│   └── the final binary
├── build
│   └── where intermediate .o and .d files are
├── docs
│   └── any useful documentation
├── include
│   └── where all the .h files are
├── src
│   └── where all the .c files are
├── Makefile
└── README.md
```
Note: `./bin` and `./build` are generated automatically upon `make`
