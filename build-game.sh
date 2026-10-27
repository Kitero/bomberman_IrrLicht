#!/usr/bin/env bash
## Rebuilds the game in place (./bomberman at the repository root).
## Run ./install.sh first to install the dependencies.

set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"
[ -f build/CMakeCache.txt ] || cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc 2>/dev/null || echo 2)"
echo "Build successful: run ./bomberman"
