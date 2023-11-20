#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NB_OPERATIONS 35

typedef struct {
    int id;
    int lst_precedents[NB_OPERATIONS];
    float duree;
} Operation;

//void initialisation_precedence

void intialisation_operations(Operation lst_operations[]) {
    int i;
    for (i = 0; i < NB_OPERATIONS; i++) {
        lst_operations[i].id = i;
        lst_operations[i].duree = 0;
        lst_operations[i].lst_precedents[] = {0};
    }
}

void contrainte_precedence_avec_temps(Operation lst_operations[], int temps_de_cycle) {
    /*
     * Cette fonction permet de verifier si les contraintes de precedence sont respectees
     * ++ On prend en compte le temps de cycle
     *
     *
     */

    int i;
    for (i = 0; i < NB_OPERATIONS; i++) {
        int j;
        for (j = 0; j < NB_OPERATIONS; j++) {
            if (lst_operations[i].lst_precedents[j] == 1) { // Si l'operation j est un precedent de l'operation i
                if (lst_operations[i].duree < lst_operations[j].duree + temps_de_cycle) { // Si l'operation i est plus courte que l'operation j + temps de cycle
                    // On met a jour la duree de l'operation i
                    lst_operations[i].duree = lst_operations[j].duree + temps_de_cycle;
                }
            }
        }
    }
}



int main() {
    printf("Hello, World!\n");
    return 0;
}
