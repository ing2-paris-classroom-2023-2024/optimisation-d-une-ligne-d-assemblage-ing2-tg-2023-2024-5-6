//
// Created by zheboss on 12/3/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_PRECEDENCE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_PRECEDENCE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include "main.h"

#include "initialisation_operations.h"
#include "Fonctions_tests_affichage.h"
#include "Traverser_les_operations.h"
#include "Time_module.h"

#define NB_OPERATIONS 36
#define TEMPS_DE_CYCLE 10

typedef struct {
    int id;
    int *lst_precedents;
    int *lst_successeurs;
    float duree;
    int statut_complete; // 0 = non complete, 1 = complete
} Operation;

typedef struct {
    float current_time;
} t_clock;


int precedence();

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_PRECEDENCE_H
