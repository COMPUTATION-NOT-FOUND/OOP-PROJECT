cmake_minimum_required(VERSION 3.26)
project(GAME_PROJ)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

# SDL2
set(SDL2_PATH "libraries\\SDL2-2.30.1\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# SDL2_image
set(SDL2_IMAGE_PATH "libraries\\SDL2_image-2.8.2\\x86_64-w64-mingw32")
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# SDL2_ttf
set(SDL2_TTF_PATH "libraries\\SDL2_ttf-2.22.0\\x86_64-w64-mingw32")
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# SDL2_mixer
set(SDL2_MIXER_PATH "libraries\\SDL2_mixer-2.8.0\\x86_64-w64-mingw32")
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

add_executable(GAME_PROJ
        src/main.cpp
        src/Game.cpp
        src/TextureManager.cpp
        src/GameObject.cpp
        src/Map.cpp
)

target_link_libraries(GAME_PROJ ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

