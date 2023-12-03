#include <stdio.h>
#include <stdlib.h>
#include "Bloc.h"



#define TAILLE_MAX 100 // Remplacez la valeur par celle appropriée

void Filtrage(int exclusion[TAILLE_MAX][2], int nbContraintes, int blocInitial[TAILLE_MAX], int tailleBloc)
{
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
            nbOperationsFiltrees++;
        }
        else
        {
            station[1][nbOperationsNonFiltrees] = operationCourante;
            nbOperationsNonFiltrees++;
        }
    }

    // Boucle pour gérer le reste des opérations non filtrées
    for (int i = 0; i < nbOperationsNonFiltrees; i++)
    {
        int operationCourante = station[1][i];
        bool reste = true;

        for (int k = 0; k < nbContraintes; k++)
        {
            if (exclusion[k][0] == operationCourante || exclusion[k][1] == operationCourante)
            {
                int autreOperation = (exclusion[k][0] == operationCourante) ? exclusion[k][1] : exclusion[k][0];

                for (int l = 0; l < nbOperationsNonFiltrees; l++)
                {
                    if (station[1][l] == autreOperation)
                    {
                        // Supprimer l'opération de la station[1]
                        for (int m = l; m < nbOperationsNonFiltrees - 1; m++)
                        {
                            station[1][m] = station[1][m + 1];
                        }
                        nbOperationsNonFiltrees--;

                        // Ajouter l'opération à la station[2]
                        station[2][resteoperationnonfiltrees] = autreOperation;
                        //nbOperationsNonFiltrees++;
                        resteoperationnonfiltrees++;

                        reste = false;
                        break;
                    }
                }
            }
        }

        if (reste)
        {
            station[2][resteoperationnonfiltrees] = operationCourante;
            //resteoperationnonfiltrees++;
        }


    }

    // Affichage des opérations filtrées
    printf("Operations filtrees :\n");
    for (int i = 0; i < nbOperationsFiltrees; i++)
    {
        printf("%d ", station[0][i]);
    }
    printf("\n");

    // Affichage des opérations non filtrées
    printf("Operations non filtrees :\n");
    for (int i = 0; i < nbOperationsNonFiltrees; i++)
    {
        printf("%d ", station[1][i]);
    }
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