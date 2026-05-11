cmake_minimum_required(VERSION 3.18)

project(voyageur_de_commerce)

add_compile_options(-Wall)

add_executable(${PROJECT_NAME}
    algorithmes.cpp
    main.cpp
    tsp.cpp
)