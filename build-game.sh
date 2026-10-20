#!/bin/bash
## Rebuild the game (configure first with install.sh).

set -e
cd "$(dirname "$0")"
[ -d build ] || exec ./install.sh
cmake --build build -j"$(nproc)"
printf "Build successful: run ./bomberman (or ./run.sh)\n"
