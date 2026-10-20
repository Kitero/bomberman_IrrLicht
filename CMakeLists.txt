cmake_minimum_required(VERSION 3.16)

project(indie_studio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()

# Link Irrlicht statically so the shipped binary does not need it installed.
option(BOMBERMAN_STATIC_IRRLICHT "Link Irrlicht statically" ON)

# Irrlicht (Debian/Ubuntu: libirrlicht-dev)
find_path(IRRLICHT_INCLUDE_DIR irrlicht.h PATH_SUFFIXES irrlicht REQUIRED)
if (BOMBERMAN_STATIC_IRRLICHT)
  find_library(IRRLICHT_LIBRARY NAMES libIrrlicht.a REQUIRED)
else ()
  find_library(IRRLICHT_LIBRARY NAMES Irrlicht REQUIRED)
endif ()

# irrKlang is proprietary and only shipped prebuilt (Linux x86_64)
set(IRRKLANG_LIBRARY ${CMAKE_SOURCE_DIR}/lib/libIrrKlang.so)

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

add_executable(bomberman ${SRCS})

target_include_directories(bomberman PRIVATE
  ${IRRLICHT_INCLUDE_DIR}
  irrklang
  Keypressed
  graphical
  map
  character
  game
  bombs
)

target_link_libraries(bomberman PRIVATE ${IRRLICHT_LIBRARY} ${IRRKLANG_LIBRARY})

if (BOMBERMAN_STATIC_IRRLICHT)
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
    OpenGL::GL
    ${X11_Xxf86vm_LIB}
    ${X11_Xext_LIB}
    ${X11_X11_LIB}
    PNG::PNG
    JPEG::JPEG
    ZLIB::ZLIB
    BZip2::BZip2
  )
endif ()

# The game loads its data with paths relative to the working directory,
# so the binary lands at the repository root, next to assets/ and lib/.
set_target_properties(bomberman PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
  BUILD_RPATH "\$ORIGIN/lib"
  INSTALL_RPATH "\$ORIGIN/lib"
)

# `cmake --install` produces a self-contained, relocatable game folder
install(TARGETS bomberman RUNTIME DESTINATION .)
install(FILES ${IRRKLANG_LIBRARY} DESTINATION lib)
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
install(PROGRAMS run.sh DESTINATION .)
install(FILES README.md DESTINATION .)
