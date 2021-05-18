
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

