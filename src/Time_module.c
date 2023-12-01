//
// Created by zheboss on 11/24/2023.
//

#include "Time_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <main.h>

#include <time.h>
#include <windows.h>

#include <Time_module.h>

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
        printf("Operation %d: %f\n", id, duration);
    }

    fclose(file);

    // Handle missing operations (set duration to 0)
    for (int i = 0; i < NB_OPERATIONS; i++) {
        if (operations[i].duree < 0 || operations[i].duree > TEMPS_DE_CYCLE) {
            // Set duration to 0 for missing operations
            printf("Operation %d has an invalid duration. Setting duration to 0.\n", operations[i].id);
            operations[i].duree = 0;
        }
    }
    printf("Initialisation des durees terminee.\n");
}

