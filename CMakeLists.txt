cmake_minimum_required( VERSION 3.15 )
project( gameProgram )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable(${PROJECT_NAME} "classes/Chapter_1/main.cpp" "classes/Chapter_1/Game.cpp")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} )
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})