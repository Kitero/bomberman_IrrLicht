#!/usr/bin/env bash
## Removes Bomberman installed by install.sh, and the local build files.
##
## Usage: ./uninstall.sh [--system]

set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

case "${1:-}" in
    --system)
        sudo_cmd=()
        [ "$(id -u)" -eq 0 ] || sudo_cmd=(sudo)
        "${sudo_cmd[@]}" rm -rf /opt/bomberman
        "${sudo_cmd[@]}" rm -f /usr/local/bin/bomberman /usr/local/share/applications/bomberman.desktop
        ;;
    "")
        DATA_HOME="${XDG_DATA_HOME:-$HOME/.local/share}"
        rm -rf "$DATA_HOME/bomberman"
        rm -f "$HOME/.local/bin/bomberman" "$DATA_HOME/applications/bomberman.desktop"
        ;;
    -h|--help)
        echo "Usage: $0 [--system]"
        exit 0
        ;;
    *)
        echo "Usage: $0 [--system]" >&2
        exit 1
        ;;
esac

rm -rf "$REPO_DIR/build" "$REPO_DIR/dist" "$REPO_DIR/bomberman"
echo "Uninstall successful."
