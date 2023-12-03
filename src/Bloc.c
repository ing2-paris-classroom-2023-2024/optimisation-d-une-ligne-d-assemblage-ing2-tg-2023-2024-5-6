#include <stdio.h>
#include <stdlib.h>
#include "Bloc.h"



#define TAILLE_MAX 100 // Remplacez la valeur par celle appropriée

void Filtrage(int exclusion[TAILLE_MAX][2], int nbContraintes, int blocInitial[TAILLE_MAX], int tailleBloc)
{

    // https://c.developpez.com/cours/20-heures/?page=page_16
    // https://www.youtube.com/watch?v=6mlp13UGfUM&t=374s&ab_channel=HassanELBAHI
    // https://www.youtube.com/watch?v=eY9j3qmy3bQ&ab_channel=BilalEnesFedar
    // https://openclassrooms.com/forum/sujet/un-tableau-a-deux-dimensions-avec-malloc-69343

    int nbOperationsFiltrees = 0;
    int nbOperationsNonFiltrees = 0;
    int resteoperationnonfiltrees = 0;

    // Utilisation d'un tableau 2D pour représenter les stations
    int **station;
    station = malloc(3 * sizeof(int *)); // Trois stations : 0 pour les filtrées, 1 pour les non-filtrées, 2 pour le reste
    if (station == NULL)
    {
        fprintf(stderr, "Erreur d'allocation");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++)
    {
        station[i] = malloc(tailleBloc * sizeof(int));
        if (station[i] == NULL)
        {
            fprintf(stderr, "Erreur d'allocation");
            exit(EXIT_FAILURE);
        }
    }

    // Boucle externe parcourant le bloc initial
    for (int i = 0; i < tailleBloc; i++)
    {
        int operationCourante = blocInitial[i];
        bool peutEtreAjoute = true;

        // Boucle interne parcourant les contraintes
        for (int k = 0; k < nbContraintes; k++)
        {
            if (exclusion[k][0] == operationCourante || exclusion[k][1] == operationCourante)
            {
                int autreOperation = (exclusion[k][0] == operationCourante) ? exclusion[k][1] : exclusion[k][0];
                // On récupère l'autre opération de la contrainte
                // Nous sommes dans le cas d'un opérateur ternaire : condition ? valeur si vrai : valeur si faux
                // Car on veut récupérer l'autre opération de la contrainte
                // https://c.developpez.com/cours/20-heures/?page=page_16

                /*
                La signification de cet opérateur est la suivante :

                Dans notre cas, la condition est : exclusion[k][0] == operationCourante
                _ Si la condition est vraie, exclusion[k][1] est évaluée. ( l'autre opération de la contrainte - Ex: 4)
                _ Si la condition est fausse, exclusion[k][0] est évaluée. ( l'opération de la contrainte - Ex: 1)
                */


                for (int l = 0; l < nbOperationsFiltrees; l++)
                {
                    if (station[0][l] == autreOperation)
                    {
                        peutEtreAjoute = false;
                        break;
                    }
                }
            }
        }

        // Ajouter l'opération à la liste appropriée
        if (peutEtreAjoute)
        {
            station[0][nbOperationsFiltrees] = operationCourante;
            nbOperationsFiltrees++; // on place les éléments dans la station 0
        }
        else {
            station[1][nbOperationsNonFiltrees] = operationCourante;
            nbOperationsNonFiltrees++; // on place les éléments dans la station 1
        }



//pour cette partie, on s'occupe du reste : dans le cas ou la station 1 possède une exclusion (ex: 1 4) ,
// on doit supprimer l'élément 2 (ex : 4) (exclusion[k][1]) de la station 1 et le mettre dans la station 2.
// permet que toutes les contraintes soient respectées.
    for (int i = 0; i < nbOperationsNonFiltrees; i++) // le nombre élément station 1
    {
        int operationCourante1 = station[1][i];
        bool reste = true;

        for (int k = 0; k < nbContraintes; k++)
        {
            if (exclusion[k][0] == operationCourante1 || exclusion[k][1] == operationCourante1)
            {
                int autreOperation = (exclusion[k][0] == operationCourante1) ? exclusion[k][1] : exclusion[k][0];

                for (int l = 0; l < nbOperationsNonFiltrees; l++)
                {
                    if (station[1][l] == autreOperation) // si on trouve une opération, on supprime de la station1
                    {
                        for (int m = l; m < nbOperationsNonFiltrees - 1; m++)
                        {
                            station[1][m] = station[1][m + 1];//déplacer les éléments pour combler le vide
                        }
                        nbOperationsNonFiltrees--; //retirer le nombre opération de la station 1

                        //on place dans la station[2]
                        station[2][resteoperationnonfiltrees] = autreOperation;
                        resteoperationnonfiltrees++;

                        reste = false;
                        break;
                    }
                }
            }
        }

        if (reste) station[2][resteoperationnonfiltrees] = operationCourante1;



    }

    // Affichage des opérations filtrées
    printf("Operations filtrees :\n");
    for (int i = 0; i < nbOperationsFiltrees; i++)
    {
        printf("%d ", station[0][i]);
    }

    // Affichage des opérations non filtrées
    printf("\nOperations non filtrees :\n");

    for (int i = 0; i < nbOperationsNonFiltrees; i++)
    {
        printf("%d ", station[1][i]);
    }

    // Affichage des opérations restantes
    printf("\n Operation restante :\n");

    for (int i = 0; i < resteoperationnonfiltrees; i++)
    {
        printf("%d ", station[2][i]);
    }

    // Libération de la mémoire
    free(station[0]);
    free(station[1]);
    free(station[2]);
    free(station);
}
}