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


int find_missing_operations(Operation op[], int numOperation, int missing[]) {

    int numMissing = 0;
    // Create a boolean array to mark the presence of operations
    int presence[NB_OPERATIONS-1]; // +1 to account for 1-based indexing

    for (int i = 0; i < NB_OPERATIONS-1; i++) {
        presence[i] = 0; // Initialize to 0, indicating the operation is missing
    }

    // Mark the presence of existing operations
    for (int i = 0; i < NB_OPERATIONS; i++) {
        presence[op[i].id] = 1;
    }

    // Find and store missing operations in the 'missing' array
    for (int i = 1; i < NB_OPERATIONS-1; i++) {
        if (presence[i] == 0) {
            missing[numMissing] = i;
            numMissing++;
        }
    }

    return numMissing;

}

void matrice_to_array(int matrice[][NB_OPERATIONS], Operation op[]) {
    int missing[NB_OPERATIONS];
    int numMissing = find_missing_operations(op, NB_OPERATIONS, missing);

    for (int k = 0; k < NB_OPERATIONS; k++) {
        int size = NB_OPERATIONS - numMissing;
        op[k].lst_successeurs = malloc(size * sizeof(int));
        op[k].lst_successeurs[0] = 0;
    }
    for (int i = 0; i < NB_OPERATIONS; i++) {
        int indice = 0;
        for (int j = 0; j < NB_OPERATIONS; j++) {
            if (matrice[i][j] == 1) {
                int adjustedIndex = j + 1;
                //printf("==========================\n");
                for (int m = 0; m < numMissing; m++) {
                    if (missing[m] <= adjustedIndex) {
                        adjustedIndex++;
                        //printf("Nombre manquant missing[%d]\n", missing[m]);
                    }
                }

                //printf("INDEX: %d\n", adjustedIndex);
                //printf("Matrice[%d][%d]\n", i, j);
                //printf("Operation %d [indice: %d]: %d\n", i+1, indice, adjustedIndex);
                //Assurer que l'operation est bien borne entre 1 et NB_OPERATIONS
                if (0 < adjustedIndex && adjustedIndex < NB_OPERATIONS) {
                    //printf("Operation %d [indice: %d]: %d\n", i+1, indice, adjustedIndex);
                    op[i].lst_successeurs[indice] = adjustedIndex;
                    //printf("Operation[%d].lst_successeurs[%d] = %d\n", i, indice, op[i].lst_successeurs[indice]);
                }
                indice++;
            }
        }
        op[i].lst_successeurs[indice] = 0;
    }
    //Affichage des successeurs
    for (int i = 0; i < NB_OPERATIONS; i++) {
        printf("Operation %d: ", op[i].id);
        for (int j = 0; op[i].lst_successeurs[j] != 0; j++) {
            printf("%d ", op[i].lst_successeurs[j]);
        }
        printf("\n");
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++\n");
}



int initialisation_successeurs(Operation lst_operations[]) {
    //Avec le tableau de precedence, nous allons l'inverser.
    //Cela falicitera la recherche de l'operation suivante.
    //Par exemple, si le precendent de 6 est 1, alors dans le nouveau tableau, l'operation 1 contiendra 6 dans son tableau de successeurs.
    //On pourra donc trouver l'operation suivante en cherchant dans le tableau de successeurs de l'operation precedente.

    //On cree un tableau de successeurs
    int tableau_successeurs[NB_OPERATIONS][NB_OPERATIONS];

    for (int i = 0; i < NB_OPERATIONS; i++) {
        for (int j = 0; j < NB_OPERATIONS; j++) {
            tableau_successeurs[i][j] = 0;
        }
    }

    //On remplit le tableau de successeurs
    //On prend en compte les operations manquantes
    for (int i = 0; i < NB_OPERATIONS; i++) {
        for (int j = 0; lst_operations[i].lst_precedents[j] != 0; j++) {
            int index = recherche_indice_id(lst_operations[i].lst_precedents[j], lst_operations, NB_OPERATIONS);
            //Si j est present dans le tableau de precedents de i, alors i est present dans le tableau de successeurs de j
            //On prend en compte les operations manquantes
            tableau_successeurs[index][i] = 1;
        }
    }

    //Affichage du tableau de successeurs
    for (int i = 0; i < NB_OPERATIONS; i++) {
        printf("Operation %d: ", lst_operations[i].id);
        for (int j = 0; j < NB_OPERATIONS; j++) {
            printf("%d ", tableau_successeurs[i][j]);
        }
        printf("\n");
    }

    matrice_to_array(tableau_successeurs, lst_operations);

    printf("Initialisation des successeurs terminee.\n");
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

    *numOperations = 0;
    //On transforme lst_precedents en tableau de int avec malloc
    for (int i = 0; i < NB_OPERATIONS; i++) {
        operations[i].lst_precedents = malloc(NB_OPERATIONS * sizeof(int));
        operations[i].statut_complete = 0;
    }

    while (fscanf(file, "%d %d", &operations[*numOperations].lst_precedents[0],
                  &operations[*numOperations].id) == 2) {
        if (operations[*numOperations].lst_precedents[0] > NB_OPERATIONS)
        { operations[*numOperations].lst_precedents[0] = 0; }
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
    for (int i = 0; i < NB_OPERATIONS-2; i++) {
        printf("Operation %d: ", i + 1);
        printf("  Duration: %.2f\n", operations[i].duree);
        printf("  Status: %d\n", operations[i].statut_complete);

        printf("  Successors: ");
        for (int j = 0; operations[i].lst_successeurs[j] != 0; j++) {
            printf(" %d ", operations[i].lst_successeurs[j]);
        }
        printf("\n");



        /*printf("  Precedents: ");
        for (int j = 0; operations[i].lst_precedents[j] != 0; j++) {
            printf("%d |", operations[i].lst_precedents[j]);
        }
        printf("\n\n");*/
    }
}