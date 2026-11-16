# Bomberman (Irrlicht)

A 3D Bomberman written in C++11 with [Irrlicht](https://irrlicht.sourceforge.io/) (graphics) and [miniaudio](https://miniaud.io/) (sound).

## Download

Prebuilt games are attached to the [GitHub Releases](../../releases):

| Platform | File |
|---|---|
| Windows x64 (installer) | `bomberman-windows-x64-setup.exe` |
| Windows x64 (portable) | `bomberman-windows-x64.zip`: unzip, run `bomberman.exe` |
| Linux x86_64 | `bomberman-linux-x86_64.tar.gz`: see below |

```sh
tar xzf bomberman-linux-x86_64.tar.gz
./bomberman/run.sh
```

The Linux build needs OpenGL, X11, libpng, libjpeg, zlib and bzip2 (present on any desktop distribution).

## Install from source (Linux)

`install.sh` installs the dependencies with your package manager (apt, pacman, dnf/yum or zypper), builds the game and installs it with a `bomberman` command and an applications menu entry:

```sh
./install.sh            # for the current user (~/.local)
./install.sh --system   # for all users (/opt/bomberman, /usr/local/bin)
./install.sh --help     # other options (--build-only, --no-deps, -y...)
```

Tested on Debian 12, Ubuntu 24.04, Arch Linux, Fedora, openSUSE Tumbleweed and Leap 15.6.

`./uninstall.sh` (or `./uninstall.sh --system`) removes the installed game and the build files.

### Development

```sh
./install.sh --build-only   # dependencies + build, ./bomberman at the repo root
./build-game.sh             # rebuild after a change
./bomberman                 # run from the repo root (data paths are relative)
```

Or with CMake directly:

```sh
cmake -S . -B build
cmake --build build -j
cmake --install build --prefix dist/bomberman   # self-contained game folder
```

Irrlicht is linked statically when the distribution ships a static library (Debian, Ubuntu), dynamically otherwise; `-DBOMBERMAN_STATIC_IRRLICHT=OFF` forces the shared library.

## Build on Windows

With Visual Studio 2022 and [vcpkg](https://vcpkg.io/):

```powershell
vcpkg install irrlicht:x64-windows-static
cmake -S . -B build -A x64 -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static
cmake --build build --config Release
cmake --install build --config Release --prefix dist/bomberman
```

`bomberman.exe` is standalone; it must be started from the folder containing `assets/`, `sound/` and `map/`. The installer is built from `packaging/windows/bomberman.iss` with [Inno Setup 6](https://jrsoftware.org/isinfo.php).

## Releases

Pushing a tag `v*` (e.g. `git tag v1.0 && git push origin v1.0`) builds the game for Linux and Windows in CI, tests the installer on every supported distribution and publishes the files above as a GitHub Release.
