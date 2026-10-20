#!/usr/bin/env bash
## Bomberman installer for Linux.
## Installs the build dependencies (apt, pacman, dnf/yum or zypper),
## builds the game and installs it with a launcher and a menu entry.
##
## Usage: ./install.sh [options]   (./install.sh --help)

set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

MODE=user           # user | system
DO_DEPS=1
DO_INSTALL=1
ASSUME_YES=0
PKG_MANAGER=""

if [ -t 1 ]; then
    BOLD=$'\033[1m'; RED=$'\033[31m'; GREEN=$'\033[32m'; YELLOW=$'\033[33m'; NOC=$'\033[0m'
else
    BOLD=""; RED=""; GREEN=""; YELLOW=""; NOC=""
fi

info() { printf '%s==>%s %s\n' "$BOLD$GREEN" "$NOC" "$*"; }
warn() { printf '%swarning:%s %s\n' "$BOLD$YELLOW" "$NOC" "$*" >&2; }
die()  { printf '%serror:%s %s\n' "$BOLD$RED" "$NOC" "$*" >&2; exit 1; }

usage() {
    cat <<EOF
Usage: $0 [options]

Installs the dependencies, builds Bomberman and installs it.

Options:
  --system       install for all users (/opt/bomberman, /usr/local/bin)
                 instead of the current user (~/.local)
  --build-only   build only: ./bomberman at the repository root, nothing installed
  --deps-only    install the dependencies only
  --no-deps      do not install the dependencies
  --pm NAME      force the package manager: apt, pacman, dnf, yum or zypper
  -y, --yes      do not ask for confirmation
  -h, --help     show this help
EOF
}

while [ $# -gt 0 ]; do
    case "$1" in
        --system)     MODE=system ;;
        --build-only) DO_INSTALL=0 ;;
        --deps-only)  DO_INSTALL=0; BUILD=0 ;;
        --no-deps)    DO_DEPS=0 ;;
        --pm)         shift; PKG_MANAGER="${1:-}" ;;
        -y|--yes)     ASSUME_YES=1 ;;
        -h|--help)    usage; exit 0 ;;
        *)            usage >&2; die "unknown option: $1" ;;
    esac
    shift
done
BUILD="${BUILD:-1}"

if [ "$MODE" = system ]; then
    PREFIX=/opt/bomberman
    BIN_DIR=/usr/local/bin
    APPS_DIR=/usr/local/share/applications
else
    DATA_HOME="${XDG_DATA_HOME:-$HOME/.local/share}"
    PREFIX="$DATA_HOME/bomberman"
    BIN_DIR="$HOME/.local/bin"
    APPS_DIR="$DATA_HOME/applications"
fi

# Runs a command as root, through sudo when needed
as_root() {
    if [ "$(id -u)" -eq 0 ]; then
        "$@"
    elif command -v sudo >/dev/null 2>&1; then
        sudo "$@"
    else
        die "root privileges required (sudo not found): $*"
    fi
}

detect_pkg_manager() {
    local pm
    for pm in apt-get pacman dnf yum zypper; do
        if command -v "$pm" >/dev/null 2>&1; then
            echo "${pm%-get}"
            return
        fi
    done
}

