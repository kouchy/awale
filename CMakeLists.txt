# CMake entry point
cmake_minimum_required (VERSION 3.0.2)
cmake_policy(SET CMP0054 NEW)

project (awale)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

option (AWALE_NETWORK "Enable multiplayer Awale" OFF)

if (AWALE_NETWORK)
    add_definitions (-DAWALE_NETWORK)
endif()

# Specify bin path
set (EXECUTABLE_OUTPUT_PATH bin/)

# Generate the source files list
file (GLOB_RECURSE source_files src/*)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
include_directories(${SDL_INCLUDE_DIR} ${SDL_TTF_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS})

find_package(FMOD)
if (FMOD_FOUND)
    add_definitions (-DAWALE_FMOD)
    include_directories(${FMOD_INCLUDE_DIR})
endif()

# Define the objects from the source files
add_library (awale-obj OBJECT ${source_files})
add_executable(awale-bin $<TARGET_OBJECTS:awale-obj>)
set_target_properties (awale-bin PROPERTIES OUTPUT_NAME awale)

target_link_libraries(awale-bin ${SDL_LIBRARY} ${SDL_TTF_LIBRARIES} ${SDL_IMAGE_LIBRARIES})

if (FMOD_FOUND)
    target_link_libraries(awale-bin ${FMOD_LIBRARY})
endif()