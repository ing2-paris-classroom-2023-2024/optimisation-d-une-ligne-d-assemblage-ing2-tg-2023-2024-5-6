#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <main.h>

#include <initialisation_operations.h>
#include <Fonctions_tests.h>
#include <Traverser_les_operations.h>
#include <Time_module.h>

#include <time.h>
#include <windows.h>

int main() {
    Operation operations[NB_OPERATIONS];
    int numOperations = 0;


    lecture_de_fichier(operations, &numOperations);
    fusion_Operations(operations, &numOperations);

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