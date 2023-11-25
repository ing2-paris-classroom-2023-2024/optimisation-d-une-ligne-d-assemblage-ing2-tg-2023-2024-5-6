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
void initialisation_duree(Operation lst_operations[]) {
    FILE *file = fopen("operations.txt", "r");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    int id_operation;
    float duree_operation;
    int indice = 0;

    while (fscanf(file, "%d %f", &id_operation, &duree_operation) != EOF) {
        lst_operations[indice].duree = duree_operation;
        printf("Operation %d : %f [Indice dans tableau: %d]\n", id_operation, duree_operation, id_operation-1);
        indice++;
    }

    fclose(file);
    printf("Initialisation des durees terminee.\n");
}

