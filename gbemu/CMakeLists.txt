
set(MAIN_SOURCES
  main.c
)

file (GLOB headers "${PROJECT_SOURCE_DIR}/include/*.h")

add_executable(gbemu ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(gbemu libgbe)
target_include_directories(gbemu PUBLIC ${PROJECT_SOURCE_DIR}/include )

install(TARGETS gbemu
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)

