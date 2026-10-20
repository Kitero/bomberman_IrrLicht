#!/bin/bash
## Remove build files and the game binary.

cd "$(dirname "$0")"
rm -rf build dist bomberman
printf "Uninstall successful.\n"
