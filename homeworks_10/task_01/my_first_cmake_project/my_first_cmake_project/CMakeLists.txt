add_executable (my_first_cmake_programm main.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET my_first_cmake_programm PROPERTY CXX_STANDARD 20)
endif()