//
// Created by zheboss on 11/26/2023.
//

#include "Fonctions_tests.h"
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