
set(LIB_SOURCES
  bus.c
  cpu.c
  emu.c
  cart.c
  ppu.c
  timer.c
)

file (GLOB headers "${PROJECT_SOURCE_DIR}/include/*.h")

add_library(libgbe STATIC ${LIB_SOURCES} ${HEADERS})

target_include_directories(libgbe PUBLIC ${PROJECT_SOURCE_DIR}/include )

if (WIN32)
target_include_directories(libgbe PUBLIC ${PROJECT_SOURCE_DIR}/windows_deps/sdl2/include )
target_include_directories(libgbe PUBLIC ${PROJECT_SOURCE_DIR}/windows_deps/sdl2_ttf/include )
endif()

#find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(libgbe ${SDL2_LIBRARIES})

include_directories(${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(libgbe ${SDL2_TTF_LIBRARIES})
