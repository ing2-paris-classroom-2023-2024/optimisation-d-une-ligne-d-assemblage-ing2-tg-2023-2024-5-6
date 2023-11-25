/* Header Main du projet TG 2023-2024
 *
 *
*/

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_MAIN_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_5_6_MAIN_H

#define NB_OPERATIONS 36
#define TEMPS_DE_CYCLE 10

typedef struct {
    int id;
    int *lst_precedents;
    int *lst_successeurs;
    float duree;
    int statut_complete; // 0 = non complete, 1 = complete
} Operation;




#endif