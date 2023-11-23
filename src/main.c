#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <main.h>

#include <initialisation_operations.h>



//void initialisation_precedence

//Fonction qui gere la precedence
// - Prends en parametre un tableau d'operations.
// - Demande a l'utilisateur de rentrer une operation.
// - Fonction cherche si le statut de l'operation est a 1 ou a 0.
// - Retourne le statut de l'operation.

int gestion_precedence(Operation lst_operations[]) {
    int id_operation;
    printf("Veuillez entrer l'identifiant de l'operation : ");
    scanf("%d", &id_operation);
    return lst_operations[id_operation].statut_complete;
}

int main() {
    Operation operations[NB_OPERATIONS];
    int numOperations = 0;

    readGraphFromFile(operations, &numOperations);
    mergeOperations(operations, &numOperations);

    Affichage_Operations(operations, numOperations);

    gestion_precedence(operations);
    if (operations[0].statut_complete == 1) {
        printf("L'operation est complete");
    } else {
        printf("L'operation n'est pas complete");
    }

    return 0;
}