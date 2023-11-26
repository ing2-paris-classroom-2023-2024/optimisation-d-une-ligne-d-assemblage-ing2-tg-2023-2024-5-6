//
// Created by zheboss on 11/26/2023.
//

#include "Traverser_les_operations.h"
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
    printf("Successeurs de l'operation %d: ", id);
    for (int i = 0; i < numSuccessors; i++) {
        printf("%d ", lst_sucesseurs[i]);
    }
    printf("\n");
    printf("================================\n");


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

    // Definition d'une pile de NB_OPERATIONS lignes
    int Pile[NB_OPERATIONS];
    int indice = 0;
    //Ajout dans la Pile toute les operations avec 0 comme precedent
    for (int i = 0; i < NB_OPERATIONS; i++) {
        if (op[i].lst_precedents[0] == 0) {
            Pile[indice] = op[i].id;
            op[i].statut_complete = 1;
            indice++;
        }
    }

    //Pile[0] = op[startOperation].id;
    //op[startOperation].statut_complete = 1;
    int i = 0;
    for (int j = indice; j < NB_OPERATIONS; j++) {
        Pile[j] = 0;
    }
    printf("Operation de debut: %d\n", Pile[0]);

    while (i < NB_OPERATIONS) {
        // Affichage de la pile
        /*printf("Pile: ");
        for (int j = 0; j < NB_OPERATIONS; j++) {
            if (Pile[j] != 0) {
                printf("%d ", Pile[j]);
            }
        }*/

        int lst_successeurs[NB_OPERATIONS];
        lst_successeurs[0] = 0; // Initialisation de la liste des successeurs

        // si id possede un successeur
        int indice = recherche_indice_id(Pile[i], op, numOperation);
        recherche_sucesseurs(op, Pile[i], lst_successeurs, numOperation);
        int num_successors = 1;
        if (op[indice].lst_successeurs[0] != 0) {

            while (lst_successeurs[0] != 0) {
                int id = lst_successeurs[0];
                int j = 0;
                while (lst_successeurs[j] != 0) {
                    lst_successeurs[j] = lst_successeurs[j + 1];
                    j++;
                }
                if (id_in_pile(id, Pile)) {
                    //printf("id_in_pile\n");
                    // Si l'id est dans la pile, on ne fait rien
                    break;
                } else {
                    //printf("id_not_in_pile\n");
                    // Sinon, on l'ajoute a la pile si tous les precedents ont statut_complete = 1
                    if (recherche_precedents(op, id)) {
                        // Recherche de l'indice de la pile ou valeur = 0
                        int k = 0;
                        while (Pile[k] != 0) {
                            k++;
                        }
                        Pile[k] = id;
                        // Set statut_complete to 1 for the added operation
                        int addedOperationIndex = recherche_indice_id(id, op, NB_OPERATIONS);
                        op[addedOperationIndex].statut_complete = 1;
                        num_successors++;
                        //sleep(5*(unsigned int)op[addedOperationIndex].duree);
                        printf("Pile: ");
                        for (int j = 0; j < NB_OPERATIONS; j++) {
                            if (Pile[j] != 0) {
                                printf("%d ", Pile[j]);
                            }
                        }
                        printf("\n");
                    } /*else {
                        printf("Tout precedents ne sont pas completes\n");
                    }*/
                }

            }
        }
        i++;
    }
}





