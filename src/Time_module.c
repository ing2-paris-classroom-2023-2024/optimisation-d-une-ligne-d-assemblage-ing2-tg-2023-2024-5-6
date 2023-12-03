//
// Created by zheboss on 11/24/2023.
//

#include "Time_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <initialisation_operations.h>
#include <color.h>
#include <Traverser_les_operations.h>


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

float calcul_duree_total(int stations[NB_OPERATIONS], int i, int version, Operation operations[]) {
    float duree_total = 0;

    //En fonction de la version, on utilisera soit la station, soit l'operation
    switch (version) {
        case 1:
            //On parcourt les operations de la station
            for (int j = 0; j < NB_OPERATIONS; j++) {
                if (stations[j] != 0) {
                    //On recherche dans l'operation correspndante a la valeur stations[i][j]en utilisant recherche_indice_id
                    duree_total += operations[recherche_indice_id(stations[j], operations, NB_OPERATIONS)].duree;
                }
            }
            //On regarde si duree total est superieur a la duree de cycle
            if (duree_total > TEMPS_DE_CYCLE) {
                printf("Duree totale: %f ms\n", duree_total);
                printf("La duree totale depasse le temps de cycle.\n");
                return 0;
            }
            break;
        case 2:
            duree_total += operations[i].duree;
        default:
            break;
    }

    return duree_total;
}