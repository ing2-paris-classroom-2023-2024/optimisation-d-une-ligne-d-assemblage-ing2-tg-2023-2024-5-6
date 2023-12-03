//
// Created by zheboss on 11/24/2023.
//

#include "Time_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <main.h>


//Initisalisation de la duree pour chaque operations en utilisant le .txt "operations.txt"
void initialisation_duree(Operation operations[]) {
    FILE *file = fopen("operations.txt", "r");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    int id;
    float duration;



    while (fscanf(file, "%d %f", &id, &duration) == 2) {
        operations[id - 1].duree = duration; // Assuming IDs start from 1
        //printf("Operation %d: %f\n", id, duration);
    }

    fclose(file);

    // Gestion d'operations manquantes
    for (int i = 0; i < NB_OPERATIONS; i++) {
        if (operations[i].duree < 0 || operations[i].duree > TEMPS_DE_CYCLE) {
            // Init a 0 si invalide
            printf("Operation %d has an invalid duration. Setting duration to 0.\n", operations[i].id);
            operations[i].duree = 0;
        }
    }
    printf("---------------------------------\n");
    printf("Initialisation des durees terminee.\n");
}

