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
#include <color.h>

#include <Fonctions_tests_affichage.h>

void exclusion_avec_cycle_de_temps(int **station, Operation *operations) {

    //Envoi de la station a la fonction calcul_duree_total
    float duree1 = calcul_duree_total(station, 0, 1, operations);
    float duree2 = calcul_duree_total(station, 1, 1, operations);
    float duree3 = calcul_duree_total(station, 2, 1, operations);

    printf("Duree total 1: %f\n", duree1);
    printf("Duree total 2: %f\n", duree2);
    printf("Duree total 3: %f\n", duree3);


    return;
}

void multi_contraintes(int **station, Operation *operations) {
    affichage_multi_contraintes();


    printf("\nLa multi-contrainte est en cours de developpement suite a des erreurs d'execution de code. \n");

    //Fonction qui lance la contrainte de precendece et la contrainte d'exclusion en meme temps
    exclusion_avec_cycle_de_temps(station, operations);

    return;
}