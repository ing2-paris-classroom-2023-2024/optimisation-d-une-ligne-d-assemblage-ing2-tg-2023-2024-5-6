//
// Created by zheboss on 11/26/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_TRAVERSER_LES_OPERATIONS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_TRAVERSER_LES_OPERATIONS_H


#include <precedence.h>

int recherche_indice_id(int id, Operation op[], int numOperation);
int recherche_sucesseurs(Operation op[], int id, int lst_sucesseurs[], int numOperation);
int id_in_pile(int id, int Pile[]);
int recherche_precedents(Operation op[], int id);

/*****************
 * FONCTION MERE *
 *****************/
void traverse_operations(Operation op[], int startOperation, int numOperation);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_TRAVERSER_LES_OPERATIONS_H
