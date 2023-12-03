//
// Created by zheboss on 12/3/2023.
//

#include "multi_contraintes.h"
#include "precedence.h"
#include <exclusion.h>
#include <initialisation_operations.h>
#include <Traverser_les_operations.h>
#include <Time_module.h>
#include <stdio.h>
#include <stdlib.h>

#include <Fonctions_tests_affichage.h>

void exclusion_avec_cycle_de_temps() {
    //int **station;
    //exclusion(&station);


    // Access and print the contents of the 2D array
    /*for (int i = 0; station[i][0] != 0; i++) {
        printf("Station %d: %d\n", i, station[i][0]);
    }*/
    //Envoi de la station a la fonction calcul_duree_total
    //calcul_duree_total(station, 0, 1, operations);
    //calcul_duree_total(station, 1, 1, operations);
    //calcul_duree_total(station, 2, 1, operations);

    //printf("Duree total: %f\n", calcul_duree_total(station, 0, 1, operations));
    //printf("Duree total: %f\n", calcul_duree_total(station, 1, 1, operations));
    //printf("Duree total: %f\n", calcul_duree_total(station, 2, 1, operations));


    return;
}

void multi_contraintes() {
    affichage_multi_contraintes();

    printf("\nLa multi-contrainte est en cours de developpement suite a des erreurs d'execution de code. \n");

    //Fonction qui lance la contrainte de precendece et la contrainte d'exclusion en meme temps
    //exclusion_avec_cycle_de_temps();

    return;
}