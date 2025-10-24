cmake_minimum_required(VERSION 3.20)
project(client_manager)
set(PostgreSQL_ADDITIONAL_VERSIONS "17")

add_executable(client_manager main.cpp)


add_subdirectory(C:/Users/Duo/Desktop/Netology_Homework/sqlcpp_homeworks_05/task_01/libpqxx libpqxx-build)
target_compile_features(client_manager PRIVATE cxx_std_17)
target_link_libraries(client_manager PRIVATE pqxx)
