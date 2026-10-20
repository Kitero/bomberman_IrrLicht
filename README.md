# Bomberman (Irrlicht)

A 3D Bomberman written in C++11 with [Irrlicht](https://irrlicht.sourceforge.io/) (graphics) and [irrKlang](https://www.ambiera.com/irrklang/) (sound).

## Download

Prebuilt Linux x86_64 builds are attached to the [GitHub Releases](../../releases).

```sh
tar xzf bomberman-linux-x86_64.tar.gz
./bomberman/run.sh
```

Runtime requirements: OpenGL, X11, libpng, libjpeg, zlib, bzip2 (present on any desktop distribution).

## Build from source

Dependencies (Debian/Ubuntu):

```sh
sudo apt install cmake g++ libirrlicht-dev libgl1-mesa-dev libxxf86vm-dev libxext-dev \
  libpng-dev libjpeg-dev zlib1g-dev libbz2-dev
```

Build and run:

```sh
./install.sh      # configure + build, puts ./bomberman at the repo root
./bomberman       # must be run from the repo root (data paths are relative)
```

- `./build-game.sh` rebuilds after a change.
- `./uninstall.sh` removes the build files and the binary.

Or with CMake directly:

```sh
cmake -S . -B build
cmake --build build -j
cmake --install build --prefix dist/bomberman   # self-contained game folder
```

Irrlicht is linked statically by default; pass `-DBOMBERMAN_STATIC_IRRLICHT=OFF` to link the shared library instead.

## Releases

Pushing a tag `v*` (e.g. `git tag v1.0 && git push origin v1.0`) builds the game in CI and publishes `bomberman-linux-x86_64.tar.gz` as a GitHub Release.

## Notes

- irrKlang is proprietary and free for non-commercial use only; its prebuilt Linux x86_64 library is shipped in `lib/`.
