cmake_minimum_required(VERSION 3.26)
project(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_5_6 C)

set(CMAKE_C_STANDARD 23)

include_directories(.)
include_directories(src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug)

add_executable(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_5_6
        src/main.c
        src/main.h
        src/initialisation_operations.c
        src/initialisation_operations.h
        src/Time_module.c
        src/Time_module.h
        src/Time_module.c
        src/Fonctions_tests_affichage.c
        src/Fonctions_tests_affichage.h
        src/Traverser_les_operations.c
        src/Traverser_les_operations.h
        src/precedence.c
        src/precedence.h
)
