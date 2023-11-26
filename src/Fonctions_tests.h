//
// Created by zheboss on 11/26/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_FONCTIONS_TESTS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_FONCTIONS_TESTS_H

#include <main.h>

int gestion_precedence(Operation lst_operations[]);
int P_est_vide(int P[]);
void initializeClock(t_clock *clock);
void tick(t_clock *clock, Operation *operation);

void affichage_attributs_operations(Operation op[], int numOperation);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_FONCTIONS_TESTS_H
