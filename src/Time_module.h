//
// Created by zheboss on 11/24/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_TIME_MODULE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_TIME_MODULE_H

#include <initialisation_operations.h>


/*****************
 * FONCTION MERE *
 *****************/
void initialisation_duree(Operation lst_operations[]);
float calcul_duree_total(int **stations, int i, int version, Operation operations[]);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_TIME_MODULE_H
