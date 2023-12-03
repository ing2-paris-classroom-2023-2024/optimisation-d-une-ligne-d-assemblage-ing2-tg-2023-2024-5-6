//
// Created by zheboss on 11/26/2023.
//

#include "Fonctions_tests_affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <main.h>

#include <initialisation_operations.h>
#include <Time_module.h>
#include <color.h>

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
    //Fonction qui verifie si la File est vide
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

void affichage_successeur(Operation op[], int i) {
    printf("  lst_successeurs: ");
    for (int j = 0; j < NB_OPERATIONS; j++) {
        if (op[i].lst_successeurs[j] != 0)
        printf("%d ", op[i].lst_successeurs[j]);
    }
}

void affichage_precedent(Operation op[], int i) {
    printf("  lst_precedents: ");
    for (int j = 0; j < NB_OPERATIONS; j++) {
        if (op[i].lst_precedents[j] != 0)
        printf("%d ", op[i].lst_precedents[j]);
    }
}

void affichage_attributs_operations(Operation op[], int numOperation) {
    //Fonction qui affiche les attributs de chaque operation
    for (int i = 0; i < numOperation; i++) {
        printf("Operation %d:\n", op[i].id);
        printf("  duree: %f\n", op[i].duree);
        //printf("  statut_complete: %d\n", op[i].statut_complete);
        affichage_successeur(op, i);
        printf("\n");
        affichage_precedent(op, i);
        printf("\n");
    }
}

void affichage_File(int File[]) {
    //Fonction qui affiche la File
    for (int j = 0; j < NB_OPERATIONS; j++) {
        if (File[j] != 0) {
            printf("%d ", File[j]);
        }
    }
    printf("\n");
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

void affichage_debut() {
    printf("\n\n\n");
    rouge();
    printf("===================================================================\n");
    printf("|   ligne d'assemblage de la future voiture électrique ECElecar   |\n");
    printf("===================================================================\n");
    reset();
    printf("\n\n\n");
}

void affichage_init_graphe() {
    jaune();
    printf("---------------------------------------------\n");
    printf("|         INITIALISATION DU GRAPHE          |\n");
    printf("---------------------------------------------\n");
    reset();
}

void affichage_precedence() {
    bleu();
    printf("---------------------------------------------\n");
    printf("|         CONTRAINTE DE PRECEDENCE          |\n");
    printf("---------------------------------------------\n");
    reset();
}

void affichage_exclusion() {
    vert();
    printf("---------------------------------------------\n");
    printf("|          CONTRAINTE D' EXCLUSION          |\n");
    printf("---------------------------------------------\n");
    reset();
}

void affichage_multi_contraintes() {
    magenta();
    printf("---------------------------------------------\n");
    printf("|             MULTI-CONTRAINTES             |\n");
    printf("---------------------------------------------\n");
    reset();
}