cmake_minimum_required(VERSION 3.26)
project(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_5_6 C)

set(CMAKE_C_STANDARD 23)

include_directories(.)
include_directories(src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug)

add_executable(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_5_6
        src/main.c
        src/main.h
)
