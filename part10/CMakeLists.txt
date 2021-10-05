project(gbemu C)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

###############################################################################
# Set build features
set(CMAKE_BUILD_TYPE Debug)

###############################################################################
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

###############################################################################
# Check headers
set(INCLUDES "")
macro(ck_check_include_file header var)
  check_include_files("${INCLUDES};${header}" ${var})
  if(${var})
    set(INCLUDES ${INCLUDES} ${header})
  endif(${var})
endmacro(ck_check_include_file)

ck_check_include_file("stdlib.h" HAVE_STDLIB_H)

###############################################################################
# Check for integer types
# (The following are used in check.h. Regardless if they are used in
# the project, they will need to be checked in order to use Check).
check_type_size(intmax_t INTMAX_T)
check_type_size(uintmax_t UINTMAX_T)

check_type_size(pid_t PID_T)
if(NOT HAVE_PID_T)
  if(WIN32)
    set(pid_t "int")
  else(WIN32)
    MESSAGE(FATAL_ERROR "pid_t doesn't exist on this platform?")
  endif(WIN32)
endif(NOT HAVE_PID_T)

if(WIN32)
  set(SDL2_DIR "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2")
  set(SDL2_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/include;${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/include/SDL2")

  # Support both 32 and 64 bit builds
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/lib/x64/SDL2.lib;${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/lib/x64/SDL2main.lib")
  else ()
    set(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/lib/x86/SDL2.lib;${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/lib/x86/SDL2main.lib")
  endif ()

  string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

  set(SDL2_TTF_DIR "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf")
  set(SDL2_TTF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/include")

  # Support both 32 and 64 bit builds
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_TTF_LIBRARIES "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/lib/x64/SDL2_ttf.lib")
  else ()
    set(SDL2_TTF_LIBRARIES "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/lib/x86/SDL2_ttf.lib")
  endif ()

  string(STRIP "${SDL2_TTF_LIBRARIES}" SDL2_TTF_LIBRARIES)
else()
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
  find_package(SDL2 REQUIRED)
  find_package(SDL2_ttf REQUIRED)
endif()

###############################################################################
# Generate "config.h" from "cmake/config.h.cmake"
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DHAVE_CONFIG_H)
set(CONFIG_HEADER ${CMAKE_CURRENT_BINARY_DIR}/config.h)


###############################################################################
# Subdirectories
add_subdirectory(lib)
add_subdirectory(gbemu)
add_subdirectory(tests)

###############################################################################
# Unit tests
enable_testing()
add_test(NAME check_gbe COMMAND check_gbe)

