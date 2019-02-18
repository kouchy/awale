# CMake entry point
cmake_minimum_required (VERSION 3.0.2)
cmake_policy(SET CMP0054 NEW)

project (awale)

option (AWALE_NETWORK "Enable multiplayer Awale" OFF)

if (AWALE_NETWORK)
	add_definitions (-DAWALE_NETWORK)
endif()

# Specify bin path
set (EXECUTABLE_OUTPUT_PATH bin/)

# Generate the source files list
file (GLOB_RECURSE source_files src/*)

find_package(SDL)
find_package(SDL_image)
find_package(SDL_ttf)
if (SDL_FOUND AND SDL_IMAGE_FOUND AND SDL_TTF_FOUND)
	add_definitions (-DAWALE_SDL)
	include_directories(${SDL_INCLUDE_DIR} ${SDL_TTF_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS})
endif()

find_package(SDL_mixer)
if (SDL_MIXER_FOUND)
	add_definitions (-DAWALE_SDL_SOUND)
	include_directories(${SDL_MIXER_INCLUDE_DIRS})
endif()

# Define the objects from the source files
add_library (awale-obj OBJECT ${source_files})
add_executable(awale-bin $<TARGET_OBJECTS:awale-obj>)
set_target_properties (awale-bin PROPERTIES OUTPUT_NAME awale)

if (SDL_FOUND AND SDL_IMAGE_FOUND AND SDL_TTF_FOUND)
	target_link_libraries(awale-bin ${SDL_LIBRARY} ${SDL_TTF_LIBRARIES} ${SDL_IMAGE_LIBRARIES})
endif()

if (SDL_MIXER_FOUND)
	target_link_libraries(awale-bin ${SDL_MIXER_LIBRARIES})
endif()