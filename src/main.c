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

int main() {
    Operation operations[NB_OPERATIONS];
    int numOperations = 0;

    readGraphFromFile(operations, &numOperations);
    mergeOperations(operations, &numOperations);

    Affichage_Operations(operations, numOperations);

    gestion_precedence(operations);

    //On commence a executer l'Operation 1. Apres la duree, on passe a l'Operation qui suit la 1 (en regardant les precedents)
    //On continue jusqu'a ce que toutes les Operations soient completees
    //On affiche le temps total d'execution
    //On affiche le temps d'execution de chaque Operation

    t_clock clock;
    initializeClock(&clock);

    for (int i = 0; i < numOperations; i++) {
        tick(&clock, &operations[i]);
    }

    return 0;
}