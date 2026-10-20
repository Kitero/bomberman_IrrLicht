cmake_minimum_required(VERSION 3.18)

project(indie_studio LANGUAGES C CXX)

# vcpkg static triplets (x64-windows-static) use the static MSVC runtime
if (VCPKG_TARGET_TRIPLET MATCHES "-static$")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()

# Link Irrlicht statically when possible so the shipped binary does not need it installed.
option(BOMBERMAN_STATIC_IRRLICHT "Link Irrlicht statically when a static library is available" ON)

set(SRCS
  graphical/Graph.cpp
  graphical/ObjectMap.cpp
  graphical/Render.cpp
  game/ObjectsGame.cpp
  game/BombsGamePlay.cpp
  game/Sound.cpp
  character/Character.cpp
  character/Move.cpp
  character/MoveDir.cpp
  bombs/Bomb.cpp
  bombs/SpecBomb.cpp
  map/Creation.cpp
  map/Init.cpp
  Keypressed/KeyPressed.cpp
  menu/menu.cpp
)

# miniaudio (vendored, public domain): sound output and wav/ogg decoding
add_library(miniaudio STATIC third_party/miniaudio/miniaudio.c)
target_include_directories(miniaudio PUBLIC third_party/miniaudio)
if (UNIX)
  find_package(Threads REQUIRED)
  # Audio backends (ALSA, PulseAudio...) are loaded at runtime with dlopen
  target_link_libraries(miniaudio PUBLIC Threads::Threads ${CMAKE_DL_LIBS} m)
endif ()

add_executable(bomberman ${SRCS})

target_include_directories(bomberman PRIVATE
  Keypressed
  graphical
  map
  character
  game
  bombs
)

target_link_libraries(bomberman PRIVATE miniaudio)

if (WIN32)
  # Irrlicht from vcpkg (use the x64-windows-static triplet for a standalone .exe)
  find_package(irrlicht CONFIG REQUIRED)
  find_package(ZLIB REQUIRED)
  find_package(PNG REQUIRED)
  find_package(JPEG REQUIRED)
  find_package(BZip2 REQUIRED)
  target_link_libraries(bomberman PRIVATE
    Irrlicht
    ZLIB::ZLIB
    PNG::PNG
    JPEG::JPEG
    BZip2::BZip2
    opengl32
    winmm
  )
  # Game window only, no console
  set_target_properties(bomberman PROPERTIES WIN32_EXECUTABLE ON)
  if (MSVC)
    # Keep the standard main() entry point with the WIN32 subsystem
    target_link_options(bomberman PRIVATE /ENTRY:mainCRTStartup)
    target_compile_definitions(bomberman PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif ()
else ()
  # Irrlicht from the system (libirrlicht-dev, irrlicht, irrlicht-devel...)
  find_path(IRRLICHT_INCLUDE_DIR irrlicht.h PATH_SUFFIXES irrlicht REQUIRED)
  if (BOMBERMAN_STATIC_IRRLICHT)
    find_library(IRRLICHT_STATIC_LIBRARY NAMES libIrrlicht.a)
  endif ()
  target_include_directories(bomberman PRIVATE ${IRRLICHT_INCLUDE_DIR})

  if (IRRLICHT_STATIC_LIBRARY)
    message(STATUS "Irrlicht: static (${IRRLICHT_STATIC_LIBRARY})")
    set(OpenGL_GL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    find_package(PNG REQUIRED)
    find_package(JPEG REQUIRED)
    find_package(ZLIB REQUIRED)
    find_package(BZip2 REQUIRED)
    if (NOT X11_Xxf86vm_LIB)
      message(FATAL_ERROR "libXxf86vm not found (libxxf86vm-dev)")
    endif ()
    target_link_libraries(bomberman PRIVATE
      ${IRRLICHT_STATIC_LIBRARY}
      OpenGL::GL
      ${X11_Xxf86vm_LIB}
      ${X11_Xext_LIB}
      ${X11_X11_LIB}
      PNG::PNG
      JPEG::JPEG
      ZLIB::ZLIB
      BZip2::BZip2
    )
  else ()
    find_library(IRRLICHT_LIBRARY NAMES Irrlicht REQUIRED)
    message(STATUS "Irrlicht: shared (${IRRLICHT_LIBRARY})")
    target_link_libraries(bomberman PRIVATE ${IRRLICHT_LIBRARY})
  endif ()
endif ()

# The game loads its data with paths relative to the working directory,
# so the binary lands at the repository root, next to assets/ and sound/.
set_target_properties(bomberman PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
)

# `cmake --install` produces a self-contained, relocatable game folder
install(TARGETS bomberman RUNTIME DESTINATION .)
install(DIRECTORY assets sound DESTINATION .
  PATTERN "*.blend" EXCLUDE
  PATTERN "*.blend1" EXCLUDE
  PATTERN "*.max" EXCLUDE
  PATTERN "*.c4d" EXCLUDE
  PATTERN "*.fbx" EXCLUDE
  PATTERN "*.psk" EXCLUDE
  PATTERN "*.zip" EXCLUDE
)
install(DIRECTORY map/Maps DESTINATION map)
install(FILES README.md DESTINATION .)
if (UNIX)
  install(PROGRAMS run.sh DESTINATION .)
endif ()
