cmake_minimum_required(VERSION 3.16)

project(class_hierarchy LANGUAGES CXX)

add_executable(class_hierarchy
    main.cpp
    Figure.cpp Figure.h
    Triangle.cpp Triangle.h
    RightTriangle.cpp RightTriangle.h
    IsoscelesTriangle.cpp IsoscelesTriangle.h
    EquilateralTriangle.cpp EquilateralTriangle.h
    Quadrangle.cpp Quadrangle.h
    RectangleQ.cpp RectangleQ.h
    Square.cpp Square.h
    Parallelogram.cpp Parallelogram.h
    Rhombus.cpp Rhombus.h
)

target_compile_features(class_hierarchy PRIVATE cxx_std_17)