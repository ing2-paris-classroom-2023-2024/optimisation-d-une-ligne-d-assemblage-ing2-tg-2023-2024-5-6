//
// Created by zheboss on 12/3/2023.
//

#include "precedence.h"
#include <initialisation_operations.h>
#include <Traverser_les_operations.h>
#include <Time_module.h>
#include <stdio.h>
#include <stdlib.h>

#include <Fonctions_tests_affichage.h>

int precedence( Operation operations[], int numOperations) {
    affichage_precedence();

    // Appel de la fonction qui va parcourir les operations
    traverse_operations(operations, 0, numOperations);


    return 0;
}

void initialisation_graphe_p() {
    Operation operations[NB_OPERATIONS];
    int numOperations = 0;

    affichage_init_graphe();


    lecture_de_fichier(operations, &numOperations);
    fusion_Operations(operations, &numOperations);

    initialisation_duree(operations);
    initialisation_successeurs(operations);

    precedence(operations, numOperations);
}