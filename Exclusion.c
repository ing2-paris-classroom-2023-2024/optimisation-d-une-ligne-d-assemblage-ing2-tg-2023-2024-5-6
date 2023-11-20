

// STRUCTURE DE DONNEES
#include <stdio.h>
#include <stdlib.h>

#define OPERATION_MAX 100
#define NB_STATIONS_MAX 10

// Structure pour représenter les contraintes d'exclusion
typedef struct
{
    int op1;
    int op2;
} Exclusion;

// Structure pour représenter la répartition des opérations sur les stations
typedef struct
{
    int station[OPERATION_MAX];
} Repartition;




// LECTURE DES FICHIERS DE CONTRAINTES

void LireFichierContraintes(char* nomFichier, Exclusion* exclusion, int* nbExclusions)
{
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    fscanf(fichier, "%d", nbExclusions);

    for (int i = 0; i < *nbExclusions; i++) {
        fscanf(fichier, "%d %d", &exclusion[i].op1, &exclusion[i].op2);
    }

    fclose(fichier);
}




// INITIALISATION DE LA REPARTITION DES OPERATIONS SUR LES STATIONS

void initialisationRepartition(Repartition* repartition)
{
    for (int i = 0; i < OPERATION_MAX; i++)
    {
        repartition->station[i] = -1;
    }
}


// SYSTEME DE VERIFICATION DE LA REPARTITION DES OPERATIONS SUR LES STATIONS

void verification (Repartition* repartition, Exclusion* exclusion, int nbExclusions)
{
    for (int i = 0; i < nbExclusions; i++)
    {
        if (repartition->station[exclusion[i].op1] == repartition->station[exclusion[i].op2])
        {
            printf("Erreur : les opérations %d et %d sont sur la même station\n", exclusion[i].op1, exclusion[i].op2);
            exit(EXIT_FAILURE);
        }
    }
}



// ATTRIBUTION DE LA REPARTITION DES OPERATIONS SUR LES STATIONS

void attributionRepartition(Repartition* repartition, const Exclusion exclusion[], int nbExclusions)
{
    int station = 1;
    for (int i = 0; i < nbExclusions; i++) {
        if (repartition->station[exclusion[i].op1 - 1] == -1) {
            repartition->station[exclusion[i].op1 - 1] = station;
        }

        if (repartition->station[exclusion[i].op2 - 1] == -1) {
            repartition->station[exclusion[i].op2 - 1] = station;
        }

        station = (station % NB_STATIONS_MAX) + 1;
    }
}








