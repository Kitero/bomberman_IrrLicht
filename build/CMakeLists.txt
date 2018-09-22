cmake_minimum_required(VERSION 3.0)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors -std=c++0x -std=c++11")
else (WIN32 || WIN64)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif ()

set(CMAKE_BUILD_TYPE Debug)

project(indie_studio)

execute_process(
  COMMAND mkdir ../lib
  )

execute_process(
  COMMAND tar -xzvf ../libirrlicht/includeirrlicht.tar.gz  -C ../libirrlicht/
  )

execute_process(
  COMMAND tar -xzvf ../libirrlicht/libirrlicht.tar.gz  -C ../libirrlicht/
  )

execute_process(
  COMMAND make -C ../libirrlicht/src/Irrlicht/
  )

execute_process(
  COMMAND cp ../libirrlicht/lib/Linux/libIrrlicht.a ../lib/
  )

include_directories(../libirrlicht/include)
include_directories(../Keypressed)
include_directories(../graphical)
include_directories(../map)
include_directories(../irrklang)
include_directories(../character)
include_directories(../game)
include_directories(../bombs)

set(SRCS
  ../graphical/Graph.cpp
  ../graphical/ObjectMap.cpp
  ../graphical/Render.cpp
  ../game/ObjectsGame.cpp
  ../game/BombsGamePlay.cpp
  ../game/Sound.cpp
  ../character/Character.cpp
  ../character/Move.cpp
  ../character/MoveDir.cpp
  ../bombs/Bomb.cpp
  ../bombs/SpecBomb.cpp
  ../map/Creation.cpp
  ../map/Init.cpp
  ../Keypressed/KeyPressed.cpp
  ../menu/menu.cpp
  ../graphical/Graph.hpp
  ../graphical/ObjectMap.hpp
  ../bombs/Bomb.hpp
  ../bombs/SpecBomb.hpp
  ../character/Character.hpp
  ../character/PlayerType.hpp
  ../game/irrlichtInc.hpp
  ../game/ObjectsGame.hpp
  ../game/vectorInc.hpp
  ../Keypressed/KeyPressedEvent.hpp
  ../map/Creation.hpp
  ../map/Init.hpp
)

link_directories(../lib)

add_executable(
  bomberman
  ${SRCS}
  )

target_link_libraries(
  bomberman
  libIrrKlang.so
  libIrrlicht.a
  GL
  Xxf86vm
  Xext
  X11
  )

execute_process(
  COMMAND rm -rf ../libirrlicht/src
  COMMAND rm -rf ../libirrlicht/lib
  )

execute_process(
  COMMAND mv bomberman ../
  )
