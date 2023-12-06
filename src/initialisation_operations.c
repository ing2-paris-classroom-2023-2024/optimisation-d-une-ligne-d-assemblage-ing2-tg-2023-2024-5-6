//
// Created by zheboss on 11/23/2023.
//

#include "initialisation_operations.h"
#include <Traverser_les_operations.h>
#include <stdio.h>
#include <stdlib.h>
#include <main.h>


int find_missing_operations(Operation op[], int numOperation, int missing[]) {

    int numMissing = 0; // Booleen indiquant si l'operation est manquante

    int presence[NB_OPERATIONS-1];

    for (int i = 0; i < NB_OPERATIONS-1; i++) {
        // On initialise le tableau de presence a 0
        presence[i] = 0;
    }

    for (int i = 0; i < NB_OPERATIONS; i++) {
        presence[op[i].id] = 1;
    }

    for (int i = 1; i < NB_OPERATIONS-1; i++) {
        if (presence[i] == 0) {
            missing[numMissing] = i;
            numMissing++;
        }
    }

    return numMissing;

}

void matrice_to_lst(int matrice[][NB_OPERATIONS], Operation op[]) {
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
                for (int m = 0; m < numMissing; m++) {
                    if (missing[m] <= adjustedIndex) {
                        adjustedIndex++;
                    }
                }

                if (0 < adjustedIndex && adjustedIndex < NB_OPERATIONS) {
                    op[i].lst_successeurs[indice] = adjustedIndex;
                }
                indice++;
            }
        }
        op[i].lst_successeurs[indice] = 0;
    }
    //Tout point inferieur a 0 ou sueprieur a NB_OPERATIONS est egale a 0
    for (int i = 0; i < NB_OPERATIONS; i++) {
        for (int j = 0; op[i].lst_successeurs[j] != 0; j++) {
            if (op[i].lst_successeurs[j] < 0 || op[i].lst_successeurs[j] > NB_OPERATIONS) {
                op[i].lst_successeurs[j] = 0;
            }
        }
    }
    //Affichage des successeurs - FONCTION TEST
    /*for (int i = 0; i < NB_OPERATIONS; i++) {
        printf("Operation %d: ", op[i].id);
        for (int j = 0; op[i].lst_successeurs[j] != 0; j++) {
            printf("%d ", op[i].lst_successeurs[j]);
        }
        printf("\n");
    }*/
}



int initialisation_successeurs(Operation lst_operations[]) {
    //Parametres de la fonction:
    //  lst_operations: tableau contenant toutes les operations

    //Objectif de la fonction:
    //  Initialiser les successeurs de chaque operation
    //  On prend en compte les operations manquantes

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
    for (int i = 0; i < NB_OPERATIONS; i++) {
        for (int j = 0; lst_operations[i].lst_precedents[j] != 0; j++) {
            int index = recherche_indice_id(lst_operations[i].lst_precedents[j], lst_operations, NB_OPERATIONS);
            //Si j est present dans le tableau de precedents de i, alors i est present dans le tableau de successeurs de j
            //On prend en compte les operations manquantes
            tableau_successeurs[index][i] = 1;
        }
    }

    //Affichage du tableau de successeurs
    /*for (int i = 0; i < NB_OPERATIONS; i++) {
        printf("Operation %d: ", lst_operations[i].id);
        for (int j = 0; j < NB_OPERATIONS; j++) {
            printf("%d ", tableau_successeurs[i][j]);
        }
        printf("\n");
    }*/

    matrice_to_lst(tableau_successeurs, lst_operations);

    printf("---------------------------------\n");
    printf("Initialisation des successeurs terminee.\n");
}

int cmpfunc(const void *a, const void *b) {
    //Fonction utilisee pour qsort
    Operation *operationA = (Operation *)a;
    Operation *operationB = (Operation *)b;
    return operationA->id - operationB->id;
}

void fusion_Operations(Operation operations[], int *numOperations) {
    //Parametres de la fonction:
    //  operations: tableau contenant toutes les operations
    //  numOperations: nombre d'operations

    //Objectif de la fonction:
    //  Fusionner les operations qui ont le meme identifiant
    //  On prend en compte les operations manquantes

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
    printf("---------------------------------\n");
    printf("Fusion des operations terminee.\n");
}

void lecture_de_fichier(Operation operations[], int *numOperations) {
    //Parametres de la fonction:
    //  operations: tableau contenant toutes les operations
    //  numOperations: nombre d'operations

    //Objectif de la fonction:
    //  Lire le fichier "graphe.txt" et initialiser les precedents de chaque operation

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

    while (fscanf(file, "%d %d", &operations[*numOperations].lst_precedents[0], &operations[*numOperations].id) == 2) {
        //fscanf permet de lire les donnees du fichier et de les stocker dans les variables

        if (operations[*numOperations].lst_precedents[0] > NB_OPERATIONS)
        //Si l'operation n'existe pas, on la met a 0
        { operations[*numOperations].lst_precedents[0] = 0; }

        (*numOperations)++;

        if (*numOperations > 1) {
            //si numOperations est superieur a 0, on realloc lst_precedents
            //On augmente la taille de lst_precedents
            operations[*numOperations - 1].lst_precedents = realloc(operations[*numOperations - 1].lst_precedents,(*numOperations) * sizeof(int));
        }
        //printf("%d ", operations[*numOperations].lst_precedents[0]);
        //Affichage de lst_precedents
        /*for (int i = 0; operations[*numOperations].lst_precedents[i] != 0; i++) {
            printf("%d ", operations[*numOperations].lst_precedents[i]);
        }*/
    }
    fclose(file);
    printf("---------------------------------\n");
    printf("Lecture du graphe terminee.\n");
}

