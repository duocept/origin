cmake_minimum_required(VERSION 3.12)

project(class_hierarchy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    Figure.cpp
    Triangle.cpp
    RightTriangle.cpp
    IsoscelesTriangle.cpp
    EquilateralTriangle.cpp
    Quadrangle.cpp
    RectangleQ.cpp
    Square.cpp
    Parallelogram.cpp
    Rhombus.cpp
)

set(HEADERS
    Figure.h
    Triangle.h
    RightTriangle.h
    IsoscelesTriangle.h
    EquilateralTriangle.h
    Quadrangle.h
    RectangleQ.h
    Square.h
    Parallelogram.h
    Rhombus.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})