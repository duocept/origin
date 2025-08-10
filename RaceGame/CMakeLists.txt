cmake_minimum_required(VERSION 3.22)
project(RacingSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Avoid Windows min/max macros and trim Windows headers
add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN)

# Optionally help MSVC produce UTF-8 console output
if(MSVC)
  add_compile_options(/utf-8)
endif()

add_subdirectory(lib)

add_executable(racing_app app/main.cpp)
target_link_libraries(racing_app PRIVATE racing_lib)
# Ensure DLL/so is next to the executable for runtime on Windows and others
add_custom_command(TARGET racing_app POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:racing_lib>
          $<TARGET_FILE_DIR:racing_app>)

