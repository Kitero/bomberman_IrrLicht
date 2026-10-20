#!/bin/bash
## Configure and build the game (Release).
## Dependencies (Debian/Ubuntu):
##   sudo apt install cmake g++ libirrlicht-dev libgl1-mesa-dev libxxf86vm-dev libxext-dev \
##     libpng-dev libjpeg-dev zlib1g-dev libbz2-dev

set -e
cd "$(dirname "$0")"
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc)"
printf "Build successful: run ./bomberman (or ./run.sh)\n"
