//
// Created by zheboss on 11/26/2023.
//

#include "Traverser_les_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <main.h>

#include <initialisation_operations.h>
#include <Time_module.h>
#include <Fonctions_tests_affichage.h>
#include <color.h>

#include <time.h>
#include <windows.h>

int recherche_indice_id(int id, Operation op[], int numOperation) {
    //Fonction qui recherche l'indice d'une operation dans le tableau d'operations
    int targetIndex = 0;
    for (int i = 0; i < numOperation; i++) {
        if (op[i].id == id) {
            targetIndex = i;
            break;
        }
    }
    return targetIndex;
}

int recherche_sucesseurs(Operation op[], int id, int lst_sucesseurs[], int numOperation) {
    //Parametres de la fonction:
    //  operations: tableau contenant toutes les operations
    //  numOperations: nombre d'operations
    //  id: identifiant de l'operation dont on veut trouver les successeurs
    //  lst_successeurs: tableau contenant les successeurs de l'operation

    //Objectif de la fonction:
    //  Trouver les successeurs de l'operation dont l'identifiant est id
    //  Afficher les successeurs
    //  Retourner le nombre de successeurs


    // Fonction qui recherche les successeurs d'une operation
    int numSuccessors = 0;

   // printf("|RS| ID: %d\n", id);

    // On recupere l'indice de l'operation dans le tableau d'operations
    int indice = recherche_indice_id(id, op, numOperation);
    //printf("|RS| INDICE: %d\n", indice);
    //Affichage du premier successeur
    //printf("Operation[%d].lst_successeurs[0] = %d\n", indice, op[indice].lst_successeurs[0]);

    if (indice == -1) {
        //printf("Operation with ID %d not found.\n", id);
        return -1;
    }

    // Si l'operation n'a pas de successeurs
    if (op[indice].lst_successeurs[0] == 0) {
        //printf("Operation with ID %d has no successors.\n", id);
        return 0;
    }
    else {
        for (int i = 0; op[indice].lst_successeurs[i] != 0; i++) {
            //printf("Operation[%d].lst_successeurs[%d] = %d\n", indice, i, op[indice].lst_successeurs[i]);
            lst_sucesseurs[i] = op[indice].lst_successeurs[i];
            numSuccessors++;
        }
    }

    // Tri des successeurs par ordre croissant de duree
    if (numSuccessors > 1) {
        for (int i = 0; i < numSuccessors - 1; i++) {
            for (int j = 0; j < numSuccessors - i - 1; j++) {
                // Comparaison des durees
                if (op[lst_sucesseurs[j] - 1].duree > op[lst_sucesseurs[j + 1] - 1].duree) {
                    int temp = lst_sucesseurs[j];
                    lst_sucesseurs[j] = lst_sucesseurs[j + 1];
                    lst_sucesseurs[j + 1] = temp;
                }
            }
        }
    }
    //Affichage des successeurs
    /*printf("Successeurs de l'operation %d: ", id);
    for (int i = 0; i < numSuccessors; i++) {
        printf("%d ", lst_sucesseurs[i]);
    }
    printf("\n");
    printf("================================\n");*/


    return numSuccessors;
}


int id_in_File(int id, int File[]) {
    //Fonction qui verifie si l'id est dans la File
    int i = 0;
    while (File[i] != 0) {
        if (File[i] == id) { return 1; }
        i++;
    }
    return 0;
}


int recherche_precedents(Operation op[], int id) {
    int indice = recherche_indice_id(id, op, NB_OPERATIONS);
    for (int i = 0; op[indice].lst_precedents[i] != 0; i++) {
        int precedentId = op[indice].lst_precedents[i];
        int precedentIndice = recherche_indice_id(precedentId, op, NB_OPERATIONS);
        if (op[precedentIndice].statut_complete != 1) {
            return 0; // Not all precedents have statut_complete = 1
        }
    }
    return 1; // All precedents have statut_complete = 1
}


void traverse_operations(Operation op[], int startOperation, int numOperation) {
    //Parametres de la fonction:
    //  operations: tableau contenant toutes les operations
    //  numOperations: nombre d'operations
    //  startOperation: identifiant de l'operation de debut

    //Objectif de la fonction:
    //  Effectue un parcours en profondeur du graphe des opérations
    //  En commençant par une opération spécifiée et en visitant ses successeurs.

    // Definition d'une File de NB_OPERATIONS lignes
    int *File = malloc(NB_OPERATIONS * sizeof(int));
    int indice = 0;
    //Ajout dans la File toute les operations avec 0 comme precedent
    for (int i = 0; i < NB_OPERATIONS; i++) {
        if (op[i].lst_precedents[0] == 0) {
            File[indice] = op[i].id;
            op[i].statut_complete = 1;
            indice++;
        }
    }

    int i = 0;
    for (int j = indice; j < NB_OPERATIONS; j++) {
        File[j] = 0;
    }
    float duree_totale = 0;

    //affichage_attributs_operations(op, numOperation);

    while (i <= NB_OPERATIONS) {
        // Affichage de la File
        affichage_File(File);
        //affichage_successeur(op, i);

        int *lst_successeurs = malloc(NB_OPERATIONS * sizeof(int));
        lst_successeurs[0] = 0; // Initialisation de la liste des successeurs

        // si id possede un successeur
        int indice = recherche_indice_id(File[i], op, numOperation);
        recherche_sucesseurs(op, File[i], lst_successeurs, numOperation);


        //printf("Operation %d\n", op[indice].id);
        //printf("Duree: %f\n", op[indice].duree);

        op[indice].statut_complete = 1;
        int num_successors = 1;
        //Si duree depasse le temps de cycle
        /*if (duree_totale > TEMPS_DE_CYCLE) {
            printf("Duree totale: %f ms\n", duree_totale);
            printf("La duree totale depasse le temps de cycle.\n");
            return;
        }*/



        if (op[indice].lst_successeurs[0] != 0) {

            while (lst_successeurs[0] > 0 && lst_successeurs[0] <= NB_OPERATIONS) {
                int id = lst_successeurs[0];

                int j = 0;
                if (id_in_File(id, File)) {
                    // Si l'id est dans la File, on ne fait rien
                    break;
                }

                while (lst_successeurs[j] != 0) {
                    lst_successeurs[j] = lst_successeurs[j + 1];
                    j++;
                }
                if (!id_in_File(id, File)) {
                    // Sinon, on l'ajoute a la File si tous les precedents ont statut_complete = 1
                    if (recherche_precedents(op, id)) {
                        // Recherche de l'indice de la File ou valeur = 0
                        int k = 0;
                        while (File[k] != 0) {
                            k++;
                        }

                        File[k] = id;
                        // Set statut_complete to 1 for the added operation
                        int addedOperationIndex = recherche_indice_id(id, op, NB_OPERATIONS);
                        num_successors++;
                        unsigned int microseconds = (unsigned int)(op[indice].duree * 1000000);
                        //printf("microseconds: %d\n", microseconds);
                        usleep(microseconds);
                        //printf("Operation %d complete\n", op[indice].id);

                        duree_totale += calcul_duree_total(File,indice, 2, op);
                    }
                }
            }

        }

        i++;

    }
    printf("\nFile finale: \n");
    rouge();
    affichage_File(File);
    reset();
}





