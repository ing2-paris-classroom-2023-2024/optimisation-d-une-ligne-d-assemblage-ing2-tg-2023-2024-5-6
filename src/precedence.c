//
// Created by zheboss on 12/3/2023.
//

#include "precedence.h"
#include <initialisation_operations.h>
#include <Traverser_les_operations.h>
#include <Time_module.h>
#include <stdio.h>

int precedence() {
    Operation operations[NB_OPERATIONS];
    int numOperations = 0;


    lecture_de_fichier(operations, &numOperations);
    fusion_Operations(operations, &numOperations);

    initialisation_duree(operations);
    initialisation_successeurs(operations);

    //affichage_attributs_operations(operations, numOperations);

    printf("---------------------------------------------\n");
    //Affichage_Operations(operations, numOperations);
    printf("---------------------------------------------\n");
    printf("|         CONTRAINTE DE PRECEDENCE          |\n");
    printf("---------------------------------------------\n");

    // Appel de la fonction qui va parcourir les operations
    traverse_operations(operations, 0, numOperations);


    return 0;
}