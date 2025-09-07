cmake_minimum_required(VERSION 3.15)

project(listCatch2)

add_subdirectory(catch2)

# Библиотека со списком
add_library(list STATIC list.cpp)
target_include_directories(list PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} test.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    list
    Catch2WithMain
)