//
// Created by zheboss on 11/23/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_INITIALISATION_OPERATIONS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_INITIALISATION_OPERATIONS_H

#include <main.h>

void intialisation_operations(Operation lst_operations[]);
void mergeOperations(Operation operations[], int *numOperations);
void readGraphFromFile(Operation operations[], int *numOperations);
void Affichage_Operations(const Operation operations[], int numOperations);


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_INITIALISATION_OPERATIONS_H
