#!/usr/bin/env bash
## CI: runs install.sh in a distribution container like a user would,
## then starts the installed game under Xvfb and uninstalls it.
## Usage: test-installer.sh [user|system]

set -euo pipefail
mode="${1:-user}"

# Xvfb + software OpenGL for the smoke test (not game dependencies)
# shellcheck source=/dev/null
case "$(. /etc/os-release; echo "$ID")" in
    debian|ubuntu)
        export DEBIAN_FRONTEND=noninteractive
        apt-get update -qq
        apt-get install -y -qq xvfb libgl1-mesa-dri >/dev/null ;;
    arch)
        pacman -Syu --noconfirm --needed xorg-server-xvfb >/dev/null ;;
    fedora)
        dnf install -y -q xorg-x11-server-Xvfb mesa-dri-drivers >/dev/null ;;
    opensuse*)
        zypper -q --non-interactive install xorg-x11-server-Xvfb Mesa-dri >/dev/null ;;
esac

if [ "$mode" = system ]; then ./install.sh -y --system; else ./install.sh -y; fi
export PATH="$HOME/.local/bin:$PATH"
command -v bomberman

Xvfb :99 >/dev/null 2>&1 &
sleep 2
set +e
DISPLAY=:99 timeout 10 bomberman
status=$?
set -e
if [ "$status" -ne 124 ]; then
    echo "::error::bomberman exited early with status $status"
    exit 1
fi

if [ "$mode" = system ]; then ./uninstall.sh --system; else ./uninstall.sh; fi
if command -v bomberman; then
    echo "::error::bomberman still installed after uninstall.sh"
    exit 1
fi
