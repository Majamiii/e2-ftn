#!/bin/bash

exit 0

# Just first time.
./waf configure

# Just to build.
./waf build

# Execute program.
./build/matrix N M

# Helper: On every code change build and execute program.
./waf build && ./build/matrix N M