install_deps() {
    [ -n "$PKG_MANAGER" ] || PKG_MANAGER="$(detect_pkg_manager)"
    [ -n "$PKG_MANAGER" ] || die "no supported package manager found (apt, pacman, dnf, yum, zypper).
Install by hand: a C++ compiler, cmake, Irrlicht 1.8 (devel), OpenGL, X11, Xxf86vm, libpng, libjpeg, zlib, bzip2."

    local yes=()
    local -a pkgs
    case "$PKG_MANAGER" in
        apt)
            pkgs=(g++ make cmake libirrlicht-dev libgl1-mesa-dev libx11-dev libxxf86vm-dev
                  libxext-dev libpng-dev libjpeg-dev zlib1g-dev libbz2-dev)
            info "Installing dependencies with apt: ${pkgs[*]}"
            [ "$ASSUME_YES" -eq 1 ] && yes=(-y)
            as_root apt-get update
            as_root apt-get install "${yes[@]}" "${pkgs[@]}"
            ;;
        pacman)
            # Arch only ships a shared Irrlicht: the game links to it dynamically.
            pkgs=(gcc make cmake irrlicht mesa libx11 libxxf86vm libxext libpng libjpeg-turbo zlib bzip2)
            info "Installing dependencies with pacman: ${pkgs[*]}"
            [ "$ASSUME_YES" -eq 1 ] && yes=(--noconfirm)
            as_root pacman -S --needed "${yes[@]}" "${pkgs[@]}" \
                || die "pacman failed. If packages were not found, update your system first: sudo pacman -Syu"
            ;;
        dnf|yum)
            pkgs=(gcc-c++ make cmake irrlicht-devel mesa-libGL-devel libX11-devel libXxf86vm-devel
                  libXext-devel libpng-devel libjpeg-turbo-devel zlib-devel bzip2-devel)
            info "Installing dependencies with $PKG_MANAGER: ${pkgs[*]}"
            [ "$ASSUME_YES" -eq 1 ] && yes=(-y)
            as_root "$PKG_MANAGER" install "${yes[@]}" "${pkgs[@]}" \
                || die "$PKG_MANAGER failed. On RHEL/Rocky/Alma, irrlicht-devel comes from EPEL."
            ;;
        zypper)
            pkgs=(gcc-c++ make cmake irrlicht-devel Mesa-libGL-devel libX11-devel libXxf86vm-devel
                  libXext-devel libpng16-devel libjpeg8-devel zlib-devel libbz2-devel)
            info "Installing dependencies with zypper: ${pkgs[*]}"
            [ "$ASSUME_YES" -eq 1 ] && yes=(--non-interactive)
            as_root zypper "${yes[@]}" install "${pkgs[@]}"
            ;;
        *)
            die "unsupported package manager: $PKG_MANAGER"
            ;;
    esac
}

build() {
    command -v cmake >/dev/null 2>&1 || die "cmake not found (run without --no-deps)"
    local jobs
    jobs="$(nproc 2>/dev/null || echo 2)"
    info "Building the game"
    cmake -S "$REPO_DIR" -B "$REPO_DIR/build" -DCMAKE_BUILD_TYPE=Release
    cmake --build "$REPO_DIR/build" -j"$jobs"
}

install_game() {
    local sudo_cmd=()
    [ "$MODE" = system ] && sudo_cmd=(as_root)

    info "Installing to $PREFIX"
    "${sudo_cmd[@]}" rm -rf "$PREFIX"
    "${sudo_cmd[@]}" cmake --install "$REPO_DIR/build" --prefix "$PREFIX"

    local tmp
    tmp="$(mktemp -d)"
    # shellcheck disable=SC2064 # expand now: tmp is local, gone at EXIT
    trap "rm -rf '$tmp'" EXIT

    cat > "$tmp/bomberman" <<EOF
#!/bin/sh
exec "$PREFIX/run.sh" "\$@"
EOF
    cat > "$tmp/bomberman.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=Bomberman
Comment=3D Bomberman built with Irrlicht
Exec=$BIN_DIR/bomberman
Path=$PREFIX
Icon=applications-games
Terminal=false
Categories=Game;ArcadeGame;
EOF
    "${sudo_cmd[@]}" install -Dm755 "$tmp/bomberman" "$BIN_DIR/bomberman"
    "${sudo_cmd[@]}" install -Dm644 "$tmp/bomberman.desktop" "$APPS_DIR/bomberman.desktop"

    info "Installed. Run it with: bomberman (or from your applications menu)"
    case ":$PATH:" in
        *":$BIN_DIR:"*) ;;
        *) warn "$BIN_DIR is not in your PATH; run $BIN_DIR/bomberman or add it to PATH" ;;
    esac
}

[ "$(uname -s)" = Linux ] || die "this installer is for Linux; see README.md for Windows"

[ "$DO_DEPS" -eq 1 ] && install_deps
[ "$BUILD" -eq 1 ] && build
if [ "$DO_INSTALL" -eq 1 ]; then
    install_game
elif [ "$BUILD" -eq 1 ]; then
    info "Build successful: run ./bomberman from $REPO_DIR"
fi
