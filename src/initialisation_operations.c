//
// Created by zheboss on 11/23/2023.
//

#include "initialisation_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <main.h>

void intialisation_operations(Operation lst_operations[]) {
    int i;
    for (i = 0; i < NB_OPERATIONS; i++) {
        lst_operations[i].id = i;
        lst_operations[i].duree = 0;
        lst_operations[i].statut_complete = 0;
        //Initailiser toute valeur de precedents a 0
        for (int j = 0; j < NB_OPERATIONS; j++) {
            lst_operations[i].lst_precedents[j] = 0;
        }
    }
    printf("Initialisation des operations terminee.\n");
}

int cmpfunc(const void *a, const void *b) {
    Operation *operationA = (Operation *)a;
    Operation *operationB = (Operation *)b;
    return operationA->id - operationB->id;
}

void mergeOperations(Operation operations[], int *numOperations) {
    qsort(operations, *numOperations, sizeof(Operation), cmpfunc);

    for (int i = 0; i < *numOperations - 1; i++) {
        if (operations[i].id == operations[i + 1].id) {
            for (int j = 0; operations[i + 1].lst_precedents[j] != 0; j++) {
                operations[i].lst_precedents[j + 1] = operations[i + 1].lst_precedents[j];
            }
            for (int j = i + 1; j < *numOperations - 1; j++) {
                operations[j] = operations[j + 1];
            }
            (*numOperations)--;
            i--;
        }
    }
    for (int i = 0; i < *numOperations; i++) {
        for (int j = 0; operations[i].lst_precedents[j] != 0; j++) {
            if (operations[i].lst_precedents[j] > NB_OPERATIONS) { operations[i].lst_precedents[j] = 0; }
        }
    }
    printf("Merge des operations terminee.\n");
}

void readGraphFromFile(Operation operations[], int *numOperations) {
    printf("Lecture du graphe...\n");
    FILE *file = fopen("graphe.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    printf("-----------------1----------------\n");

    *numOperations = 0;
    //On transforme lst_precedents en tableau de int avec malloc
    for (int i = 0; i < NB_OPERATIONS; i++) {
        operations[i].lst_precedents = malloc(NB_OPERATIONS * sizeof(int));
    }
    printf("-----------------2----------------\n");

    while (fscanf(file, "%d %d %f", &operations[*numOperations].lst_precedents[0],
                  &operations[*numOperations].id,
                  &operations[*numOperations].duree) == 3) {
        if (operations[*numOperations].lst_precedents[0] > NB_OPERATIONS)
        { operations[*numOperations].lst_precedents[0] = 0; }
        printf("-----------------3-[%d]--------------\n", *numOperations);
        // Increment the operation count
        (*numOperations)++;
        //si numOperations est superieur a 0, on realloc lst_precedents
        if (*numOperations > 1) {
            operations[*numOperations - 1].lst_precedents = realloc(operations[*numOperations - 1].lst_precedents,
                                                                    (*numOperations) * sizeof(int));
        }
        printf("%d ", operations[*numOperations].lst_precedents[0]);
    }
    fclose(file);
    printf("---------------------------------\n");
    printf("Lecture du graphe terminee.\n");
}

void Affichage_Operations(const Operation operations[], int numOperations) {
    // Fonction d'affichage des opérations
    for (int i = 0; i < numOperations; i++) {
        printf("Operation %d:\n", operations[i].id);
        printf("  Duration: %.2f\n", operations[i].duree);
        printf("  Status: %d\n", operations[i].statut_complete);
        printf("  Precedents: ");

        for (int j = 0; operations[i].lst_precedents[j] != 0; j++) {
            printf("%d |", operations[i].lst_precedents[j]);
        }
        printf("\n\n");
    }
}