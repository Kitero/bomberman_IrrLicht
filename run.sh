#!/bin/sh
# The game loads its data relative to the working directory.
cd "$(dirname "$0")" && exec ./bomberman "$@"
