#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <main.h>

#include <initialisation_operations.h>
#include <Time_module.h>

#include <time.h>
#include <windows.h>

typedef struct {
    float current_time;
} t_clock;

void initializeClock(t_clock *clock) {
    clock->current_time = 0.0;
}

void tick(t_clock *clock, Operation *operation) {
    // Simulate the passage of time
    sleep((unsigned int)operation->duree);
    printf("Operation %d\n", operation->id);

    // Update the current time
    clock->current_time += operation->duree;
}

int gestion_precedence(Operation lst_operations[]) {
    int id_operation;
    printf("Veuillez entrer l'identifiant de l'operation : ");
    scanf("%d", &id_operation);
    if (id_operation < 0 || id_operation > NB_OPERATIONS) {
        printf("L'identifiant de l'operation n'est pas correct. Veuillez reessayer.\n");
        gestion_precedence(lst_operations);
    }
    else {
        if (lst_operations[id_operation].statut_complete == 1) {
            printf("L'operation est complete.\n");
        }
        else {
            printf("L'operation n'est pas complete.\n");
        }
    }
}

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
                printf("==========================\n");
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
                    printf("Operation %d [indice: %d]: %d\n", i+1, indice, adjustedIndex);
                    op[i].lst_successeurs[indice] = adjustedIndex;
                    printf("Operation[%d].lst_successeurs[%d] = %d\n", i, indice, op[i].lst_successeurs[indice]);
                }
                indice++;
            }
        }
        op[i].lst_successeurs[indice] = 0;
    }
    //Affichage des successeurs
    for (int i = 0; i < NB_OPERATIONS; i++) {
        printf("Operation %d: ", i + 1);
        for (int j = 0; op[i].lst_successeurs[j] != 0; j++) {
            printf("%d ", op[i].lst_successeurs[j]);
        }
        printf("\n");
    }
}



int initialisation_successeurs(Operation lst_operations[]) {
    //Avec le tableau de precedence, nous allons l'interser.
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
            //Si j est present dans le tableau de precedents de i, alors i est present dans le tableau de successeurs de j
            tableau_successeurs[lst_operations[i].lst_precedents[j] - 1][i] = 1;
        }
    }

    //Affichage du tableau de successeurs
    for (int i = 0; i < NB_OPERATIONS; i++) {
        //printf("Operation %d: ", i + 1);
        for (int j = 0; j < NB_OPERATIONS; j++) {
            printf("%d ", tableau_successeurs[i][j]);
        }
        printf("\n");
    }

    matrice_to_array(tableau_successeurs, lst_operations);

    printf("Initialisation des successeurs terminee.\n");
}



int main() {
    Operation operations[NB_OPERATIONS];
    int numOperations = 0;

    readGraphFromFile(operations, &numOperations);
    mergeOperations(operations, &numOperations);

    initialisation_duree(operations);
    initialisation_successeurs(operations);


    Affichage_Operations(operations, numOperations);

    //gestion_precedence(operations);

    //On commence a executer l'Operation 1. Apres la duree, on passe a l'Operation qui suit la 1 (en regardant les precedents)
    //On continue jusqu'a ce que toutes les Operations soient completees
    //On affiche le temps total d'execution
    //On affiche le temps d'execution de chaque Operation

    /*
    t_clock clock;
    initializeClock(&clock);

    for (int i = 0; i < numOperations; i++) {
        tick(&clock, &operations[i]);
    }*/

    return 0;
}