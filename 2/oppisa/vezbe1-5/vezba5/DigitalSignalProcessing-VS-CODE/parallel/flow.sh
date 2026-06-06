#!/bin/bash

exit 0

# Just first time.
./waf configure

# Just to build.
./waf build

# Execute program.
./build/parallel

# Helper: On every code change build and execute program.
./waf build && ./build/parallel

# Reconfigure for releasen.
./waf configure --release
# Then build and run again release (faster) version.
./waf build && ./build/parallel