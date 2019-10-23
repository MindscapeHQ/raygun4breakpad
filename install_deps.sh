#!/bin/bash

# Clear old breakpad repo
rm -rf deps/breakpad

# Clone Breakpad
git clone https://github.com/google/breakpad.git deps/breakpad

# Clone LSS
git clone https://chromium.googlesource.com/linux-syscall-support/ deps/breakpad/src/third_party/lss