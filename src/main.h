/* Header Main du projet TG 2023-2024
 *
 *
*/

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_MAIN_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_MAIN_H

typedef struct {
    int id;
    int *lst_precedents;
    float duree;
    int statut_complete; // 0 = non complete, 1 = complete
} Operation;

#define NB_OPERATIONS 35


#endif
