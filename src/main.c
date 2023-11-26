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


int P_est_vide(int P[]) {
    //Fonction qui verifie si la pile est vide
    if (P[0] == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int recherche_indice_id(int id, Operation op[], int numOperation) {
    //Fonction qui recherche l'indice d'une operation dans le tableau d'operations
    int targetIndex = -1;
    for (int i = 0; i < numOperation; i++) {
        if (op[i].id == id) {
            targetIndex = i;
            break;
        }
    }
    return targetIndex;
}

int recherche_sucesseurs(Operation op[], int id, int lst_sucesseurs[], int numOperation) {
    // Fonction qui recherche les successeurs d'une operation
    int numSuccessors = 0;

    printf("|RS| ID: %d\n", id);

    // On recupere l'indice de l'operation dans le tableau d'operations
    int indice = recherche_indice_id(id, op, numOperation);
    printf("|RS| INDICE: %d\n", indice);
    //Affichage du premier successeur
    printf("Operation[%d].lst_successeurs[0] = %d\n", indice, op[indice].lst_successeurs[0]);


    // Check if the target operation ID is not found
    if (indice == -1) {
        printf("Operation with ID %d not found.\n", id);
        return -1;
    }

    // Check if the target operation has no successors
    if (op[indice].lst_successeurs[0] == 0) {
        printf("Operation with ID %d has no successors.\n", id);
        return 0;
    }
    else {
        for (int i = 0; op[indice].lst_successeurs[i] != 0; i++) {
            printf("Operation[%d].lst_successeurs[%d] = %d\n", indice, i, op[indice].lst_successeurs[i]);
            lst_sucesseurs[i] = op[indice].lst_successeurs[i];
            numSuccessors++;
        }
    }

    // Sort the lst_sucesseurs array based on the duration of the operations
    if (numSuccessors > 1) {
        for (int i = 0; i < numSuccessors - 1; i++) {
            for (int j = 0; j < numSuccessors - i - 1; j++) {
                // Compare durations directly without using recherche_indice_id
                if (op[lst_sucesseurs[j] - 1].duree > op[lst_sucesseurs[j + 1] - 1].duree) {
                    // Swap indices if the duration is longer
                    int temp = lst_sucesseurs[j];
                    lst_sucesseurs[j] = lst_sucesseurs[j + 1];
                    lst_sucesseurs[j + 1] = temp;
                }
            }
        }
    }


    // Affichage des successeurs
    printf("=======================\n");
    for (int i = 0; i < numSuccessors; i++) {
        printf("Operation %d: %d\n", i + 1, lst_sucesseurs[i]);
    }
    printf("=======================\n");

    return numSuccessors;
}


int id_in_pile(int id, int Pile[]) {
    //Fonction qui verifie si l'id est dans la pile
    int i = 0;
    while (Pile[i] != 0) {
        if (Pile[i] == id) { return 1; }
        i++;
    }
    return 0;
}


void traverse_operations(Operation op[], int startOperation, int numOperation) {
    for (int i = 0; i < numOperation; i++) {
        printf("%d: %d\n", op[i].id, op[i].lst_successeurs[0]);
    }
    printf("----------------------------------TRAVERSE-----------------------------------------\n");
    //Defintion d'une pile de NB_OPERATIONS lignes
    int Pile[NB_OPERATIONS];
    Pile[0] = op[startOperation].id;
    int i = 0;
    for (int j = 1; j < NB_OPERATIONS; j++) {
        Pile[j] = 0;
    }
    printf("Operation de debut: %d\n", Pile[0]);

    while (i < NB_OPERATIONS) {
        //Affichage de la pile
        printf("Pile: ");
        for (int j = 0; j < NB_OPERATIONS; j++) { printf("%d ", Pile[j]); }

        int lst_sucesseurs[NB_OPERATIONS];
        lst_sucesseurs[0] = 0;      //Initialisation de la liste des successeurs
        printf("\n135\n");

        //si id possede un successeur
        int indice = recherche_indice_id(Pile[i], op, numOperation);
        printf("|||Traverse||| i: %d |/| INDICE: %d |/| Operation: %d", i, indice, Pile[i]);
        recherche_sucesseurs(op, Pile[i], lst_sucesseurs, numOperation);
        printf("||||LST_SUCCESSEURS[0]: %d\n", lst_sucesseurs[0]);
        int num_sucessors = 1;
        if (op[indice].lst_successeurs[0] != 0) {

            printf("139\n");
            //recherche_sucesseurs(op, Pile[i], lst_sucesseurs, numOperation);

            while (lst_sucesseurs[0] != 0) {
                printf("139\n");
                printf("|140||LST_SUCCESSEURS[0]: %d\n", lst_sucesseurs[0]);
                int id = lst_sucesseurs[0];
                int j = 0;
                while (lst_sucesseurs[j] != 0) {
                    lst_sucesseurs[j] = lst_sucesseurs[j + 1];
                    j++;
                }
                printf("145\n");
                printf("ID: %d\n", id);
                if (id_in_pile(id, Pile)) {
                    printf("id_in_pile\n");
                    //Si l'id est dans la pile, on ne fait rien
                    break;
                }
                else {
                    printf("id_not_in_pile\n");
                    //Sinon, on l'ajoute a la pile
                    //REcherche de l'indice de la pile ou valeur  = 0
                    int k = 0;
                    while (Pile[k] != 0) {
                        k++;
                    }
                    Pile[k] = id;
                    num_sucessors++;
                }
                printf("165\n");
            }
        }
        i++;
    }
}



int main() {
    Operation operations[NB_OPERATIONS];
    int numOperations = 0;


    readGraphFromFile(operations, &numOperations);
    mergeOperations(operations, &numOperations);

    initialisation_duree(operations);
    initialisation_successeurs(operations);




    //Affichage_Operations(operations, numOperations);

    traverse_operations(operations, 0, numOperations);

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