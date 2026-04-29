cmake_minimum_required(VERSION 3.18)
project(voyageur-de-commerce)
add_compile_options(-Wall)
add_executable(${PROJECT_NAME}.out
algorithmes.cpp
main.cpp
tsp.cpp
)