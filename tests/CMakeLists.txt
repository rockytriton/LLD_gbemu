include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

set(TEST_SOURCES
  check_gbe.c
)

add_executable(check_gbe ${TEST_SOURCES})
target_link_libraries(check_gbe libgbe ${CHECK_LIBRARIES})
target_include_directories(check_gbe PRIVATE ${PROJECT_SOURCE_DIR}/include )

if (WIN32)
target_include_directories(libgbe PUBLIC ${PROJECT_SOURCE_DIR}/windows_deps/check )
endif()

if (WIN32)
# copy the .dll file to the same folder as the executable
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:CHECK>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif()
